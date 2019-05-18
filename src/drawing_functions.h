#include "data.h"
#include "graphical_values.h"
#include "game_functions.h"

#include <string>
#include <cassert>

extern display_info_t	display_info;
extern general_gv_t	GENERAL_GV;
extern menu_gv_t	MENU_GV;
extern playwa_gv_t	PLAYWA_GV;
extern instr_gv_t	INSTR_GV;
extern usr_gv_t	USR_GV;

/**
 *      Funzione che genera l'array contenente i puntatori ai bitmap relativi alla schermata di gioco. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_BITMAP **generate_playwa_bitmaps();

/**
 *      Funzione che genera l'array contenente i puntatori ai font relativi alla schermata di gioco. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_FONT **generate_playwa_fonts();

/**
 *      Funzione che genera l'array contenente i puntatori ai bitmap relativi alla schermata del menu principale. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_BITMAP **generate_menu_bitmaps();

/**
 *      Funzione che genera l'array contenente i puntatori ai bitmap relativi alla schermata di pausa. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_BITMAP **generate_instr_bitmaps();

/**
 *      Funzione che genera l'array contenente i puntatori ai font relativi ai menu. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_FONT **generate_menu_fonts();

/**
 *      Funzione che genera l'array contenente i puntatori ai font relativi alla schermata di pausa. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_FONT **generate_instr_fonts();

/**
 *      Funzione che genera l'array contenente i puntatori ai font relativi alla schermata di gameover. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_FONT **generate_user_fonts();

/**
 *      Funzione che genera l'array contenente i puntatori ai font relativi alla schermata delle impostazioni. \n
 *      Ritorna un puntatore all'array generato.
 */
ALLEGRO_FONT **generate_settings_fonts();

/**
 *      Funzione che dealloca un array di bitmap, oltre che tutti i bitmap in esso contenuti. \n
 *      Parametri: \n
 *      1) arr - Array di bitmap; \n
 *      2) num - Dimensione dell'array di bitmap.
 */
void destroy_arr_bitmaps(ALLEGRO_BITMAP **arr, const int num);

/**
 *      Funzione che dealloca un array di font, oltre che tutti i font in esso contenuti. \n
 *      Parametri: \n
 *      1) arr - Array di font; \n
 *      2) num - Dimensione dell'array di font.
 */
void destroy_arr_fonts(ALLEGRO_FONT **arr, const int num);

/**
 *      Funzione che stampa lo sfondo della schermata. \n
 *      Parametri: \n
 *      1) bmp_bg - Bitmap relativo allo sfondo; \n
 *      2) offset_bg - Scostamento in pixel dello sfondo dal lato sinistro della schermata (per rotazione sfondo); \n
 *      3) playing - Flag sul quale si basa la velocità di rotazione (durante il gioco risulta essere più lenta).
 */
void draw_background(ALLEGRO_BITMAP *bmp_bg, float &offset_bg, const bool playing);

/**
 *      Funzione che stampa il titolo della schermata. \n
 *      Parametri: \n
 *      1) head_str - Stringa relativa al titolo; \n
 *      2) font - Font relativo al titolo.
 */
void draw_head(char *head_str, ALLEGRO_FONT *font);

/**
 *      Funzione che stampa la stringa di ritorno al gioco, o al menu principale (in base alla variabile "pause"). \n
 *      Parametri: \n
 *      1) font - Font relativo alla stringa di ritorno; \n
 *      2) pause - In base al valore assunto da questa variabile viene stampata la stringa adatta.
 */
void draw_back(ALLEGRO_FONT *font, const bool pause);

/**
 *      Funzione che gestisce l'inizializzazione dell'animazione di introduzione. \n
 *      Parametri: \n
 *      1) arr_bitmaps - Array di bitmap; \n
 *      2) bg_offset - Offset iniziale dello sfondo.
 */
void draw_intro_init(ALLEGRO_BITMAP **arr_bitmaps, float &bg_offset);

/**
 *      Funzione che gestisce lo slide del titolo nell'animazione di introduzione. \n
 *      Parametri: \n
 *      1) arr_bitmaps - Array di bitmap; \n
 *      2) bg_offset - Offset iniziale dello sfondo.
 */
void draw_intro_title_slide(ALLEGRO_BITMAP **arr_bitmaps, float &bg_offset);

/**
 *      Funzione che gestisce il fadein del menu nell'animazione di introduzione. \n
 *      Parametri: \n
 *      1) arr_bitmaps - Array di bitmap; \n
 *      2) arr_fonts - Array di font; \n
 *      3) bg_offset - Offset iniziale dello sfondo.
 */
void draw_intro_menu_fadein(ALLEGRO_BITMAP **arr_bitmaps, ALLEGRO_FONT **arr_fonts, float &bg_offset);

/**
 *      Funzione che stampa il bitmap relativo al titolo presente nel menu principale. \n
 *      Parametri: \n
 *      1) bmp_title - Bitmap relativo al titolo.
 */
void draw_menu_title(ALLEGRO_BITMAP *bmp_title);

/**
 *      Funzione che stampa l'opzione indicata (menu). \n
 *      Parametri: \n
 *      1) index - Indice dell'opzione; \n
 *      2) bmp_option - Bitmap relativo all'opzione indicata; \n
 *      3) font - Font relativo all'opzione indicata; \n
 *      4) str_scelta - Stringa relativa all'opzione indicata; \n
 *      5) settings - Se vero, stampa le opzioni leggermente più in alto rispetto al menu principale.
 */
void draw_menu_option(const int &index, ALLEGRO_BITMAP *bmp_option, ALLEGRO_FONT *font, char *str_scelta,
                      const bool settings);

/**
 *      Funzione che stampa la stringa di copyright (menu). \n
 *      Parametri: \n
 *      1) font - Font relativo alla stringa di copyright.
 */
void draw_menu_copyright(ALLEGRO_FONT *font);

/**
 *      Funzione che stampa il punteggio e i suggerimenti (schermata di gioco). \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) font_score - Font relativo al punteggio; \n
 *      3) font_hints - Font relativo ai suggerimenti; \n
 *      4) visible_hints - Se true, mostra i suggerimenti di gioco.
 */
void draw_playwa_score_hint(const match_vars_t &match_vars, ALLEGRO_FONT *font_score, ALLEGRO_FONT *font_hints,
                            const bool visible_hints);

/**
 *      Funzione che stampa lo shooter, la sua area (bianca normalmente, rossa in caso di pericolo o azzurra nel caso in cui il bonus "shield" venga attivato). \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) arr_bullet - Array contenente i proiettili in gioco; \n
 *      3) shooter - Struct contenente le variabili relative allo shooter; \n
 *      4) arr_bitmaps - Array contenente i bitmap di gioco.
 */
void draw_playwa_shooter(const match_vars_t &match_vars, const bullet_t *arr_bullet, const shooter_t &shooter,
                         ALLEGRO_BITMAP **arr_bitmaps);

/**
 *      Funzione che stampa lo gli asteroidi ed i proiettili presenti in gioco. \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) arr_bullet - Array contenente i proiettili in gioco; \n
 *      3) arr_bitmaps - Array contenente i bitmap di gioco; \n
 *      4) font - Font relativo agli asteroidi.
 */
void
draw_playwa_asteroids_bullets(const match_vars_t &match_vars, const bullet_t *arr_bullet, ALLEGRO_BITMAP **arr_bitmaps,
                              ALLEGRO_FONT *font);

/**
 *      Funzione che stampa i bonus della partita (e le icone relative al suono). \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) arr_bitmaps - Array contenente i bitmap di gioco; \n
 *      3) font_score - Font relativo al punteggio (utilizzato per stampare l'intestazione dei bonus); \n
 *      4) font_bonus - Font relativo alla numerosità dei bonus; \n
 *      5) font_bonus_hint - Font relativo al suggerimento per l'attivazione del bonus.
 */
void draw_playwa_bonus_music(const match_vars_t &match_vars, ALLEGRO_BITMAP **arr_bitmaps, ALLEGRO_FONT *font_score,
                             ALLEGRO_FONT *font_bonus, ALLEGRO_FONT *font_bonus_hint, settings_t settings);

/**
 *      Funzione che gestisce l'animazione di fine partita. \n
 *      Parametri: \n
 *      1) score_goal - Score effettiva del giocatore; \n
 *      2) dast_goal - Asteroidi effettivamente distrutti; \n
 *      4) bg_bmp - Bitmap di sfondo; \n
 *      5) bg_offset - Scostamento laterale dello sfondo; \n
 *      6) arr_fonts - Array dei font necessari.
 */
void draw_gameover_animation(const int &score_goal, const int &dast_goal, ALLEGRO_BITMAP *bg_bmp, float &bg_offset,
                             ALLEGRO_FONT **arr_fonts);

/**
 *      Funzione che disegna i risultati estratti dagli archivi corrispondenti alla password inserita dell'utente. \n
 *      Parametri: \n
 *      1) arr_fonts - Array dei font necessari;\n
 *      2) res - Risultati dei match estratti;
 */
void draw_results(ALLEGRO_FONT *font, result_t res);

/**
 *      Funzione che disegna il bottone "play again" nella schermata di Game Over. \n
 *      Parametri: \n
 *      1) arr_fonts - Array dei font necessari;\n
 */
void draw_playagain_button(ALLEGRO_FONT *font);

/**
 *      Funzione che disegna i blocchi di sfondo relativi ai risultati di fine partita. \n
 *      Parametri: \n
 *      1) font - Font utilizzato.
 */
void draw_stats_blocks(ALLEGRO_FONT *font);

/**
 *      Funzione che disegna un singolo risultato. \n
 *      Parametri: \n
 *      1) idx_stat - Indice del risultato; \n
 *      2) stat_value - Valore del risultato; \n
 *      3) font - Font utilizzato.
 */
void draw_stat(const int &idx_stat, int stat_value, ALLEGRO_FONT *font);

/**
 *      Funzione che disegna il blocco di inserimento dello username. \n
 *      Parametri: \n
 *      1) enter_active - Se true, è possibile cliccare il tasto di invio dello username; \n
 *      2) font - Font utilizzato.
 */
void draw_username_block(const bool enter_active, ALLEGRO_FONT *font);

/**
 *      Funzione che disegna lo username. \n
 *      1) username - Stringa dello username; \n
 *      2) cur_pos - Posizione corrente all'interno della stringa; \n
 *      3) font - Font utilizzato; \n
 *      4) bar_visible - Se vero, il cursore è visibile.
 */
void draw_username(char *username, const int &cur_pos, ALLEGRO_FONT *font, const bool bar_visible);

/**
 *      Funzine che disegna le istruzioni durante la pausa. \n
 *      Parametri: \n
 *      1) arr_fonts - Array contenente i font utilizzati; \n
 *      2) arr_bitmaps - Array contenente i bitmap utilizzati.
 */
void draw_instructions(ALLEGRO_FONT **arr_fonts, ALLEGRO_BITMAP **arr_bitmaps);
