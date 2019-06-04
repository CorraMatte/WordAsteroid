#include <dirent.h>
#include "utilities.h"

// Private
/**
 *      Funzione che verifica il formato del file passato in input.\n
 *      Parametri:\n
 *      1) filename - file in input da verificare l'estensione.\n
 *      Ritorna true se il file ha estensione .tar.gz, false altrimenti.
 */
static bool is_targz(const char *filename) {
    const char s[2] = ".";
    char *token, *gz, fn[strlen(filename)];

    strcpy(fn, filename);
    token = strtok(fn, s);

    while (true) {
        while (token != nullptr && strcmp(token, "tar") != 0) {
            token = strtok(nullptr, s);
        }

        if (token == nullptr) {
            return false;
        }

        gz = strtok(nullptr, s);
        if (strcmp(gz, "gz") == 0 && (token = strtok(nullptr, s)) == nullptr)
            return true;
    }
}

// Public
bool exit(ALLEGRO_DISPLAY * display, const bool playing){
    return al_show_native_message_box(display,
                                    "Vuoi davvero uscire?", "Word asteroid",
                                    playing
                                    ? "Attenzione: cliccando su \"Yes\" perderai tutti i progressi della partita corrente."
                                      : "",
                                      nullptr, ALLEGRO_MESSAGEBOX_YES_NO) == 1;
}


char* int_to_str_score(const int & match_score){
    stringstream ss;
    string score;
    char *score_ptr;

    ss << setfill('0') << setw(MAX_DIGIT_SCORE) << match_score;
    ss >> score;
    score_ptr = new char[MAX_DIGIT_SCORE + 1];
    strcpy(score_ptr, score.c_str());

    return score_ptr;
}

int which_quadrant(const float x, const float y){
    if(y < display_info.height/2)
        if(x > display_info.width/2)
            return 1;
        else
            return 2;
    else if(x < display_info.width/2)
        return 3;
    else
        return 4;
}

void extract_elem(asteroid_list* ast_queues, const int& index_to_extract){
    asteroid_list h = ast_queues[index_to_extract]->next;
    assert(ast_queues[index_to_extract] != nullptr);
    delete[] ast_queues[index_to_extract];
    ast_queues[index_to_extract] = h;
}

int insert_elem_head(asteroid_list* ast_queues, const asteroid_t& asteroid){
    int index_to_insert;
    elem_asteroid_t *p;

    index_to_insert = asteroid.word[0] - 'A';
    elem_asteroid_t * h = ast_queues[index_to_insert];
    p = new elem_asteroid_t;
    p->asteroid = asteroid;
    p->next = nullptr;

    if (h == nullptr) {
        ast_queues[index_to_insert] = p;
        return -1;
    }

    while (h->next != nullptr)
        h = h->next;
    h->next = p;

    return index_to_insert+1;
}

void change_enable(enable_t& enabled){
    if(enabled == ON)
        enabled = OFF;
    else
        enabled = ON;
}


void delete_ast_queues(asteroid_list* ast_queues){
    int i;
    for (i = 0; i < N_QUEUES; i++)
        while (ast_queues[i] != nullptr) {
            al_destroy_bitmap(ast_queues[i]->asteroid.bmp);
            extract_elem(ast_queues, i);
        }
}

void delete_timer(match_vars_t& match_vars){
    al_destroy_timer(match_vars.spawn_timer);
    al_destroy_timer(match_vars.timer_shield_bonus);
    al_destroy_timer(match_vars.timer_rallenty_bonus);
}

void delete_display_evqueue_music(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *ev_queue, ALLEGRO_SAMPLE* sound){
    al_destroy_display(display);
    al_destroy_event_queue(ev_queue);
    al_destroy_sample(sound);
}

void delete_sounds(match_vars_t& match_vars){
    al_destroy_sample(match_vars.sound_exp);
    al_destroy_sample(match_vars.sound_fire);
    al_destroy_sample(match_vars.sound_gameover);
    al_destroy_sample(match_vars.sound_error);
    al_destroy_sample_instance(match_vars.music_playwa);
}

bool ls_tar(ls_t *ls) {
    DIR *dp;
    FILE *f;
    struct dirent *dentry;
    char *filename;
    file_t file;

    ls->nfile = 0;
    if (!(dp = opendir(COLLECTION_FOLDER))) {
        return false;
    }
    while ((dentry = readdir(dp))) {
        if (is_targz(dentry->d_name)) {
            ls->nfile++;
        }
    }

    ls->files = new file_t[ls->nfile];
    rewinddir(dp);
    (*ls).nfile = 0;
    dentry = readdir(dp);

    while (dentry != nullptr) {
        if (is_targz(dentry->d_name)) {
            filename = new char[strlen(COLLECTION_FOLDER) +
                                strlen(dentry->d_name) + 1];
            strcpy(filename, COLLECTION_FOLDER);
            filename = strcat(filename, dentry->d_name);
            file.filename = filename;
            f = fopen(filename, "r");
            fseek(f, 0, SEEK_END);
            file.size = ftell(f);
            fclose(f);
            ls->files[ls->nfile] = file;
            ls->nfile++;
        }
        dentry = readdir(dp);
    }

    closedir(dp);
    return true;
}

bool archives_exist() {
    struct stat info;
    if (stat(COLLECTION_FOLDER, &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR) {
        ls_t ls;
        return (ls_tar(&ls) && ls.nfile > 1);
    }
    else
        return false;
}