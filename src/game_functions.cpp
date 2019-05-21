#include <semaphore.h>
#include "game_functions.h"


// Private

/**
 *      Funzione che elimina il primo carattere di una stringa. \n
 *      Parametri: \n
 *      1) str - Stringa sulla quale effettuare lo shift.
 */
static void word_leftshift(char *str) {
	unsigned int	i;
	for (i = 0; i < strlen(str); i++)
        str[i] = str[i + 1];
}

/**
 *      Funzione che calcola la distanza (in pixel) tra due punti del display, considerando il raggio dell'asteroide coinvolto. \n
 *      Parametri: \n
 *      1) x_a - Ascissa del punto a; \n
 *      2) x_b - Ascissa del punto b; \n
 *      3) y_a - Ordinata del punto a; \n
 *      4) y_b - Ordinata del punto b; \n
 *      5) radius -Raggio dell'asteroide coinvolto. \n
 *      Ritorna la distanza calcolata.
 */
static float
calculate_distance(const float &x_a, const float &x_b, const float &y_a,
				   const float &y_b, const float &radius) {
	float	d_x, d_y;
	d_x = x_a + radius - x_b;
	d_y = y_a + radius - y_b;

    return sqrt(pow(d_x, 2) + pow(d_y, 2));
}

/**
 *      Funzione dedicata alla gestione dei caratteri inseriti da tastiera. \n
 *      Parametri: \n
 *      1) ast_queues - Array delle code di asteroidi; \n
 *      2) k - Carattere corrispondente al tasto premuto; \n
 *      3) current_asteroid - Indice dell'asteroide agganciato (nel caso in cui non ve ne siano, vale 0). \n
 *      Ritorna false se: \n
 *      - k non corrisponde ad un carattere alfabetico; \n
 *      - La coda corrispondente a k risulta essere vuota; \n
 *      - L'asteroide è già agganciato, ma k non corrisponde al primo carattere della parola relativa a tale asteroide. \n
 *      Altrimenti, cancella il primo carattere della parola relativa all'asteroide agganciato e ritorna true.
 */
static bool char_key_handler(asteroid_list *ast_queues, const char *k,
							 int &current_asteroid) {
    char	key = k[0];

    if (!isalpha(key) && !isdigit(key))
        return false;

    key = toupper(key);
    if (!isalpha(key) && current_asteroid == -1)
        return false;

    // Nuovo asteroide
    if (current_asteroid == -1) {
        if (ast_queues[key - 'A'] == nullptr) return false;
        current_asteroid = key - 'A';
        word_leftshift(ast_queues[current_asteroid]->asteroid.word);
        return true;
    }

    // Asteroide gia' agganciato
    assert(ast_queues[current_asteroid] != nullptr);
    if (key != ast_queues[current_asteroid]->asteroid.word[0])
        return false;

    word_leftshift(ast_queues[current_asteroid]->asteroid.word);
    return true;
}

/**
 *      Funzione che estrae una parola casuale (o forzata, se invocata con force) dal buffer e la alloca in memoria dinamica. \n
 *      Paramentri: \n
 *      1) force - Indice dell'array (che rappresenta una lettera) da cui viene estratta la parola ricercata.
 *      Se vale zero, allora la prima lettera della parola viene cercata casualmente.\n
 *      Ritorna il puntatore alla parola allocata.
 */
static char *get_random_word(char force) {
	char	i, *punt;
	int	j;

    // Generazione casuale (o assegnamento forzato) di i
    srand(clock());
    i = force == 0 ? rand() % N_QUEUES : force; // perchè estrae da un buffer lungo 0..N_QUEUE-1

    // Prende la parola dal buffer che riempono i searcher_thread
    pthread_mutex_lock(&thread_manager.words_buffer_mutex);

	punt = new char[strlen(words_buffer.words[i])];
    strcpy(punt, words_buffer.words[i]);
    free(words_buffer.words[i]);
    words_buffer.words[i] = nullptr;
    words_buffer.load--;
    pthread_mutex_unlock(&thread_manager.words_buffer_mutex);

    // Manda un segnale ai searcher_thread di riempire il buffer e aspetta
    sem_post(&thread_manager.searcher_sem);
    sem_wait(&thread_manager.consumer_sem);

    return punt;
}

/**
 *		Funzione che elimina l'asteroide selezionato. \n
 * 		Parametri: \n
 * 		1)	ast_queues - Vettore di liste di asteroidi \n
 * 		2)	index_to_extract - Indice dell'asteroide da eliminare \n
 *      Ritorna -1 se l'asteroide non ha asteroide in coda, index_to_extract se ha altri asterodi in coda.
 */
static int delete_asteroid(asteroid_list *ast_queues, const int &index_to_extract) {
    extract_elem(ast_queues, index_to_extract);
    if (ast_queues[index_to_extract] == nullptr) return -1;

    return index_to_extract;
}

/**
 *      Funzione chiamata quando viene distrutto un asteroide: aumenta lo score del giocatore in base al tipo dell'asteroide e
 * 	    ogni 10 asteroidi distrutti aumenta la difficola' del livello. \n
 *      Parametri: \n
 * 	    1) match - Struttura per modificare lo score il numero di asteroidi distrutti; \n
 * 	    2) match_vars - Struttura per aumentare la velocità di spawn degli asteroidi in caso di update di livello; \n
 * 	    3) index_to_extract - Indice dell'asteroide distrutto da cui si ottiene il suo tipo. \n
 *      Ritorna il bonus dell'asteroide da generare.
 */
static asteroid_special_t update_diff_score(match_vars_t &match_vars,
											const int &index_to_extract) {
	int	bonus_to_generate;

    srand(clock());
	match_vars.score += SCORE_INCREMENT;
    match_vars.asteroids_destroyed++;
    match_vars.current_asteroid = -1;
    match_vars.asteroid_head--;

    // Aggiornamento difficolta'
    if (match_vars.asteroids_destroyed % 10 == 0) {
        if (match_vars.spawn_interval > MIN_TIME_SPAWN) match_vars.spawn_interval -= .1;
        al_set_timer_speed(match_vars.spawn_timer, match_vars.spawn_interval);
    }

    if (match_vars.asteroids_destroyed - match_vars.asteroid_to_bonus >= match_vars.instant_ast_dest) {
		match_vars.asteroid_to_bonus = init_target_bonus(
				match_vars.instant_ast_dest,
				match_vars.asteroids_destroyed);
        srand(time(nullptr));

		bonus_to_generate = rand() % NUM_ITEMS;
        switch (bonus_to_generate) {
            case 0:
                return ATOMIC;
            case 1:
                return RALLENTY;
            case 2:
                return FIRE;
            case 3:
                return SHIELD;
        }
    }

    return NORMAL;
}

/**
 *		Funzione che aggiorna i contatori dei bonus. \n
 * 		Parametri: \n
 * 		1)	items[] - Vettore dei bonus; \n
 * 		2)	s - Tipo di bonus ottenuto.
 */
static void update_bonus(int *items, const asteroid_special_t &s) {
    switch (s) {
        case NORMAL:
            break;

        case ATOMIC:
            items[0]++;
            break;

        case RALLENTY:
            items[1]++;
            break;

        case FIRE:
            items[2]++;
            break;

        case SHIELD:
            items[3]++;
    }
}

/**
 *		Funzione che calcola l'indice dell'asteroide più vicino alla navicella. \n
 * 		Parametri: \n
 * 		1) ast_queue - Vettore di liste di asteroidi; \n
 *      2) arr_bullet - Vettore dei proiettili; \n
 * 		3) shooter - Shooter posizionato al centro dello schermo.  \n
 *      Ritorna l'indice dell'asteroide piu' vicino.
 */
static int closer_asteroid(const asteroid_list *ast_queues,
						   const bullet_t *arr_bullet,
						   const shooter_t &shooter) {
	float	distance;
	int	index_to_extract, i;

	distance = 0;
	index_to_extract = -1;

	for (i = 0; i < N_QUEUES; i++)
		if (ast_queues[i] != nullptr &&
			arr_bullet[i].x == 0 &&
			(distance == 0 || distance >
							  calculate_distance(ast_queues[i]->asteroid.x,
												 shooter.x,
												 ast_queues[i]->asteroid.y,
												 shooter.y,
												 ast_queues[i]->asteroid.radius))) {

			distance = calculate_distance(ast_queues[i]->asteroid.x, shooter.x,
										  ast_queues[i]->asteroid.y, shooter.y,
										  ast_queues[i]->asteroid.radius);
            index_to_extract = i;
        }

    return index_to_extract;
}

/**
 *      Funzione che gestisce l'attivazione del bonus "Atomic". \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) arr_bullet - Vettore dei proiettili; \n
 *      3) shooter - Navicella; \n
 *      4) en_sound - Se ON, viene riprodotto il suono dell'esplosione degli asteroidi.
 */
static void atomic_bonus(match_vars_t &match_vars, bullet_t *arr_bullet, enable_t &en_sound) {
	int	i;

	for (i = 0; i < N_QUEUES; i++)
        if (match_vars.ast_queues[i] != nullptr) {

            //Manca da mandare l'animazione
            match_vars.asteroid_to_generate = update_diff_score(match_vars, i);
            assert(match_vars.ast_queues[i] != nullptr);
            al_destroy_bitmap(match_vars.ast_queues[i]->asteroid.bmp);
            update_bonus(match_vars.items, match_vars.ast_queues[i]->asteroid.special);

            if (arr_bullet[i].x != 0) init_bullet(arr_bullet[i]);
            //Elimino gli asteroidi in coda
            while (match_vars.ast_queues[i]->next != nullptr) {

                elem_asteroid_t *h = match_vars.ast_queues[i]->next;
                match_vars.ast_queues[i]->next = h->next;
                delete[] h;
            }

            extract_elem(match_vars.ast_queues, i);
        }

    sound_play(match_vars.sound_exp, en_sound);
    match_vars.current_asteroid = -1;
    match_vars.asteroid_head = 0;
    match_vars.items[0]--;
}

/**
 *      Funzione che gestisce l'attivazione del bonus "Fire". \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) arr_bullet - Vettore dei proiettili; \n
 *      3) shooter - Navicella; \n
 *      4) en_sound - Se ON, viene riprodotto il suono dell'esplosione degli asteroidi.
 */
static void fire_bonus(match_vars_t &match_vars, const bullet_t *arr_bullet,
					   const shooter_t &shooter, enable_t &en_sound) {
	int	index_to_extract;

	index_to_extract = closer_asteroid(match_vars.ast_queues, arr_bullet,
									   shooter);
    if (index_to_extract == -1) return;
    sound_play(match_vars.sound_exp, en_sound);
    al_destroy_bitmap(match_vars.ast_queues[index_to_extract]->asteroid.bmp);
	update_bonus(match_vars.items,
				 match_vars.ast_queues[index_to_extract]->asteroid.special);
    match_vars.asteroid_to_generate = update_diff_score(match_vars, index_to_extract);
	match_vars.insert_asteroid_index = delete_asteroid(match_vars.ast_queues,
													   index_to_extract);
    match_vars.items[2]--;
}

/**
 *      Funzione che gestisce la creazione del singolo asteroide. \n
 *      Parametri: \n
 *      1) match_vars - Struct contenente le variabili di gioco; \n
 *      2) settings - Struct contenente le impostazioni di gioco.
 */
static void spawn_asteroid(match_vars_t &match_vars) {
	int	next_pos_to_insert;

    // Inserimento asteroidi
    if (match_vars.asteroid_head == MAX_ASTEROID_HEAD)
        return;

    match_vars.asteroid_head++;

    // Se l'asteroide conivolto nello spawn era in coda
    if (match_vars.insert_asteroid_index != -1) {
        match_vars.insert_asteroid_index = -1;
        return;
    }

	next_pos_to_insert = insert_elem_head(match_vars.ast_queues,
										  generate_asteroid(
												  match_vars.asteroid_to_generate,
												  0));
    match_vars.asteroid_to_generate = NORMAL;

    // next_pos_to_insert
    while (next_pos_to_insert != -1)
        if (next_pos_to_insert == N_QUEUES) next_pos_to_insert = 0;
        else {
			next_pos_to_insert = insert_elem_head(match_vars.ast_queues,
												  generate_asteroid(
														  match_vars.asteroid_to_generate,
														  next_pos_to_insert));
		}
}

/**
 *		Funzione che genera il bullet corrispondente all'asteroide distrutto, spostandolo all'estremita' dello shooter. \n
 * 		Parametri: \n
 * 		1)	asteroid - Asteroide da distruggere; \n
 * 		2)	shooter - Shooter posizionato al centro dello schermo.
 */
static bullet_t generate_bullet(const asteroid_t &asteroid, const shooter_t &shooter) {
    bullet_t	bullet = {shooter.x, shooter.y, PLAYWA_GV.BULLET_RADIUS,
                       atan((display_info.height / 2 - asteroid.y - asteroid.radius) /
                            (display_info.width / 2 - asteroid.x - asteroid.radius))};

    if (bullet.slope * asteroid.slope < 0)
        bullet.slope = -bullet.slope;

    while (calculate_distance(bullet.x, shooter.x, bullet.y, shooter.y, 0) < shooter.radius) {

        if (asteroid.x < display_info.width / 2) {
            bullet.x -= cos(bullet.slope);
            bullet.y -= sin(bullet.slope);
        } else {
            bullet.x += cos(bullet.slope);
            bullet.y += sin(bullet.slope);
        }

    }

    return bullet;
}

/**
 *      Funzione che pulisce e sblocca il mutex relativo alla condition wait "spawn_mutex".
 */
static void spawn_asteroid_cancel_routine(void *) {
    pthread_mutex_unlock(&thread_manager.spawn_mutex);
}

/*********/

// Public
void *spawn_asteroid_thread(void *mv) {
    pthread_cleanup_push(spawn_asteroid_cancel_routine, nullptr);
        match_vars_t	*match_vars = (match_vars_t *) mv;

        while (true) {
            pthread_cond_wait(&thread_manager.spawn_cond, &thread_manager.spawn_mutex);
            spawn_asteroid(*(match_vars));
        }
    pthread_cleanup_pop(0);
}

void sound_play(ALLEGRO_SAMPLE *sound, const enable_t &en_sound) {
    if (en_sound == OFF) return;

    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

void music_wa_play() {
    al_play_sample(music_wa, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, nullptr);
}

asteroid_t generate_asteroid(const asteroid_special_t s, const int &next_p) {
	asteroid_t	asteroid;
	char	src[255], *c_num, *h_word;
	float	intervall_no_spawn = 180;
	int	rand_side, first_char;

    srand(clock());
    // Init raggio
	asteroid.radius = (float) 5 / 3 * (2.5 * display_info.width) / 100;
    // Init special
    asteroid.special = s;
    strcpy(src, "media/images/asteroids/");

    switch (s) {
        case NORMAL:
			strcat(src, "normal/ast.png");
            break;

        case ATOMIC:
			strcat(src, "atomic/ast.png");
            break;

        case RALLENTY:
			strcat(src, "rallenty/ast.png");
            break;

        case FIRE:
			strcat(src, "fire/ast.png");
            break;

        case SHIELD:
			strcat(src, "shield/ast.png");
    }

    asteroid.bmp = al_load_bitmap(src);
    assert(asteroid.bmp != nullptr);

    // Init coordinate
	rand_side = rand() % 4 + 1;
    switch (rand_side) {

        // Lato superiore
        case 1:
            do
                asteroid.x = rand() % (int) display_info.width;
            while (asteroid.x > display_info.width / 2 - intervall_no_spawn &&
                   asteroid.x < display_info.width / 2 + intervall_no_spawn);
            asteroid.y = 0 - 2 * asteroid.radius;
            break;

            // Lato destro
        case 2:
            asteroid.x = display_info.width + 2 * asteroid.radius;
            asteroid.y = rand() % (int) display_info.height;
            break;

            // Lato inferiore
        case 3:
            do
                asteroid.x = rand() % (int) display_info.width;
            while (asteroid.x > display_info.width / 2 - intervall_no_spawn &&
                   asteroid.x < display_info.width / 2 + intervall_no_spawn);
            asteroid.y = display_info.height + 2 * asteroid.radius;
            break;

            // Lato sinistro
        case 4:
            asteroid.x = 0 - 2 * asteroid.radius;
            asteroid.y = rand() % (int) display_info.height;
            break;

    }

    // Init slope
    asteroid.slope = atan((display_info.height / 2 - (asteroid.y + asteroid.radius)) /
                          (display_info.width / 2 - (asteroid.x + asteroid.radius)));

    // Init parola
	h_word = nullptr;
	first_char = next_p;

    while (h_word == nullptr) {
        h_word = get_random_word(first_char);
        if (first_char != 0) first_char++;
        if (first_char == N_QUEUES - 1 + 'A') first_char = 'A';
    }

    strcpy(asteroid.word, h_word);
    delete[] h_word;
    return asteroid;
}

void move_bullets(bullet_t *bullet, match_vars_t &match_vars, enable_t &en_sound) {
	int	i;

	for (i = 0; i < N_QUEUES; i++) {
        if (bullet[i].x == 0) continue;

        if (bullet[i].x < display_info.width / 2) {
            bullet[i].x -= 3 * cos(bullet[i].slope);
            bullet[i].y -= 3 * sin(bullet[i].slope);
        } else {
            bullet[i].x += 3 * cos(bullet[i].slope);
            bullet[i].y += 3 * sin(bullet[i].slope);
        }

		if (calculate_distance(match_vars.ast_queues[i]->asteroid.x,
							   bullet[i].x,
							   match_vars.ast_queues[i]->asteroid.y,
							   bullet[i].y,
							   match_vars.ast_queues[i]->asteroid.radius) <
            match_vars.ast_queues[i]->asteroid.radius + bullet[i].radius) {

            sound_play(match_vars.sound_exp, en_sound);
            al_destroy_bitmap(match_vars.ast_queues[i]->asteroid.bmp);
            update_bonus(match_vars.items, match_vars.ast_queues[i]->asteroid.special);
            match_vars.insert_asteroid_index = delete_asteroid(match_vars.ast_queues, i);
            init_bullet(bullet[i]);
        }
    }
}

void move_asteroids(asteroid_list *ast_queues, const int &extract_index) {
	int	i;

	for (i = 0; i < N_QUEUES; i++) {

		if (ast_queues[i] != nullptr) {

			if (ast_queues[i]->asteroid.x < display_info.width / 2) {
				ast_queues[i]->asteroid.x += cos(ast_queues[i]->asteroid.slope);
				ast_queues[i]->asteroid.y += sin(ast_queues[i]->asteroid.slope);

			} else {

				ast_queues[i]->asteroid.x -= cos(ast_queues[i]->asteroid.slope);
				ast_queues[i]->asteroid.y -= sin(ast_queues[i]->asteroid.slope);

			}
		}
	}
}

void move_shooter(shooter_t &shooter, const asteroid_list *ast_queues,
				  const int current_asteroid) {
	float	goal_slope, distanza;
	int	goal_quadrant;
	bool	senso_orario;

	// Se non deve puntare a nulla, ritorna
    if (current_asteroid == -1)
        return;

    // "ast" è una copia dell'asteroide interessato
    asteroid_t ast = ast_queues[current_asteroid]->asteroid;

    // "goal_quadrant" è il quadrante a cui appartiene l'asteroide interessato
	goal_quadrant = which_quadrant(ast.x, ast.y);

    // Offset quadrante.
    switch (goal_quadrant) {
        case 1:
            goal_slope = 0;
            break;
        case 2:
            goal_slope = 3 * M_PI_2;
            break;
        case 3:
            goal_slope = M_PI;
            break;
        case 4:
            goal_slope = M_PI_2;
            break;
    }

    // Aggiunta angolo asteroide
    if (goal_quadrant % 2 == 0)
        goal_slope += ast.slope;
    else
        goal_slope += M_PI_2 - (-ast.slope);

    // Se l'ha gia' raggiunto, ritorna...
    if (shooter.slope == goal_slope)
        return;
    // ...altrimenti, ruota.

    // Scelta via più breve:
	senso_orario = true;
	distanza = abs(goal_slope - shooter.slope);
    if (goal_slope > shooter.slope) {
        if (distanza >= M_PI) {
            senso_orario = false;
            distanza = 2 * M_PI - distanza;
        }
    } else {
        if (distanza < M_PI)
            senso_orario = false;
    }
    if (senso_orario)
        // Velocità proporzionata alla distanza
        shooter.slope += 0.1 * distanza / M_PI;
    else
        shooter.slope += 2 * M_PI - 0.1 * distanza / M_PI;

    // Aggiustamento: shooter.slope deve appartenere a [0, 2*M_PI]
    shooter.slope = fmod(shooter.slope, 2 * M_PI);

    // Margine d'errore
    if (abs(goal_slope - shooter.slope) < 0.05)
        shooter.slope = goal_slope;
}

bool check_gameover(asteroid_list *ast_queues, const shooter_t &shooter,
					const bullet_t *arr_bullet) {
    int	index_to_extract = closer_asteroid(ast_queues, arr_bullet, shooter);
    if (index_to_extract == -1) return false;

    return ast_queues[index_to_extract] != nullptr &&
           calculate_distance(ast_queues[index_to_extract]->asteroid.x,
                              shooter.x,
                              ast_queues[index_to_extract]->asteroid.y,
                              shooter.y,
                              ast_queues[index_to_extract]->asteroid.radius) <
           ast_queues[index_to_extract]->asteroid.radius + shooter.radius;
}

float check_distance(const asteroid_list *ast_queues, const bullet_t *arr_bullet, const shooter_t &shooter) {
    int	index_to_extract = closer_asteroid(ast_queues, arr_bullet, shooter);
    if (index_to_extract == -1) return false;

    float	distance = calculate_distance(ast_queues[index_to_extract]->asteroid.x, shooter.x,
                                        ast_queues[index_to_extract]->asteroid.y,
                                        shooter.y, ast_queues[index_to_extract]->asteroid.radius);

    return distance;
}

void check_shield(match_vars_t &match_vars, bullet_t *arr_bullet, shooter_t &shooter, enable_t &en_sound) {
    if (match_vars.gameover && al_get_timer_started(match_vars.timer_shield_bonus)) {

        match_vars.gameover = false;
        int index_to_extract = closer_asteroid(match_vars.ast_queues, arr_bullet, shooter);

        sound_play(match_vars.sound_exp, en_sound);
        al_destroy_bitmap(match_vars.ast_queues[index_to_extract]->asteroid.bmp);
        update_bonus(match_vars.items, match_vars.ast_queues[index_to_extract]->asteroid.special);
        match_vars.asteroid_to_generate = update_diff_score(match_vars, index_to_extract);
        match_vars.insert_asteroid_index = delete_asteroid(match_vars.ast_queues, index_to_extract);

        DEB2(int h = match_vars.insert_asteroid_index;
                     cout << "Indice del prossimo asteroide da generare: " << (h == -1 ? h : (char) (h + 'A')) << endl;)

    }
}

void handler_timer(ALLEGRO_EVENT ev, match_vars_t &match_vars, settings_t &settings) {
    if (ev.timer.source == match_vars.timer_shield_bonus) {
        al_stop_timer(match_vars.timer_shield_bonus);
        return;
    }

    if (ev.timer.source == match_vars.timer_rallenty_bonus) {
        match_vars.fps = 170;
        al_set_sample_instance_speed(match_vars.music_playwa, 1.0);
        al_stop_timer(match_vars.timer_rallenty_bonus);
        return;
    }

    if (ev.timer.source == match_vars.spawn_timer) {
        pthread_cond_signal(&thread_manager.spawn_cond);
        return;
    }
}

void handler_key_pressed(ALLEGRO_EVENT ev, match_vars_t &match_vars,
						 bullet_t *arr_bullet, shooter_t &shooter,
						 settings_t &settings) {
	int	index_to_extract;


    switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            change_enable(match_vars.playing);
            break;

        case ALLEGRO_KEY_F1: {
            if (match_vars.items[0] == 0) break;
            atomic_bonus(match_vars, arr_bullet, settings.sound);
            break;
        }

        case ALLEGRO_KEY_F2: {
            if (match_vars.items[1] == 0 || al_get_timer_started(match_vars.timer_rallenty_bonus)) break;
            al_start_timer(match_vars.timer_rallenty_bonus);
            match_vars.fps = 20;
            al_set_sample_instance_speed(match_vars.music_playwa, 0.5);
            match_vars.items[1]--;
            break;
        }

        case ALLEGRO_KEY_F3: {
            if (match_vars.items[2] == 0) break;
            fire_bonus(match_vars, arr_bullet, shooter, settings.sound);
            break;
        }

        case ALLEGRO_KEY_F4: {
            if (match_vars.items[3] == 0 || al_get_timer_started(match_vars.timer_shield_bonus)) break;
            al_start_timer(match_vars.timer_shield_bonus);
            match_vars.items[3]--;
            break;
        }

        case ALLEGRO_KEY_F8: {
            change_enable(settings.music);
            if (settings.music == ON) al_play_sample_instance(match_vars.music_playwa);
            else al_stop_sample_instance(match_vars.music_playwa);
            break;
        }

        case ALLEGRO_KEY_F9: {
            change_enable(settings.sound);
            break;
        }

        case ALLEGRO_KEY_LSHIFT:
        case ALLEGRO_KEY_RSHIFT:
            settings.visible_hints = !settings.visible_hints;

        default: {
            const char *value = al_keycode_to_name(ev.keyboard.keycode);
            if (char_key_handler(match_vars.ast_queues, value, match_vars.current_asteroid) && value[1] == '\0') {

				index_to_extract = match_vars.current_asteroid;
                assert(match_vars.ast_queues[index_to_extract] != nullptr);

                if (match_vars.ast_queues[index_to_extract]->asteroid.word[0] == '\0') {

                    sound_play(match_vars.sound_fire, settings.sound);
                    arr_bullet[index_to_extract] = generate_bullet(match_vars.ast_queues[index_to_extract]->asteroid,
                                                                   shooter);
                    match_vars.asteroid_to_generate = update_diff_score(match_vars, index_to_extract);
                }
            } else {
                match_vars.key_error = match_vars.current_asteroid;
                if (match_vars.key_error != -1) sound_play(match_vars.sound_error, settings.sound);
            }
        }
    }
}

void change_music(const char *path, const enable_t &music) {
    al_destroy_sample(music_wa);
    music_wa = al_load_sample(path);
    assert(music_wa != nullptr);

    if (music == ON)
        music_wa_play();
}
