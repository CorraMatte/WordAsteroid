#include "data.h"

#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

extern display_info_t display_info;

/**
 *      Funzione ausiliaria che genera un alert con la richiesta di uscire dal gioco. \n
 *      Parametri: \n
 *      1) display - Puntatore al display del gioco; \n
 *      2) playing - Flag per indicare se si sta giocando, in modo da modificare il messaggio; \n
 * 		Ritorna un booleano, e indica se si desidera uscire (true) o continuare a giocare (false).
 */
bool exit(ALLEGRO_DISPLAY * display, const bool playing);

/**
 *      Funzione che converte il punteggio (intero) in una stringa di otto caratteri.\n
 *      Parametri:\n
 *      1) match_score - Il punteggio intero.\n
 *      Ritorna il puntatore contenente la stringa formattata.
 */
char* int_to_str_score(const int & match_score);

/**
 *      Funzione che, dato un certo punto del display, restituisce il quadrante (1-4) al quale appartiene. \n
 *      Parametri: \n
 *      1) x - Ascissa punto; \n
 *      2) y - Ordinata punto.
 */
int which_quadrant(const float x, const float y);

/**
 *		Funzione che estrai l'elemento dalla coda. Non sono necessari controlli prima dell'estrazione, perchè sono fatti
 * 		prima della chiamata a questa funzione. \n
 *      Parametri: \n
 * 		1) ast_queues - Vettore di liste di asteroidi; \n
 * 		2) character - Iniziale dell'elemento da eliminare, cioè indice dell'array.
 */
void extract_elem(asteroid_list * ast_queues, const int & index_to_extract);

/**
 *      Funzione che inserisce un elemento nella lista, con un controllo se l'elemento è inserito in testa o in coda. 
 * 		Ricavo l'indice della coda direttamente da asteroid.word[0]. \n
 *      Parametri: \n
 * 		1) ast_queues - Vettore di liste di asteroidi; \n
 * 		2) asteroid - Asteroide da inserire.
 * 		Ritorna un intero, -1 se l'asteroide è stato inserito in testa altrimenti un indice che rappresenta il numero della coda.
 */
int insert_elem_head(asteroid_list * ast_queues, const asteroid_t& asteroid);

/**
 *      Funzione adibita al set/reset di una determinata impostazione di gioco. \n
 *      Parametri: \n
 *      1) enable - Impostazione corrente.
 */
void change_enable(enable_t& enable);

/**
 *      Funzione che dealloca gli asteroidi in gioco a fine partita e le relativi immagini. \n
 *		Parametri: \n
 *		1) ast_queues - Vettore di liste di asteroidi.
 */
void delete_ast_queues(asteroid_list* ast_queues);

/**
 *      Funzione che dealloca i timer utilizzati come appoggio durante la partita. \n
 *		Parametri: \n
 *		1) match_vars - Contenitore dei puntatori ai tre timer.
 */
void delete_timer(match_vars_t& match_vars);

/**
 *      Funzione che dealloca il display, la coda degli eventi e la musica alla chiusera del gioco.
 *		Parametri: \n
 *		1) display - Puntatore al display del gioco; \n
 *		2) ev_queue - Puntatore alla coda di eventi; \n
 *		3) sound - Puntatore alla musica del gioco.
 */
void delete_display_evqueue_music(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue, ALLEGRO_SAMPLE* sound);

/**
 *      Funzione che dealloca i suoni durante la singola partita. \n
 *		Parametri: \n
 *		1) match_vars - Contenitore dei puntatori agli audio.
 */
void delete_sounds(match_vars_t& match_vars);

/**
 *      Funzione che restituisce la lista di archivi presenti nella cartella.\n
 *      Parametri:\n
 *      1) ls - struttura che rappresenta i file contenuti nella cartella.
 *      Ritorno false in caso di errore, true altrimenti.
 */
bool ls_tar(ls_t *ls);

/**
 *      Funzione true nel caso la cartella indicata durante la compilazione del programma contenga archivi validi.\n
 *      Ritorna false altrimenti.
 */
bool archives_exist();