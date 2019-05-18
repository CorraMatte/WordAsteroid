#include "data.h"
#include "utilities.h"
#include "init.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>

extern display_info_t	display_info;
extern ALLEGRO_SAMPLE	*music_wa;
extern playwa_gv_t	PLAYWA_GV;
extern thread_manager_t	thread_manager;
extern words_buffer_t	words_buffer;

/**
 * 		Funzione che fa partire il rispettivo suono del gioco, se i suoni sono attivati.
 * 		Parametri: \n
 * 		1) sound - Suono da far partire; \n
 * 		2) en_sound - Impostazioni che indica se i suoni sono ON/OFF.
 */
void sound_play(ALLEGRO_SAMPLE* sound, const enable_t& en_sound);

/**
 * 		Funzione che fa partire la musica del gioco.
 */
void music_wa_play();

/**
 *      Funzione che genera un singolo asteroide (di tipo compreso tra 3 e lev) in un punto casuale del bordo della zona di gioco. \n
 *      Parametri: \n
 *      1) lev - Livello attuale; \n
 * 		2) v - lingua della parole dell'asteroide \n
 *      3) s - Caratteristiche speciali dell'asteroide \n
 *      4) next_p - In caso di conflitto, viene utilizzata come posizione in cui inserire l'asteroide
 */
asteroid_t generate_asteroid(const asteroid_special_t s, const int &next_p);

/**
 *		Funzione che muove i bullets, e quando c'è una collisione viene definitivamente eliminato l'asteroide dalla lista, e aggiornati i bonus
 * 		corrispondenti agli asteroidi distrutti. \n
 * 		Parametri: \n
 * 		1)	bullet - Vettore dei bullet; \n
 * 		2) match_vars - Contenitore delle variabili di gioco; \n
 * 		3)  items - Vettore dei bonus.
 * 
 */
void move_bullets(bullet_t * bullet, match_vars_t& match_vars, enable_t& en_sound);

/**
 *    	Funzione che muove l'asteroide in relazione al suo angolo con lo shooter, in modo che segua la retta che congiunge
 * 	   	shooter - asteroide. \n
 *     	Parametri: \n
 * 	   	1) ast_queues - Vettore di liste di asteroidi; \n
 * 	   	2) extract_index - Indice dell'asteroide in campo ma da non far comparire.
 */
void move_asteroids(asteroid_list * ast_queues, const int& extract_index);

/**
 *      Funzione che ruota lo shooter in base all'asteroide puntato. \n
 *      Parametri: \n
 *      1) shooter - Informazioni relative allo shooter; \n
 *      2) ast_queues - Vettore di liste di asteroidi; \n
 *      3) current_asteroid - Carattere corrispondente all'asteroide puntato.
 */
void move_shooter(shooter_t& shooter, const asteroid_list * ast_queues, const int current_asteroid);

/**
 *     Funzione che, in base alla posizione degli asteroidi in gioco e dello shooter, controlla se ci siano collisioni,
 * 	   ovvero se lo shooter e un asteroide in gioco si siano toccati, e il gioco in questo caso finisce. \n
 *     Parametri: \n
 * 	   1) ast_queues - Vettore di liste di asteroidi; \n
 * 	   2) shooter - Informazioni relative allo shooter; \n
 * 	   3) arr_bullet - Vettore dei proiettili.
 */
bool check_gameover(asteroid_list * ast_queues, const shooter_t& shooter, const bullet_t * arr_bullet);

/**
 *      Funzione che restitusice la distanza tra il meteorite più vicino all'asteroide e l'asteroide stesso.
 * 		Parametri: \n
 * 		1) ast_queues - Vettore di liste di asteroidi; \n
 * 		2) arr_bullet - Vettore dei proiettili \n
 * 	  	3) shooter - Informazioni relative allo shooter.
 */
float check_distance(const asteroid_list * ast_queues, const bullet_t * arr_bullet, const shooter_t& shooter);

/**
 * 		Funzione che controlla lo stato dello scudo. Se c'è gameover ma lo scudo è attivo grazie al bonus 'shield',
 * 		l'asteroide che colpisce lo scudo viene distrutto. \n
 * 		Parametri: \n
 * 		2) match_vars - Contenitore delle variabili di gioco; \n
 * 		2) arr_bullet - Vettore dei proiettili; \n
 * 	  	3) shooter - Informazioni relative allo shooter.
 */
void check_shield(match_vars_t& match_vars, bullet_t* arr_bullet, shooter_t& shooter, enable_t& en_sound);

/**
 * 		Funzione di routine che gestisce l'evento della scadenza di un timer. In base al timer scaduto (spawn, shield, rallenty) genera
 * 		l'evento associato. \n
 * 		Parametri: \n
 * 		1) ev - Evento generato; \n
 * 		2) match_vars - Contenitore dei tre timer; \n
 * 	  	3) settings - Impostazioni di gioco.
 */
void handler_timer(ALLEGRO_EVENT ev, match_vars_t &match_vars, settings_t &settings);

/**
 * 		Funzione di routine che gestisce l'evento della scadenza di un timer. In base al timer scaduto (spawn, shield, rallenty) genera
 * 		l'evento associato. \n
 * 		Parametri: \n
 * 		1) ev - Evento generato; \n
 * 		2) match_vars - Contenitore delle variabili di gioco; \n
 * 	  	3) arr_bullet - Vettore dei proiettili; \n
 * 		4) shooter - Informazioni relative allo shooter; \n
 * 		5) settings - Impostazioni di gioco.
 */
void handler_key_pressed(ALLEGRO_EVENT ev, match_vars_t& match_vars, bullet_t* arr_bullet, shooter_t& shooter, settings_t& settings);

/**
 * 		Funzione che mette cambia la musica tra le varie schermate. \n
 * 		Parametri: \n
 * 		1) path - Percorso del nuovo audio.
 */
void change_music(const char* path, const enable_t& music);

/**
 *      Funzione che implementa il consumer thread. Ad intervalli regolari viene estratta una parola
 *      ed inserita all'interno del gioco. \n
 * 		Parametri: \n
 * 		1) mv - Puntatore alle match vars, le variabili di gioco; \n
 */
void *spawn_asteroid_thread(void *mv);