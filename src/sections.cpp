#include <semaphore.h>
#include "sections.h"

// Private
/**
 *      Funzione che gestisce la schermata delle istruzioni del gioco nella pausa. \n
 *      Parametri: \n
 *      1) display - Display corrente; \n
 *      2) ev_queue - Coda degli eventi; \n
 *      3) settings - Struct contenente le impostazioni di gioco. \n
 *      4) prev_bg_offset - Posizione dello sfondo al momento del lancio della funzione. \n
 *      Ritorna false se si è usciti dal gioco.
 */
static bool
instructions(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue,
            enable_t &playing, settings_t &settings, float &prev_bg_offset) {
    ALLEGRO_BITMAP	**arr_bitmaps = generate_instr_bitmaps();
    ALLEGRO_FONT	**arr_fonts = generate_instr_fonts();
    char	*head_str;
    ALLEGRO_EVENT	ev;

    while (true) {
        // Stampa sfondo
        draw_background(arr_bitmaps[0], prev_bg_offset, 1);

        // Stampa titolo
        head_str = new char[255];
        strcpy(head_str, "Pausa");
        draw_head(head_str, arr_fonts[0]);
        delete[] head_str;

        // Stampa fondo nero
        al_draw_filled_rectangle(display_info.width / 32, display_info.height / 6,
                                 display_info.width - display_info.width / 32,
                                 display_info.height - display_info.height / 10,
                                 al_map_rgba_f(0, 0, 0, 0.4));

        // Stampa istruzioni
        draw_instructions(arr_fonts, arr_bitmaps);
        // Stampa back
        draw_back(arr_fonts[1], 1);
        // Aggiorna il display
        al_flip_display();
        if (!al_wait_for_event_timed(ev_queue, &ev, BG_REFRESH_TIME))
            continue;

        switch (ev.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (exit(display, true))
                    return false;

                // Evento da tastiera
            case ALLEGRO_EVENT_KEY_DOWN:
                if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    destroy_arr_bitmaps(arr_bitmaps, NUM_INSTR_BITMAPS);
                    destroy_arr_fonts(arr_fonts, NUM_INSTR_FONTS);
                    playing = ON;
                    return true;
                }
        }
    }
}

/**
 *      Funzione che gestisce la schermata delle istruzioni del gioco nella pausa. \n
 *      Parametri: \n
 *      1) display - Display corrente; \n
 *      2) ev_queue - Coda degli eventi; \n
 *      3) match_vars - Contenitore delle variabili di gioco; \n
 *      Ritorna nullptr se si è usciti dal gioco, altrimenti ritorna la stringa contenente l'username del giocatore \n
 *      che ha appena finito di giocare la partita.
 */
static void
draw_gameover(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue,
              const match_vars_t &match_vars) {
    float	bg_offset = 0;
    bool	bar_visible;
    ALLEGRO_FONT	**arr_fonts = generate_user_fonts();
    ALLEGRO_BITMAP	*bg_bmp = al_load_bitmap("media/images/bg_menu.png");
    assert(bg_bmp != nullptr);

    // Animazione gameover
    draw_gameover_animation(match_vars.score, match_vars.asteroids_destroyed,
                            bg_bmp, bg_offset, arr_fonts);

    // Lampeggiamento barra username
    bar_visible = false;
    ALLEGRO_TIMER *bar_timer = al_create_timer(0.5);
    al_register_event_source(ev_queue, al_get_timer_event_source(bar_timer));
    al_start_timer(bar_timer);

    while (true) {
        // Stampa sfondo
        char	*head_str = new char[255];
        draw_background(bg_bmp, bg_offset, 0);
        strcpy(head_str, "Gameover");
        draw_head(head_str, arr_fonts[1]);
        // delete[] head_str;

        // Stampa stats
        draw_stats_blocks(arr_fonts[2]);
        draw_stat(0, match_vars.score, arr_fonts[2]);
        draw_stat(1, match_vars.asteroids_destroyed, arr_fonts[2]);
        draw_results(arr_fonts[0], thread_manager.search_manager.res);
        draw_playagain_button(arr_fonts[0]);
        al_flip_display();

        ALLEGRO_EVENT ev;
        if (!al_wait_for_event_timed(ev_queue, &ev, BG_REFRESH_TIME))
            continue;

        switch (ev.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (exit(display, true))
                    return;
                break;

            case ALLEGRO_EVENT_TIMER:
                bar_visible = !bar_visible;
                break;

                // Evento da tastiera
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (ev.keyboard.keycode) {
                    // sx e/o dx per vedere le password

                    case ALLEGRO_KEY_ENTER:
                        destroy_arr_fonts(arr_fonts, NUM_USER_FONTS);
                        al_destroy_bitmap(bg_bmp);
                        al_destroy_timer(bar_timer);
                        return;
                }
                break;
        }
    }
}

/**
 *      Funzione che gestisce la schermata di richiesta della email da ricercare negli archivi. \n
 *      Parametri: \n
 *      1) display - Display corrente; \n
 *      2) ev_queue - Coda degli eventi; \n
 *      3) settings - Struct contenente le impostazioni di gioco. \n
 *      Ritorna la mail inserita dall'utente.
 */
static char *
ask_email(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue,
          settings_t &settings) {

    ALLEGRO_FONT	**arr_fonts = generate_user_fonts();
    ALLEGRO_BITMAP	*bg_bmp = al_load_bitmap("media/images/bg_menu.png");
    assert(bg_bmp != nullptr);
    char *username, *head_str;
    float bg_offset;
    bool bar_visible;
    int cur_pos;

    username = new char[MAX_USERNAME_LENGTH];
    bg_offset = 0;

    // Lampeggiamento barra username
    bar_visible = false;
    ALLEGRO_TIMER *bar_timer = al_create_timer(0.5);
    al_register_event_source(event_queue, al_get_timer_event_source(bar_timer));
    al_start_timer(bar_timer);
    cur_pos = 0;

    while (true) {

        // Stampa sfondo
        draw_background(bg_bmp, bg_offset, 0);

        // Stampa titolo
        head_str = new char[255];
        strcpy(head_str, "inserisci la tua email");
        draw_head(head_str, arr_fonts[1]);
        delete[] head_str;

        // Stampa username
        draw_username_block(cur_pos > 0, arr_fonts[0]);
        draw_username(username, cur_pos, arr_fonts[0], bar_visible);

        al_flip_display();

        ALLEGRO_EVENT ev;
        if (!al_wait_for_event_timed(event_queue, &ev, BG_REFRESH_TIME))
            continue;

        switch (ev.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (exit(display, true))
                    return nullptr;
                break;

            case ALLEGRO_EVENT_TIMER:
                bar_visible = !bar_visible;
                break;

                // Evento da tastiera
            case ALLEGRO_EVENT_KEY_CHAR:
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_BACKSPACE:
                        username[cur_pos] = '\0';
                        if (cur_pos == 0) break;
                        cur_pos--;
                        username[cur_pos] = '\0';
                        break;

                    case ALLEGRO_KEY_ENTER:
                        if (cur_pos == 0) break; // Non può tornare stringa vuota
                        username[cur_pos] = '\0';
                        destroy_arr_fonts(arr_fonts, NUM_USER_FONTS);
                        al_destroy_bitmap(bg_bmp);
                        al_destroy_timer(bar_timer);
                        return username;

                    default: {
                        char unichar = (char) ev.keyboard.unichar;
                        if (cur_pos == MAX_USERNAME_LENGTH - 1 || ev.keyboard.unichar > 128) break;
                        username[cur_pos] = unichar;
                        cur_pos++;
                        break;
                    }
                }
                break;
        }
    }
}

/*********/

// Public

float intro(ALLEGRO_DISPLAY *display) {
    // Inizializzazione bitmaps, e ripresa del controllo da parte del display
    ALLEGRO_BITMAP	**arr_bitmaps = generate_menu_bitmaps();
    ALLEGRO_FONT	**arr_fonts = generate_menu_fonts();
    float bg_offset;

    al_set_target_bitmap(al_get_backbuffer(display));

    // Init offset per rotazione sfondo
    bg_offset = 0;

    // Transizione titolo: posizione iniziale
    draw_intro_init(arr_bitmaps, bg_offset);

    // Transizione titolo: slide fino a MENU_GV.UPPER_OFFSET
    draw_intro_title_slide(arr_bitmaps, bg_offset);

    // Transizione opzioni: fadein, fino ad opacità 255
    draw_intro_menu_fadein(arr_bitmaps, arr_fonts, bg_offset);

    // Deallocazione bitmap
    destroy_arr_bitmaps(arr_bitmaps, NUM_MENU_BITMAPS);

    // Deallocazione font
    destroy_arr_fonts(arr_fonts, NUM_MENU_FONTS);

    return bg_offset;
}

int main_menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue,
              const float &prev_bg_offset) {
    // Inizializzazione bitmaps (menu)
    ALLEGRO_BITMAP	**arr_bitmaps = generate_menu_bitmaps();
    ALLEGRO_FONT	**arr_fonts = generate_menu_fonts();
    int i, scelta = 0;
    char arr_scelte[][255] = {
            "Gioca",
            "Impostazioni",
            "Esci"
    };
    float bg_offset = prev_bg_offset;
    bool done = false;

    // Ripresa di controllo da parte del bitmap "display"
    al_set_target_bitmap(al_get_backbuffer(display));
    while (!done) {
        // Stampa sfondo
        draw_background(arr_bitmaps[3], bg_offset, 0);
        // Stampa titolo
        draw_menu_title(arr_bitmaps[0]);

        // Stampa opzioni
        for (i = 0; i < NUM_OPTIONS; i++) {
            // Selezione bitmap option
            ALLEGRO_BITMAP *bmp_option;
            if (i == scelta)
                bmp_option = arr_bitmaps[1];
            else
                bmp_option = arr_bitmaps[2];

            // Stampa opzione i-esima
            draw_menu_option(i, bmp_option, arr_fonts[0], arr_scelte[i], 0);
        }
        // Stampa scritta copyright
        draw_menu_copyright(arr_fonts[1]);
        // Aggiornamento display
        al_flip_display();
        ALLEGRO_EVENT event;
        if (!al_wait_for_event_timed(ev_queue, &event, BG_REFRESH_TIME))
            continue;

        switch (event.type) {
            // X
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (exit(display, false))
                    return NUM_OPTIONS - 1;
                break;
                // Evento da tastiera
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {

                    case ALLEGRO_KEY_ENTER:
                        done = true;
                        break;

                    case ALLEGRO_KEY_DOWN:
                        scelta++;
                        if (scelta == NUM_OPTIONS)
                            scelta = 0;
                        break;

                    case ALLEGRO_KEY_UP:
                        scelta--;
                        if (scelta == -1)
                            scelta = NUM_OPTIONS - 1;
                        break;

                }
                break;
        }
    }
    destroy_arr_bitmaps(arr_bitmaps, NUM_MENU_BITMAPS);
    destroy_arr_fonts(arr_fonts, NUM_MENU_FONTS);
    return scelta;
}

bool settings_menu(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue,
    			   settings_t &settings) {

    // Inizializzazione bitmaps (menu)
    ALLEGRO_BITMAP	**arr_bitmaps = generate_menu_bitmaps();
    ALLEGRO_FONT	**arr_fonts = generate_settings_fonts();

    // Ripresa di controllo da parte del bitmap "display"
    al_set_target_bitmap(al_get_backbuffer(display));
    int i, scelta = 0;
    char *head_str, arr_scelte[][255] = {
            "Musica: ",
            "Suoni: ",
            "Torna al menu principale"
    };
    float bg_offset = 0;
    bool done = false;

    while (!done) {
        // Stampa sfondo
        draw_background(arr_bitmaps[3], bg_offset, 0);

        // Stampa titolo
    	head_str = new char[255];
        strcpy(head_str, "Impostazioni");
        draw_head(head_str, arr_fonts[0]);
        delete[] head_str;

        // Stampa opzioni
        for (i = 0; i < NUM_OPTIONS_SETTINGS; i++) {

            // Selezione bitmap option
            ALLEGRO_BITMAP *bmp_option;
            if (i == scelta)
                bmp_option = arr_bitmaps[1];
            else
                bmp_option = arr_bitmaps[2];

            // Concatena il contenuto di "settings" alle opzioni
            char testo_scelta[255];
            strcpy(testo_scelta, arr_scelte[i]);
            switch (i) {
                case 0:
                    strcat(testo_scelta, settings.music == ON ? "ON" : "OFF");
                    break;

                case 1:
                    strcat(testo_scelta, settings.sound == ON ? "ON" : "OFF");
                    break;
            }

            // Stampa opzione i-esima
            draw_menu_option(i, bmp_option, arr_fonts[1], testo_scelta, 1);
        }

        // Stampa scritta copyright
        draw_menu_copyright(arr_fonts[2]);
        // Aggiornamento display
        al_flip_display();
        ALLEGRO_EVENT event;
        if (!al_wait_for_event_timed(ev_queue, &event, BG_REFRESH_TIME))
            continue;

        switch (event.type) {
            // X
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (exit(display, false))
                    return false;
                break;
                // Evento da tastiera
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {

                    case ALLEGRO_KEY_ENTER:
                        switch (scelta) {
                            case 0:
                                change_enable(settings.music);
                                if (settings.music == ON) music_wa_play();
                                else al_stop_samples();
                                break;

                            case 1:
                                change_enable(settings.sound);
                                break;

                            case 3:
                            default:
                                done = true;

                        }
                        break;

                    case ALLEGRO_KEY_DOWN:
                        scelta++;
                        if (scelta == NUM_OPTIONS_SETTINGS)
                            scelta = 0;
                        break;

                    case ALLEGRO_KEY_UP:
                        scelta--;
                        if (scelta == -1)
                            scelta = NUM_OPTIONS_SETTINGS - 1;
                        break;

                    case ALLEGRO_KEY_LEFT:
                    case ALLEGRO_KEY_RIGHT:
                        switch (scelta) {
                            case 0:
                                change_enable(settings.music);
                                if (settings.music == ON) music_wa_play();
                                else al_stop_samples();
                                break;

                            case 1:
                                change_enable(settings.sound);
                                break;

                            case 2:
                            default:
                                done = true;
                        }
                }
                break;
        }
    }
    destroy_arr_bitmaps(arr_bitmaps, NUM_MENU_BITMAPS);
    destroy_arr_fonts(arr_fonts, NUM_SETTINGS_FONTS);
    return true;
}

bool play_wa(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue,
             settings_t &settings) {

    ALLEGRO_BITMAP	**arr_bitmaps = generate_playwa_bitmaps();
    ALLEGRO_FONT	**arr_fonts = generate_playwa_fonts();
    match_vars_t	match_vars;
    shooter_t	shooter;
    float	bg_offset = 0;
    bool	start = false;
    bullet_t	arr_bullet[N_QUEUES];

    char *email = ask_email(display, ev_queue, settings);

    // Setto il sample del play_wa, ma non uso la musica per lo stoppo subito
    change_music(MUSIC_PLAYWA_PATH_WA, settings.music);
    al_stop_samples();

    // Ripresa di controllo da parte del bitmap "display".
    al_set_target_bitmap(al_get_backbuffer(display));

    // Inizializzazione variabili di gioco
    init_match_vars(match_vars, ev_queue);

    // Play della musica
    if (settings.music == ON)
        al_set_sample_instance_playing(match_vars.music_playwa, true);

    // Inizializzaione shooter
    init_shooter(shooter);

    // Inizializzazione proiettili
    init_arr_bullet(arr_bullet);

    init_words_buffer(words_buffer);
    /* Inizializzazione dei Thread e avvio della ricerca*/
    /* Inizializzazione delle strutture per la ricerca negli archivi */
    init_thread_manager(thread_manager, email);
    pthread_create(&thread_manager.searcher_thread, nullptr,
    			   start_searching, (void *) &thread_manager.search_manager);
    pthread_create(&thread_manager.spawner_thread, nullptr,
    			   spawn_asteroid_thread, (void *) &match_vars);
    al_start_timer(match_vars.spawn_timer);

    while (!match_vars.gameover) {

        // Controllo pausa
        if (match_vars.playing == OFF &&
            !instructions(display, ev_queue, match_vars.playing, settings, bg_offset))
            return false;

        // Movimento asteroidi, proiettili e shooter
        move_asteroids(match_vars.ast_queues, match_vars.insert_asteroid_index);
        move_bullets(arr_bullet, match_vars, settings.sound);
        move_shooter(shooter, match_vars.ast_queues, match_vars.current_asteroid);

        // Controllo gameover
        match_vars.gameover = check_gameover(match_vars.ast_queues, shooter, arr_bullet);

        // Controllo se ho lo scudo e se c'è stato gameover, in quel caso devo distruggere l'asteroide
        // che ha toccato lo scudo, che è l'asteroide più vicino
        check_shield(match_vars, arr_bullet, shooter, settings.sound);

        // Stampe
        draw_background(arr_bitmaps[8], bg_offset, true);
        draw_playwa_asteroids_bullets(match_vars, arr_bullet,
                                      arr_bitmaps, arr_fonts[2]);
        draw_playwa_score_hint(match_vars, arr_fonts[0], arr_fonts[1],
                               settings.visible_hints);
        draw_playwa_shooter(match_vars, arr_bullet, shooter, arr_bitmaps);
        draw_playwa_bonus_music(match_vars, arr_bitmaps, arr_fonts[0],
                                arr_fonts[3], arr_fonts[4], settings);
        al_flip_display();

        if (match_vars.gameover) {
            al_stop_samples();
            sound_play(match_vars.sound_gameover, settings.sound);
            al_rest(1.0);
            break;
        }

        ALLEGRO_EVENT ev;
        if (!al_wait_for_event_timed(ev_queue, &ev, 1.0 / match_vars.fps))
            continue;

        switch (ev.type) {
            // X
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                if (exit(display, true))
                    return false;
                change_enable(match_vars.playing);
                break;

                // Evento da timer - crea un asteroide ogni N secondi
                // PERIODIC TASK
            case ALLEGRO_EVENT_TIMER:
                handler_timer(ev, match_vars, settings);
                break;

                // Evento da tastiera
            case ALLEGRO_EVENT_KEY_DOWN:
                handler_key_pressed(ev, match_vars, arr_bullet, shooter, settings);
                break;

            case ALLEGRO_EVENT_KEY_UP:
                if (match_vars.key_error != -1)
                    match_vars.key_error = -1;
                break;
        }
        if (!start) {
            sem_wait(&thread_manager.consumer_sem);
            start = true;
        }
        pthread_cond_broadcast(&thread_manager.gameover_cond);
    }

    // Sign term ai thread per completare
    pthread_cancel(thread_manager.spawner_thread);
    pthread_join(thread_manager.spawner_thread, nullptr);
    pthread_cancel(thread_manager.searcher_thread);
    pthread_join(thread_manager.searcher_thread, nullptr);

    // Dealloca i timer, gli asteroidi rimasti, le immagini e svuota la coda degli eventi
    delete_ast_queues(match_vars.ast_queues);
    delete_timer(match_vars);
    delete_sounds(match_vars);
    destroy_arr_fonts(arr_fonts, NUM_PLAYWA_FONTS);
    destroy_arr_bitmaps(arr_bitmaps, NUM_PLAYWA_BITMAPS);
    al_flush_event_queue(ev_queue);
    change_music(MUSIC_GAMEOVER_PATH_WA, settings.music);

    // Schermata di fine partita
    draw_gameover(display, ev_queue, match_vars);
    al_stop_samples();
    return true;
}


