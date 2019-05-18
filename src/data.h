#ifndef DATA
#define DATA

//============================================
//                  Debug
//============================================

#ifdef DEBUG_MODE
    #define MASK 3
    #define DEB(a,b) { if((a) & MASK){ \
                            for(int	i=0; i < a - 1; i++) \
                                cout<<'\t'; \
                            b \
                       } \
                     }
    #else
    #define DEB(a,b)
#endif

#define DEB1(a) DEB(1, a)
#define DEB2(a) DEB(2, a)

//============================================
//                Inclusioni
//============================================

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <semaphore.h>

//============================================
//                 Costanti
//============================================

/** Numerosita' delle code di asteroidi ('A'..'Z') e del buffer */
const int	N_QUEUES = 'Z' - 'A' + 1;

/** Percorso del file audio relativo alla musica dei menu. */
const char	MUSIC_MENU_PATH_WA[] = "media/sounds/menu.wav";

/** Percorso del file audio relativo alla musica della schermata di gameover. */
const char	MUSIC_GAMEOVER_PATH_WA[] = "media/sounds/gameover.wav";

/** Tempo (in secondi) di durata del bonus "Shield". */
#define TIMER_SHIELD_BONUS 8.0

/** Tempo (in secondi) di durata del bonus "Rallenty". */
#define TIMER_RALLENTY_BONUS 5.0

/** Larghezza della risoluzione base. */
#define GAMERES_W 1280

/** Altezza della risoluzione base. */
#define GAMERES_H 800

/** Frazione di schermo (in altezza) lasciata libera per la creazione della schermata di gioco. */
#define MONITOR_OFFSET_RATE 5

/** Percorso del file audio relativo all'effetto sonoro dell'esplosione di un asteroide. */
const char	SOUND_PATH_EXPLOSION[] = "media/sounds/explosion.wav";

/** Percorso del file audio relativo all'effetto sonoro dello sparo di un proiettile. */
const char	SOUND_PATH_FIRE[] = "media/sounds/fire.wav";

/** Percorso del file audio relativo all'effetto sonoro che viene riprodotto quando si sbaglia una lettera. */
const char	SOUND_PATH_ERROR[] = "media/sounds/error.wav";

/** Percorso del file audio relativo all'effetto sonoro che viene riprodotto quando un asteroide tocca la navicella. */
const char	SOUND_PATH_GAMEOVER[] = "media/sounds/death.wav";

/** Percorso del file audio relativo alla musica della schermata di gioco. */
const char	MUSIC_PLAYWA_PATH_WA[] = "media/sounds/playwa.wav";

/** Percorso del font utilizzato in tutto il progetto. */
const char	FONT_PATH[] = "media/font/visitor.ttf";
/** Percorso della cartella contenente le immagini. */
const char	BMP_PATH_BASE[] = "media/images/";

/** Numerosita' dei bonus. */
#define NUM_ITEMS  4

/** Lunghezza massima dello username del giocatore. */
#define MAX_USERNAME_LENGTH 40

/** Numero massimo di asteroidi in campo (ovvero in testa alle code). \n
 *  Questo accorgimento garantisce un normale flusso nella generazione degli asteroidi: \n
 *  dal momento che le parole relative agli asteroidi vengono generate casualmente, troppe \n
 *  teste occupate (Es. 9 su 10) provocherebbero una situazione di "stallo" dovuto alla \n
 *  probabilità minima di individuare casualmente le teste libere (Es. La decima).
 */
#define MAX_ASTEROID_HEAD	9

/** Numero massimo di caratteri relativi allo score. */
#define MAX_DIGIT_SCORE	8

/** Lunghezza massima delle parole che verranno presentate al giocatore */
#define MAX_LENGTH_WORD	8

/** Massimo numero di password cercate negli archivi */
#define MAX_MATCHING_PASS	10

/** Tempo minimo di spawn tra un asteroide e l'altro. */
#define MIN_TIME_SPAWN	0.5

/** Numero di bitmap relativi ai menu. */
#define NUM_MENU_BITMAPS	4

/** Numero di bitmap relativi alla schermata di gioco. */
#define NUM_PLAYWA_BITMAPS	14

/** Numero di bitmap relativi alla pausa. */
#define NUM_INSTR_BITMAPS	6

/** Numero di font relativi ai menu. */
#define NUM_MENU_FONTS	3

/** Numero di font relativi alla schermata di pausa. */
#define NUM_INSTR_FONTS	4

/** Numero di font relativi al menu delle impostazioni. */
#define NUM_SETTINGS_FONTS	3

/** Numero di font relativi alla schermata di gioco. */
#define NUM_PLAYWA_FONTS	5

/** Numero di font relativi alla schermata di fine partita. */
#define NUM_USER_FONTS	4

/** Tempo (espresso in secondi) di aggiornamento relativo allo scorrimento dello sfondo. */
#define BG_REFRESH_TIME	0.0005

/** Numero di opzioni presenti nel menu principale. */
#define NUM_OPTIONS	3

/** Numero di opzioni presenti nel menu delle impostazioni. */
#define NUM_OPTIONS_SETTINGS	3

/** Punteggio dato dalla distruzione di un asteroide */
#define SCORE_INCREMENT	50

#define SHADOW_COLOR	al_map_rgba_f(0, 0, 0, 0.75)
#define MENU_FONT_COLOR	al_map_rgb(246, 242, 212)
#define MENU_CPY_COLOR	al_map_rgb(122, 124, 119)

//============================================
//                   Enum
//============================================

/** Enumerato relativo alle impostazioni di gioco: attive o non attive.*/
enum enable_t	{
	ON, OFF
};
/** Enumerato relativo al bonus contenuto nel singonlo asteroide: nessuno, Atomic, Rallenty, Fire o Shield. */
enum asteroid_special_t {
	NORMAL, ATOMIC, RALLENTY, FIRE, SHIELD
};

//============================================
//                  Struct
//============================================

/**
 *      Struct contenente le informazioni relative al display. \n
 *      Campi: \n
 *      1) width - Larghezza (in pixel) del display; \n
 *      2) height - Altezza (in pixel) del display.
 */
struct display_info_t{
	float	width;
	float	height;
};

/**
 *      Struct contenente le informazioni relative al singolo asteroide. \n
 *      Campi: \n
 *      1) x - Ascissa dell'asteroide; \n
 *      2) y - Ordinata dell'asteroide; \n
 *      3) slope - Inclinazione della traiettoria dell'asteroide; \n
 *      4) type - Tipo dell'asteroide (corrisponde alla lunghezza della parola; [3,14]); \n
 *      5) radius - Raggio dell'asteroide; \n
 *      6) bmp - Bitmap dell'asteroide; \n
 *      7) special - Bonus contenuto nell'asteroide; \n
 *      8) word - Parola relativa all'asteroide.
 */
struct asteroid_t{
	float	x;
	float	y;
	float	slope;
	// int	type;
	float	radius;

	ALLEGRO_BITMAP *bmp;
	asteroid_special_t special;
	char	word[255];
};

/**
 *      Struct del singolo elemento di una lista di asteroidi. \n
 *      Campi: \n
 *      1) asteroid - Asteroide; \n
 *      2) next - Puntatore al prossimo elemento.
 */
struct elem_asteroid_t{
	asteroid_t asteroid;
	elem_asteroid_t *next;
};

/** Definizione del tipo "lista di asteriodi". */
typedef elem_asteroid_t *asteroid_list;

/**
 *      Struct contenente le informazioni relative al singolo proiettile. \n
 *      Campi: \n
 *      1) x - Ascissa del proiettile; \n
 *      2) y - Ordinata del proiettile; \n
 *      3) slope - Inclinazione della traiettoria del proiettile; \n
 *      4) radius - Raggio del proiettile.
 */
struct bullet_t{
	float	x;
	float	y;
	float	radius;
	float	slope;
};

/**
 *      Struct contenente le informazioni relative al singolo proiettile. \n
 *      Campi: \n
 *      1) x - Ascissa della navicella (centro del display); \n
 *      2) y - Ordinata della navicella (centro del display); \n
 *      3) slope - Angolo di rotazione della "testa" della navicella; \n
 *      4) radius - Raggio della navicella.
 */
struct shooter_t{
	float	x;
	float	y;
	float	slope;
	float	radius;
};

/**
 *      Struct contenenti le password corrispondenti alla mail data in input dall'utente.
 */
struct result_t {
	char	*pass_result[MAX_MATCHING_PASS];
	int	count_result;
};

/** 
 *      Struct contenente le variabili di gioco. \n
 *      Campi: \n
 *		1) ast_queues - Array di liste di asteroidi; \n
 * 		2) score - Punteggio; \n
 * 		3) asteroids_destroyed - Numero di asteroidi distrutti;  \n
 *		4) spawn_interval - Tempo di attesa (espresso in secondi) tra la generazione di due asteroidi; \n
 * 		5) spawn_timer - Timer relativo alla generazione di asteroidi; \n
 *	  	6) timer_shield_bonus - Timer relativo alla durata del bonus "Shield"; \n
 *   	7) timer_rallenty_bonus - Timer relativo alla durata del bonus "Rallenty"; \n
 * 		8) fps - Intervallo di refresh della schermata; \n
 *   	9) diff_liv - Livello di difficoltà del gioco ([3,14]); \n
 *   	10) insert_asteroid_index - Indice che dice se c'è un asteroide in coda che andrà fatto comparire nel gioco; \n
 *   	11) asteroid_head - Numero di asteroidi presenti in testa nel vettore delle liste ([0,NUM_QUEUES]); \n
 *		12) asteroid_to_generate - Tipo dell'asteroide che verrà generato; \n \n
 *  	13) sound_exp - Suono dell'esplosione di un asteroide; \n
 * 		14) sound_fire - Suono dello sparo di un proiettile; \n
 * 		15) sound_gameover - Suono che viene eseguito quando si verifica il gameover; \n
 *		16) sound_rallenty - Suono che sostituisce la musica durante il bonus "Rallenty"; \n
 *		17) sound_error - Suono che viene eseguito quando si digita una lettera sbagliata; \n
 *	 	18) current_asteroid - Indice dell'asteroide che si sta cercando di distruggere. \n
 *          Vale -1 se si deve ancora agganciare un asteroide da colipire; \n
 *   	19) key_error - Indice dell'asteroide del quale si è sbagliata la lettera. Vale -1 se non vi sono errori; \n
 * 		20) playing - Variabile che indica se il gioco è in pausa o si sta giocando; \n
 * 		21) gameover - Variabile che indica se si è verificato il gameover; \n \n
 *		22) items - Array dei bonus: indica la numerosità di ognuno dei quattro bonus; \n
 *   	23) asteroid_to_bonus - Numero di asteroidi da distruggere per ottenere un bonus; \n
 *   	24) instant_ast_dest - Numero di asteroidi distrutti in un determinato istante, in modo da calcolare se si è arrivati al bonus.
 */
struct match_vars_t{
	asteroid_list ast_queues[N_QUEUES];
	int	score;
	int	asteroids_destroyed;
	ALLEGRO_TIMER	*spawn_timer;
	double	spawn_interval;
	ALLEGRO_TIMER	*timer_shield_bonus;
	ALLEGRO_TIMER	*timer_rallenty_bonus;
	float	fps;
	int	insert_asteroid_index;
	int	asteroid_head;
	asteroid_special_t asteroid_to_generate;
	ALLEGRO_SAMPLE	*sound_exp;
	ALLEGRO_SAMPLE	*sound_fire;
	ALLEGRO_SAMPLE	*sound_gameover;
	ALLEGRO_SAMPLE	*sound_error;
	ALLEGRO_SAMPLE_INSTANCE *music_playwa;
	int	current_asteroid;
	int	key_error;
	enable_t	playing;
	bool	gameover;
	int	items[NUM_ITEMS];
	int	asteroid_to_bonus;
	int	instant_ast_dest;
};

/**
 *      Struct contenente le impostazioni di gioco. \n
 *      Campi: \n
 *      2) sound - Impostazione relativa agli effetti sonori ([OFF,ON]); \n
 *      3) music - Impostazione relativa alla musica ([OFF,ON]); \n
 *      4) visible_hints - Se "true", i suggerimenti presenti sulla schermata di gioco risultano essere visibili.
 */
struct settings_t{
	enable_t	sound;
	enable_t	music;
	bool	visible_hints;
};

/** 
 *      Struct relativo alle proporzioni grafiche generali.
 */
struct general_gv_t{
	float	HEAD_TOP_OFFSET;
	float	HEAD_TEXT_SHADOW_GAP;
	float	BACK_TOP_OFFSET;
	float	BACK_LEFT_OFFSET;
	float	BACK_TEXT_SHADOW_GAP;
	float	RESULT_TOP_OFFSET;
	int	HEAD_FONTSIZE;
	int	BACK_FONTSIZE;
};

/**
 *      Struct relativo alle proporzioni grafiche dei menu.
 */
struct menu_gv_t{
	float	TITLE_W;
	float	TITLE_H;
	float	OPTION_W;
	float	OPTION_H;
	float	OPTION_TEXT_OFFSET;
	float	UPPER_OFFSET;
	float	INTERNAL_OFFSET;
	float	COPYRIGHT_TOP_OFFSET;
	int	OPTION_FONTSIZE;
	int	COPYRIGHT_FONTSIZE;
};

/**
 *      Struct relativo alle proporzioni grafiche della schermata di gioco.
 */
struct playwa_gv_t{
	float	TEXT_INTERNAL_OFFSET;
	float	SCORE_TOP_OFFSET;
	float	SCORE_LEFT_OFFSET;
	float	HINT_TOP_OFFSET;
	float	HINT_LEFT_OFFSET;
	float	SHOOTER_AREA_RAD;
	float	SHOOTER_SCALE;
	float	ASTEROID_SHADOW_GAP;
	float	ASTEROID_TEXT_SHADOW_GAP;
	float	BULLET_RADIUS;
	float	HEIGHT_BONUS;
	float	BONUS_TOP_OFFSET;
	float	BONUS_LEFT_OFFSET;
	float	BULLET_SCALE;
	float	DANGER_RADIUS;
	int	SCORE_FONTSIZE;
	int	HINT_FONTSIZE;
	int	ASTEROID_FONTSIZE;
	int	BONUS_NUM_FONTSIZE;
	int	BONUS_HINT_FONTSIZE;
};

/**
 *      Struct relativo alle proporzioni grafiche della schermata di pausa.
 */
struct instr_gv_t{
	float	BONUS_RADIUS;
	float	BONUS_CASE_WIDTH;
	int	SUBTITLE_FONTSIZE;
	int	TEXT_FONTSIZE;
};

/**
 *      Struct relativo alle proporzioni grafiche della schermata di fine partita.
 */
struct usr_gv_t{
	float	USERNAME_BLOCK_TOP_OFFSET;
	float	ENTER_LEFT_OFFSET;
	float	ENTER_TOP_OFFSET;
	float	ENTER_WIDTH;
	float	ENTER_HEIGHT;
	int	USERNAME_FONTSIZE;
	int	STATS_FONTSIZE;
	int	ENTER_FONTSIZE;
};

/**
 *      Struct relativa alla descrizione di un archivio che andrà esaminato.\n
 *      Raccoglie il nome (l'intero percorso) e la sua dimensione per poterli ordinare.
 */
struct file_t {
	char	*filename;
	long int	size;
};

/**
 *      Struct che raccoglie tutti gli archivi.\n
 *      Tiene anche conto di quelli letti attraverso un array di flag.
 */
struct ls_t {
	file_t	*files;
	int	nfile;
};

/**
 *      Struct che rappresenta il manager dei thread atti a ricercare le password all'interno degli archivi.\n
 *      Campi:\n
 *      1) t - Array di thread searcher/worker;\n
 *      2) file_list - Lista degli archivi in cui cercare;\n
 *      3) res - Password che corrispondo all'email dell'utente;\n
 *      4) email - Email inserita dall'utente.
 */
struct search_manager_t {
	pthread_t	*threads;
	ls_t	*file_list;
	result_t	res;
	char	*email;
};

/**
 *      Struct che contiene le variabili di sincronizzazione del gioco.\n
 *      Campi:
 *      1) search_manager - struct che contiene le informazioni per la ricerca dentro gli archivi;
 *      2) searcher_thread - thread che si occupa della ricerca delle informazioni (producer);
 *      3) spawner_thread - thread che si occupa di fornire le parole al gioco (consumer);
 *      4) searcher_sem - semaforo privato per i producer;
 *      5) consumer_sem - semaforo privato per i consumer;
 *      6) spawn_cond - condition per la sincronizzazione dello spawner thread;
 *      7) spawn_mutex - mutex per la sincronizzazione dello spawner thread;
 *      8) words_buffer_mutex - mutex per gestire il buffer condiviso;
 *      9) gameover_cond  - condition per la sincronizzazione dei threads con il gioco principale;
 *      10) gameover_mutex - mutex per la sincronizzazione dei threads con il gioco principale;
 *      11) search_result_mutex - mutex per gestire la mutua esclusione sui risultati della ricerca;
 */
struct thread_manager_t {
	search_manager_t	search_manager;
	pthread_t	searcher_thread;
	pthread_t	spawner_thread;
	sem_t	searcher_sem;
	sem_t	consumer_sem;
	pthread_cond_t	spawn_cond;
	pthread_mutex_t	spawn_mutex;
	pthread_mutex_t	words_buffer_mutex;
	pthread_cond_t	gameover_cond;
	pthread_mutex_t	gameover_mutex;
	pthread_mutex_t	search_result_mutex;
};

/**
 *      Struct buffer che implementa l'architettura producer/consumer
 */
struct words_buffer_t {
	char	*words[N_QUEUES];
	int	load;
};

/**
 *      Struct di appoggio utilizzata dai thread searcher/worker per ricevere informazioni riguardo:
 *      1) filename - dentro quale archivio cercare;
 *      2) email - quale email cercare;
 *      3) is_searcher - se il thread si tratta di un searcher (fornisce le parole al gioco) o di un worker.
 */
struct look_into_t {
	char	*filename;
	char	*email;
	bool	is_searcher;
};

#endif
