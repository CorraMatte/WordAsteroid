#include "data.h"
#include "graphical_values.h"
#include "utilities.h"
#include "archive_functions.h"

extern display_info_t display_info;
extern playwa_gv_t PLAYWA_GV;
extern ALLEGRO_SAMPLE *music_wa;

/**
 *      Funzione che inizializza le funzionalità relative all'audio, ai font (ttf), alla tastiera. \n
 * 		Ritorna un booleano che indica il successo delle installazioni.
 */
bool init_game_requirements();

/**
 *      Funzione che inizializza le dimensioni del display di gioco in base alle proporzioni standard (1280x800), adattandole al monitor del proprio computer. Viene lasciata libera una certa porzione di schermo (1/5 in altezza). \n
 * 		Ritorna le dimensioni effettive del display di gioco.
 */
display_info_t init_display_res();

/**
 *      Funzione che crea il puntatore alla coda degli eventi e aggancia alla coda gli eventi relativi alla
 * 		tastiera e display. \n
 * 		Parametri: \n
 * 		1) display - Puntatore al display del gioco; \n
 * 		Ritorna il puntatore alla coda del display, o nullptr se si è verificato un errore nella creazione.
 */
ALLEGRO_EVENT_QUEUE * init_queue_event(ALLEGRO_DISPLAY * & display);

/**
 *		Funzione che indica dopo quanti asteroidi distrutti ottengo il bonus. Inizializza instant_ast_dest, per memorizzare quanti asteroidi
 * 		sono stati distrutti fino a quel momento, per controllare ad ogni asteroide distrutto se si ha diritto al bonus. \n
 * 		Parametri: \n
 * 		1)	instant_ast_dest - Appoggio per sapere quanti asteroidi ho distrutto in quel momento, per capire se ho raggiunto il bonus \n
 * 		2)	asteroids_destroyed - Numero di asteroidi distrutti in quel momento
 */
int init_target_bonus(int& instant_ast_dest, const int& asteroids_destroyed);

/**
 *      Funzione che inizializza un suono del gioco. Le impostazioni di inizializzazione sono standard,
 * 		e il suono viene ripetuto una sola volta. \n
 * 		Parametri: \n
 * 		1) path - Percorso del file audio; \n
 * 		Ritorna il puntatore al suono inizializzato.
 */
ALLEGRO_SAMPLE* init_sound_music(const char* path);

/**
 * 		Funzione che inizializza le varaibili di gioco. \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco;
 *      2) ev_queue - Coda degli eventi (per inizializzazione dei timer).
 */
void init_match_vars(match_vars_t& match_vars, ALLEGRO_EVENT_QUEUE * ev_queue);

/**
 *      Funzione che inizializza le impostazioni di gioco. \n
 *      Parametri: \n
 *      1) settings - Struct contenente le impostazioni di gioco.
 */
void init_settings(settings_t& settings);

/**
 *		Funzione che inizializza le informazioni dello shooter a inizio gioco. \n
 *      Parametri: \n
 *      1) shooter - Struct relativo alla navicella.
 */
void init_shooter(shooter_t& shooter);

/**
 * 		Funzione che inizializza le informazioni di un proiettile. \n
 *      Parametri: \n
 *      1) shooter - Struct relativo al singolo proiettile.
 */
void init_bullet(bullet_t& bullet);

/**
 *      Funzione che inizializza un array di puntatori a asteroidi. \n
 *      Parametri: \n
 *      1) arr_bullet - Array dei bullet.
 */
void init_arr_bullet(bullet_t * arr_bullet);

/**
 *      Funzione che inizializza l'array utilizzato come buffer per le parole tra producer e consumer. \n
 *      Parametri: \n
 *      1) words_buffer - Buffer delle parole.
 */
void init_words_buffer(words_buffer_t &words_buffer);

/**
 *      Funzione che inizializza la struttura dati del thread manager. \n
 *      Questa struttura contiene i mutex, le condition variable e i thread utilizzati durante il gioco,
 *      al fine di sincronizzare i vari worker. \n
 *      Parametri: \n
 *      1) thread_manager - Variabile contenente le strutture per la sincronizzazione;
 *      2) email - Email da cercare con cui viene inizializzato il search manager.
 */
void init_thread_manager(thread_manager_t &thread_manager, char *email);