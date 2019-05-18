//
// Created by corra on 30/03/19.
//

#ifndef DECOMPRESSTEST_UNCOMPRESS_H
#define DECOMPRESSTEST_UNCOMPRESS_H

#include "data.h"

extern thread_manager_t	thread_manager;
extern words_buffer_t	words_buffer;

/**
 *      Funzione che gestire i thread searcher e worker. \n
 *      Questi thread gestiscono la ricerca dell'email dello username all'interno delle collection. \n
 *      Parametri: \n
 *      1) search_manager - Variabile contenente le strutture per la sincronizzazione la ricerca.
 */
void *start_searching(void *search_manager);

#endif //DECOMPRESSTEST_UNCOMPRESS_H
