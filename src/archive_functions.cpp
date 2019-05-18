#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <malloc.h>
#include <archive.h>
#include <archive_entry.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <cctype>
#include "archive_functions.h"

/**
 *      Funzione che prova a convertire la stringa in maiuscolo. Se la stringa contiene caratteri che non sono
 *      numeri o lettere, ritorna nullptr. Viene usata per validare la password estratta dall'archivio.\n
 *      Parametri:\n
 *      1) str - stringa da convertire in maiuscolo e validare.
 *      Ritorna la nuova stringa in maiuscolo, oppure nullptr se contiene caratteri speciali.
 */
static inline char *convert_to_only_alpha(char *str) {
	char	*tmp = new char[strlen(str) + 1];
	int	i, c = 0;

	for (i = 0; i < strlen(str); ++i) {
        if (!isalpha(str[i]) && !isdigit(str[i]))
            return nullptr;
        if (islower(str[i]))
            tmp[c] = toupper(str[i]);
        else
            tmp[c] = str[i];
        c++;
    }

    tmp[c] = '\0';
    return tmp;
}

/**
 *      Funzione che pulisce e chiude l'archivio che si stava analizzando.\n
 *      1) arg - Puntatore all'oggetto da deallocare.
 */
static void extract_archive_cancel_routine(void *arg) {
	struct archive	*a = (struct archive *) arg;
	pthread_mutex_unlock(&thread_manager.gameover_mutex);
	pthread_mutex_unlock((&thread_manager.words_buffer_mutex));
	archive_clear_error(a);
	archive_read_free(a);
}

/**
 *      Funzione che pulisce e chiude l'entry di lettura dell'archivio
 *      che si stava analizzando.\n
 *      1) arg - Puntatore all'oggetto da deallocare.
 */
static void extract_entry_cancel_routine(void *arg) {
	struct archive_entry	*entry = (struct archive_entry *) arg;
	archive_entry_free(entry);
}

/**
 *      Funzione che pulisce e sblocca il mutex relativo alla condition wait "spawn_mutex".\n
 *      Inoltre fa il free della memoria sull'oggetto passato.\n
 *      Parametri:\n
 *      1) arg - Puntatore all'oggetto da deallocare.
 */
static void extract_free_cancel_routine(void *arg) {
    delete[] (look_into_t* )arg;
}

/**
 *      Funzione che pulisce dalla memoria tutte le strutture dati allocate dal search manager.\n
 *      Inoltre invia un segnale di terminazione ai thread, per poi farne il join.\n
 *      Parametri:\n
 *      1) arg - Puntatore al search manager.
 */
static void start_searching_cancel_routine(void *arg) {
	int i;
	search_manager_t	*sm = (search_manager_t *) arg;

	for (i = 0; i < NUMBER_THREADS; i++) {
        pthread_cancel(sm->threads[i]);
        pthread_join(sm->threads[i], nullptr);
    }
	for (i = 0; i < N_QUEUES; i++) {
        if (words_buffer.words[i] != nullptr) {
            delete[] words_buffer.words[i];
            words_buffer.words[i] = nullptr;
        }
    }

    delete[] sm->file_list->files;
    delete[] sm->file_list;
}

/**
 *      Funzione che si occupa della ricerca della email all'interno di un file contenuto in un archivio. \n
 * 		Parametri: \n
 * 		1) ar - Puntatore all'archivio da esaminare; \n
 * 		2) email - email da ricercare; \n
 * 		3) is_searcher - flag che indica la tipologia del thread; \n
 */
static int search_string(struct archive *ar, const char *email, const bool is_searcher) {
	int	i, r, first_letter;
	const void	*buff;
	char	*row, *t, *char_buffer, *e, *pass;
	char	comma[2] = {":"};
	size_t	size;
	bool	full;
#if ARCHIVE_VERSION_NUMBER >= 3000000
	int64_t offset;
#else
    off_t offset;
#endif

    for (;;) {
        /* Legge ogni blocco del file (generalmente di 65000 caratteri) */
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF) {
            return 0;
        }
        if (r != ARCHIVE_OK)
            return 1;

		char_buffer = (char *) buff;
        row = strtok_r(char_buffer, "\r\n", &t);
        if (row == nullptr) continue;
		first_letter = 0;

        if (is_searcher) {
            pthread_mutex_lock(&thread_manager.words_buffer_mutex);
            full = words_buffer.load == N_QUEUES;
            pthread_mutex_unlock(&thread_manager.words_buffer_mutex);

            if (full)
                sem_wait(&thread_manager.searcher_sem);

            pthread_mutex_lock(&thread_manager.words_buffer_mutex);
            for (i = 0; i < N_QUEUES; ++i) {
                if (words_buffer.words[i] == nullptr) {
                    first_letter = i;
                    break;
                }
            }
            pthread_mutex_unlock(&thread_manager.words_buffer_mutex);
        }


        do {
            if (strstr(row, comma) == nullptr) continue;
            if (is_searcher) {
                pass = strdup(strstr(row, comma) + sizeof(char));

                /* Controllo se sono alla ricerca di lettere */
                if (pass != nullptr && strlen(pass) < MAX_LENGTH_WORD + 1) {
                    pass = convert_to_only_alpha(pass);

                    if (pass != nullptr && toupper(pass[0]) == (first_letter + 'A')) {
                        pthread_mutex_lock(&thread_manager.words_buffer_mutex);
                        if (words_buffer.words[first_letter] == nullptr) {
                            words_buffer.words[first_letter] = strdup(pass);
                            words_buffer.load++;
                        }
                        full = words_buffer.load == N_QUEUES;
                        pthread_mutex_unlock(&thread_manager.words_buffer_mutex);

                        if (full) {
                            sem_post(&thread_manager.consumer_sem);
                            sem_wait(&thread_manager.searcher_sem);
                        }

                        pthread_mutex_lock(&thread_manager.words_buffer_mutex);
                        for (i = 0; i < N_QUEUES; ++i) {
                            if (words_buffer.words[i] == nullptr) {
                                first_letter = i;
                                break;
                            }
                        }
                        pthread_mutex_unlock(&thread_manager.words_buffer_mutex);
                    }
                }
                delete[] pass;
            }

			e = strdup(row);
            e[strlen(row) - strlen(strstr(row, comma))] = '\0';
            if (strstr(e, email) != nullptr) {
                /* Lock della struttura dei risultati e salva il match trovato */
                pthread_mutex_lock(&thread_manager.search_result_mutex);
                row[strlen((row)) - 2] = '\0';
                if (thread_manager.search_manager.res.count_result == MAX_MATCHING_PASS) {
                    pthread_mutex_unlock(&thread_manager.search_result_mutex);
                    continue;
                }
				thread_manager.search_manager.res.pass_result[
						thread_manager.search_manager.res.count_result++
				] = strdup(row);

                /* unlock */
                pthread_mutex_unlock(&thread_manager.search_result_mutex);
            }
            delete[] e;
        } while ((row = strtok_r(nullptr, "\n", &t)) != nullptr);

    }
}

/**
 *      Funzione che estrae i risultati da un archivio. \n
 *      Questi thread gestiscono la ricerca dell'email dello username all'interno delle collection. \n
 *      Parametri: \n
 *      1) look_into - Struttura dati per la ricerca. Contiene la mail, il percorso del file ed un boolean \n
 *      che indica se il thread si tratta di un searcher.
 */
static void *extract(void *look_into) {
	look_into_t	*lk = (look_into_t *) look_into;
	struct archive	*a = archive_read_new();
	struct archive_entry	*entry;
	int	r;

    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    pthread_cleanup_push(extract_free_cancel_routine, lk);
        pthread_cleanup_push(extract_archive_cancel_routine, a);
			pthread_cleanup_push(extract_entry_cancel_routine, entry);
				// if (lk->filename != nullptr && strcmp(lk->filename, "-") == 0)
				//		lk->filename = nullptr;

				if (archive_read_open_filename(a, lk->filename, 1024)) {
					return (void *) 1;
				}
				for (;;) {
					if (!lk->is_searcher) {
						pthread_cond_wait(&thread_manager.gameover_cond,
										  &thread_manager.gameover_mutex);
					}
					r = archive_read_next_header(a, &entry);
					if (r == ARCHIVE_EOF)
						break;

					if (r < ARCHIVE_OK || r < ARCHIVE_WARN) {
						return (void *) 1;
					}
					assert(search_string(a, lk->email, lk->is_searcher) == 0);
				}
				archive_entry_free(entry);
				archive_read_close(a);
				archive_read_free(a);

			pthread_cleanup_pop(0);
        pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void *) 0;
}

void *start_searching(void *search_manager) {
	search_manager_t	*sm= (search_manager_t *) search_manager;
    pthread_cleanup_push(start_searching_cancel_routine, (void *) sm);
        pthread_attr_t	attr;
		long long	sig1;
		int	sig, err, i;
		look_into_t	*lk;
		void	*ret;
        sm->threads = new pthread_t[NUMBER_THREADS];

        for (i = 0; i < sm->file_list->nfile; i++) {
			ret = nullptr;
            if (i >= NUMBER_THREADS) {
            	pthread_testcancel();
                pthread_join(sm->threads[i % NUMBER_THREADS], &ret);
            }
			sig1 = reinterpret_cast<long long> (ret);
			sig = static_cast<int>(sig1);
            assert(sig == 0);

			lk = new look_into_t;
            lk->filename = sm->file_list->files[i].filename;
            lk->email = sm->email;
            lk->is_searcher = i % 2 == 1 || NUMBER_THREADS == 1;

            pthread_attr_init(&attr);
			err = pthread_create(&sm->threads[i % NUMBER_THREADS], nullptr,
								 extract, (void *) lk);
            pthread_attr_destroy(&attr);
            assert(err == 0);
        }
        pthread_join(sm->threads[sm->file_list->nfile - 1], &ret);
    pthread_cleanup_pop(0);
    return nullptr;
}