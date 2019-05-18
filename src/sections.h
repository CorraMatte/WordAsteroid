#include "data.h"
#include "init.h"
#include "utilities.h"
#include "game_functions.h"
#include "drawing_functions.h"
#include "archive_functions.h"

#include <cstring>
#include <iostream>
#include <fstream>

extern display_info_t display_info;
extern thread_manager_t thread_manager;
extern words_buffer_t words_buffer;
extern menu_gv_t MENU_GV;
extern usr_gv_t USR_GV;
extern ALLEGRO_SAMPLE *music_wa;

/**
 *      Funzione che lancia l'animazione di introduzione. \n
 *      Parametri: \n
 *      1) display - Display corrente. \n
 *      Ritorna la posizione dello sfondo a fine funzione (espressa in pixel).
 */
float intro(ALLEGRO_DISPLAY *display);

/**
 *      Funzione che gestisce la schermata del menu principale. \n
 *      Parametri: \n
 *      1) display - Display corrente; \n
 *      2) ev_queue - Coda degli eventi; \n
 *      3) prev_bg_offset - Posizione dello sfondo al momento del lancio della funzione. \n
 *      Ritorna la scelta effettuata dall'utente.
 */
int main_menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue, const float& prev_bg_offset);

/**
 *      Funzione che gestisce la schermata del menu delle impostazioni. \n
 *      Parametri: \n
 *      1) display - Display corrente; \n
 *      2) ev_queue - Coda degli eventi; \n
 *      3) settings - Struct contenente le impostazioni di gioco. \n
 *      Ritorna true se l'utente decide di tornare al menu principale, false se decide di uscire dal gioco.
 */
bool settings_menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue, settings_t& settings);

/**
 *      Funzione che gestisce la schermata di gioco. \n
 *      Parametri: \n
 *      1) display - Display corrente; \n
 *      2) ev_queue - Coda degli eventi; \n
 *      3) settings - Struct contenente le impostazioni di gioco. \n
 *      Ritorna true se la partita termina normalmente, false se l'utente decide di uscire dal gioco.
 */
bool play_wa(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue, settings_t& settings);
