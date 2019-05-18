#include "init.h"
#include "graphical_values.h"
#include "game_functions.h"
#include "sections.h"

#include <iostream>
#include <cassert>

using namespace std;

display_info_t 	display_info;
ALLEGRO_SAMPLE 	*music_wa = nullptr;
thread_manager_t	thread_manager;
words_buffer_t 	words_buffer;

int main(int argc, char **argv){
	// Inizializzaione display
	ALLEGRO_DISPLAY	*display = nullptr;
	settings_t 	settings;
	float 	prev_bg_offset = 3;
	int 	choose = -1;
	bool 	exit_wa = false;

    assert(al_init() && archives_exist());
    // Inizializzazione periferiche di gioco
    if(!init_game_requirements()){
		al_show_native_message_box(nullptr, "Errore", "Word Asteroid",
								   "Si è verificato un errore nell'inizializzazione delle periferiche di gioco.",
								   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

	/**
	 * Inizializzazione dimensioni display, e aggiornamento proporzioni grafiche
	 * Inizializzazione della coda degli eventi e delle impostazioni
	 * Inizializzione e avvio della musica
	 */
    display_info = init_display_res();
	display = al_create_display(display_info.width, display_info.height);
    al_set_window_title(display, "Word Asteroid");
	ALLEGRO_EVENT_QUEUE *event_queue = init_queue_event(display);
	assert(event_queue != nullptr);
    music_wa = init_sound_music(MUSIC_MENU_PATH_WA);
    music_wa_play();
	init_settings(settings);
	update_graphical_values();

	if (!display) {
		al_show_native_message_box(display, "Errore", "Word Asteroid",
								   "Si è verificato un errore nel caricamento del display principale.",
								   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

    // Animazione di introduzione
    intro(display);
	while(!exit_wa){

		if (choose == 0 && settings.music == ON) {
            music_wa = init_sound_music(MUSIC_MENU_PATH_WA);
            music_wa_play();
		}

		choose = main_menu(display, event_queue, prev_bg_offset);
        switch(choose){
            case 0:
                if(!play_wa(display, event_queue, settings)) exit_wa = true;
                break;

            case 1:
                if(!settings_menu(display, event_queue, settings)) exit_wa = true;
                break;

            case 2:
            default:
                exit_wa = true;
        }
    }

	// Deallocazione display, coda degli eventi e musica
	delete_display_evqueue_music(display, event_queue, music_wa);
    DEB1(cout<<"--- USCITA ---"<<endl;)
    
	return 0;
}
