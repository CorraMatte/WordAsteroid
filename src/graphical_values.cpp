#include "graphical_values.h"

/** Struct contenente le proporzioni grafiche generali. */
general_gv_t GENERAL_GV;
/** Struct contenente le proporzioni grafiche dei menu. */
menu_gv_t MENU_GV;
/** Struct contenente le proporzioni grafiche della schermata di gioco. */
playwa_gv_t PLAYWA_GV;
/** Struct contenente le proporzioni grafiche della schermata di pausa. */
instr_gv_t INSTR_GV;
/** Struct contenente le proporzioni grafiche della schermata di fine partita. */
usr_gv_t USR_GV;

void update_graphical_values(){
    // Aggiornamento proporzioni grafiche generali
    GENERAL_GV.HEAD_TOP_OFFSET = (1 * display_info.height) / 24;
    GENERAL_GV.HEAD_TEXT_SHADOW_GAP = (1 * display_info.width) / 600;
    GENERAL_GV.BACK_TOP_OFFSET = (13 * display_info.height) / 14;
    GENERAL_GV.BACK_LEFT_OFFSET = (1 * display_info.height) / 20;
    GENERAL_GV.BACK_TEXT_SHADOW_GAP = (1 * display_info.width) / 600;
    GENERAL_GV.HEAD_FONTSIZE = (1 * display_info.height) / 10;
    GENERAL_GV.BACK_FONTSIZE = (1 * display_info.height) / 23;
    GENERAL_GV.RESULT_TOP_OFFSET = (3 * display_info.height) / 7;

    // Aggiornamento proporzioni grafiche menu
    MENU_GV.TITLE_W = (27 * display_info.width) / 32;
    MENU_GV.TITLE_H = (63 * display_info.height) / 192;
    MENU_GV.OPTION_W = (2 * display_info.width) / 5;
    MENU_GV.OPTION_H = (3 * display_info.height) / 40;
    MENU_GV.OPTION_FONTSIZE = (1 * display_info.height) / 27;
    MENU_GV.OPTION_TEXT_OFFSET = (11 * MENU_GV.OPTION_FONTSIZE) / 20;
    MENU_GV.UPPER_OFFSET = (1 * display_info.height) / 15;
    MENU_GV.INTERNAL_OFFSET = (1 * display_info.height) / 50;
    MENU_GV.COPYRIGHT_FONTSIZE = (3 * MENU_GV.OPTION_FONTSIZE) / 5;
    MENU_GV.COPYRIGHT_TOP_OFFSET = display_info.height - (3 * MENU_GV.COPYRIGHT_FONTSIZE) / 2;
    
    // Aggiornamento proporzioni grafiche playwa
    PLAYWA_GV.TEXT_INTERNAL_OFFSET = (1 * display_info.height) / 21;
    PLAYWA_GV.SCORE_TOP_OFFSET = (1 * display_info.height) / 50;
    PLAYWA_GV.SCORE_LEFT_OFFSET = (display_info.width - PLAYWA_GV.SCORE_TOP_OFFSET);
    PLAYWA_GV.HINT_TOP_OFFSET = (11 * display_info.height) / 12;
    PLAYWA_GV.HINT_LEFT_OFFSET = PLAYWA_GV.SCORE_LEFT_OFFSET;
    PLAYWA_GV.SHOOTER_AREA_RAD = (1 * display_info.height) / 8;
    PLAYWA_GV.SHOOTER_SCALE = (1 * display_info.height) / 3250;
    PLAYWA_GV.ASTEROID_SHADOW_GAP = (1 * display_info.height) / 350;
    PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP = (1 * display_info.width) / 700;
    PLAYWA_GV.BULLET_RADIUS = (1 * display_info.height) / 45;
    PLAYWA_GV.HEIGHT_BONUS = (2 * display_info.height) / 33;
    PLAYWA_GV.BONUS_TOP_OFFSET = (1 * display_info.height) / 13;
    PLAYWA_GV.BONUS_LEFT_OFFSET = (1 * display_info.width) / 11;
    PLAYWA_GV.BULLET_SCALE = (1 * display_info.width) / 1700;
    PLAYWA_GV.DANGER_RADIUS = (2 * display_info.height) / 7;
    PLAYWA_GV.SCORE_FONTSIZE = (1 * display_info.height) / 19;
    PLAYWA_GV.HINT_FONTSIZE = (2 * PLAYWA_GV.SCORE_FONTSIZE) / 3;
    PLAYWA_GV.ASTEROID_FONTSIZE = (1 * display_info.height) / 40;
    PLAYWA_GV.BONUS_NUM_FONTSIZE = (1 * display_info.height) / 30;
    PLAYWA_GV.BONUS_HINT_FONTSIZE = (1 * display_info.height) / 47;
    
    // Aggiornamento proporzioni grafiche instructions
    INSTR_GV.BONUS_RADIUS = (1*display_info.width) / 14;
    INSTR_GV.BONUS_CASE_WIDTH = (3*display_info.width) / 7;
    INSTR_GV.SUBTITLE_FONTSIZE = (1*display_info.width) / 40;
    INSTR_GV.TEXT_FONTSIZE = (1*display_info.width) / 58;
    
    // Aggiornamento proporzioni grafiche input username
    USR_GV.USERNAME_FONTSIZE = (1 * display_info.height) / 30;
    USR_GV.STATS_FONTSIZE = (1 * display_info.height) / 22;
    USR_GV.USERNAME_BLOCK_TOP_OFFSET = (3*display_info.height)/6;
    USR_GV.ENTER_FONTSIZE = (1 * display_info.height) / 60;
    USR_GV.ENTER_LEFT_OFFSET = (244*display_info.width) / 345;
    USR_GV.ENTER_TOP_OFFSET = USR_GV.USERNAME_BLOCK_TOP_OFFSET + display_info.height / 38;
    USR_GV.ENTER_WIDTH = (1*display_info.width) / 18 ;
    USR_GV.ENTER_HEIGHT = (1*display_info.height) / 34;
}