#include "init.h"



// Private

/**
 *      Funzione che inizializza i requisiti di Allegro riguardanti lo schermo.
 */
static void init_monitor_requirements(){
    al_init_image_addon();
    al_init_primitives_addon();
}

/**
 *      Funzione che ordina un array di elementi che rappresentano gli archivi in ordine crescente
 *      in base alla loro dimensione. \n
 *      Parametri: \n
 *      1) file_list - Lista degli archivi; \n
 */
void sort_file_list(ls_t *file_list) {
    file_t	temp;
    int i, j;

    for (i = 0; i < file_list->nfile; i++)
        for (int j = 0; j < file_list->nfile - 1; j++)
            if (file_list->files[j].size < file_list->files[j + 1].size) {
                temp = file_list->files[j];
                file_list->files[j] = file_list->files[j + 1];
                file_list->files[j + 1] = temp;
            }
}

/**
 *      Funzione che inizializza un array di archivi ordinati. \n
 * 		Ritorna un puntatore all'array di file, o nulllptr in caso di errori.
 */
static ls_t *init_file_list() {
    ls_t 	*file_list = new ls_t;
    if (!ls_tar(file_list)) {
        return nullptr;
    }
    sort_file_list(file_list);

    return file_list;
}

//**********

// Public

bool init_game_requirements(){
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();     
    if(!al_install_audio())				return false;
    if(!al_init_acodec_addon())			return false;
    if(!al_reserve_samples(6))			return false;
    // Installo e controllo se esiste la tastiera
    if (!al_install_keyboard())			return false;
    if (!al_is_keyboard_installed())	return false;
    return true;
}

display_info_t init_display_res(){
    ALLEGRO_MONITOR_INFO 	monitor_info;
    int 	monitor_w, monitor_h, offset_w, offset_h;
    float 	display_h, display_w;
    display_info_t	D;

    init_monitor_requirements();
    al_get_monitor_info(0, &monitor_info);
    monitor_w = monitor_info.x2 - monitor_info.x1;
    monitor_h = monitor_info.y2 - monitor_info.y1;
    offset_w = monitor_w / MONITOR_OFFSET_RATE;

    for(int offset_idx = MONITOR_OFFSET_RATE; offset_idx>0; offset_idx--){
        offset_h = monitor_h / offset_idx;
        display_h = monitor_h - offset_h;
        display_w = (float)(display_h / GAMERES_H) * GAMERES_W;
        if(display_w <= monitor_w - offset_w)
            break;
    }

    D = {display_w, display_h};
    return D;
};

ALLEGRO_EVENT_QUEUE* init_queue_event(ALLEGRO_DISPLAY * & display){
    // Creo la code degli eventi
    ALLEGRO_EVENT_QUEUE 	*event_queue = al_create_event_queue();
    if (!event_queue) return nullptr;

    // Associo il display e la tastiera agli eventi
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    return event_queue;
}

int init_target_bonus(int& instant_ast_dest, const int& asteroids_destroyed){
    srand(time(nullptr));
    instant_ast_dest = asteroids_destroyed;

    return (rand() % 5) + 5;
}

ALLEGRO_SAMPLE* init_sound_music(const char* path){
    ALLEGRO_SAMPLE	*sound = al_load_sample(path);
    assert(sound != nullptr);

    return sound;
}

void init_match_vars(match_vars_t& match_vars, ALLEGRO_EVENT_QUEUE * ev_queue){
    int	i;
    for (i = 0; i < N_QUEUES; i++)
        match_vars.ast_queues[i] = nullptr;

    match_vars.score = 0;
    match_vars.asteroids_destroyed = 0;
    match_vars.spawn_interval = 2.7;
    match_vars.spawn_timer = al_create_timer(match_vars.spawn_interval);
    match_vars.timer_shield_bonus = al_create_timer(TIMER_SHIELD_BONUS);
    match_vars.timer_rallenty_bonus = al_create_timer(TIMER_RALLENTY_BONUS);
    al_register_event_source(ev_queue, al_get_timer_event_source(match_vars.spawn_timer));
    al_register_event_source(ev_queue, al_get_timer_event_source(match_vars.timer_shield_bonus));
    al_register_event_source(ev_queue, al_get_timer_event_source(match_vars.timer_rallenty_bonus));
    match_vars.fps = 5000;
    match_vars.insert_asteroid_index = -1;
    match_vars.asteroid_head = 1;
    match_vars.asteroid_to_generate = NORMAL;
    match_vars.sound_exp = init_sound_music(SOUND_PATH_EXPLOSION);
    match_vars.sound_fire = init_sound_music(SOUND_PATH_FIRE);
    match_vars.sound_gameover = init_sound_music(SOUND_PATH_GAMEOVER);
    match_vars.sound_error = init_sound_music(SOUND_PATH_ERROR);
    match_vars.music_playwa = al_create_sample_instance(music_wa);
    al_attach_sample_instance_to_mixer(match_vars.music_playwa, al_get_default_mixer());
    al_set_sample_instance_playmode(match_vars.music_playwa, ALLEGRO_PLAYMODE_LOOP);
    match_vars.current_asteroid = -1;
    match_vars.key_error = -1;
    match_vars.playing = ON;
    match_vars.gameover = false;

    for (i = 0; i < NUM_ITEMS; i++) match_vars.items[i] = 1;
    match_vars.asteroid_to_bonus = init_target_bonus(match_vars.instant_ast_dest, match_vars.asteroids_destroyed);
    match_vars.instant_ast_dest = 0;
}

void init_settings(settings_t& settings){
    settings.sound = ON;
    settings.music = ON;
    settings.visible_hints = true;
}

void init_shooter(shooter_t& shooter){
    shooter.x = display_info.width/2;
    shooter.y = display_info.height/2;
    shooter.slope = 0;
    shooter.radius = PLAYWA_GV.SHOOTER_AREA_RAD;
}

void init_bullet(bullet_t& bullet){
    bullet.x = 0;
    bullet.y = 0;
    bullet.slope = 0;
    bullet.radius = PLAYWA_GV.BULLET_RADIUS;
}

void init_arr_bullet(bullet_t * arr_bullet){
    int	i;
    for (i = 0; i < N_QUEUES; i++)
        init_bullet(arr_bullet[i]);
}

void init_words_buffer(words_buffer_t &words_buffer) {
    words_buffer.load = 0;
}

void init_thread_manager(thread_manager_t &thread_manager, char *email) {
    pthread_condattr_t cond_attr;
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_condattr_init(&cond_attr);

    sem_init(&thread_manager.consumer_sem, 0, 0);
    sem_init(&thread_manager.searcher_sem, 0, 0);

    pthread_cond_init(&thread_manager.spawn_cond, &cond_attr);
    pthread_cond_init(&thread_manager.gameover_cond, &cond_attr);
    pthread_mutex_init(&thread_manager.spawn_mutex, &mutex_attr);
    pthread_mutex_init(&thread_manager.gameover_mutex, &mutex_attr);
    pthread_mutex_init(&thread_manager.search_result_mutex, &mutex_attr);
    pthread_mutex_init(&thread_manager.words_buffer_mutex, &mutex_attr);

    pthread_condattr_destroy(&cond_attr);
    pthread_mutexattr_destroy(&mutex_attr);
    thread_manager.search_manager.file_list = init_file_list();
    assert(thread_manager.search_manager.file_list != nullptr);
    thread_manager.search_manager.email = email;
    thread_manager.search_manager.res.count_result = 0;
}