#include "drawing_functions.h"

// Private

//*******

// Public

ALLEGRO_BITMAP **generate_menu_bitmaps() {
    int	i;
    ALLEGRO_BITMAP	**arr = new ALLEGRO_BITMAP *[NUM_MENU_BITMAPS];
    char	*bmp_path;
    char	bmp_path_names[][255] = {/* [0]*/ "title.png",
            /* [1]*/ "menu_option_selected.png",
            /* [2]*/ "menu_option_unselected.png",
            /* [3]*/ "bg_menu.png"
    };

    for (i = 0; i < NUM_MENU_BITMAPS; i++) {
        bmp_path = new char[255];
        bmp_path[0] = '\0';
        strcat(bmp_path, BMP_PATH_BASE);
        strcat(bmp_path, bmp_path_names[i]);
        arr[i] = al_load_bitmap(bmp_path);
        assert(arr[i] != nullptr);
        delete[] bmp_path;
    }

    return arr;
}

ALLEGRO_BITMAP **generate_playwa_bitmaps() {
    int	i;
    ALLEGRO_BITMAP	**arr = new ALLEGRO_BITMAP *[NUM_PLAYWA_BITMAPS];
    char	*bmp_path;
    char	bmp_path_names[][255] = {/* [0]*/ "shooter.png",
            /* [1]*/ "shooter_area.png",
            /* [2]*/ "shooter_area_danger.png",
            /* [3]*/ "bullet.png",
            /* [4]*/ "atomic_bonus.png",
            /* [5]*/ "rallenty_bonus.png",
            /* [6]*/ "fire_bonus.png",
            /* [7]*/ "shield_bonus.png",
            /* [8]*/ "bg_play.png",
            /* [9]*/ "back_bonus.png",
            /*[10]*/ "asteroids/error/ast.png",
            /*[11]*/ "shooter_area_shield.png",
            /*[12]*/ "music_icon.png",
            /*[13]*/ "sound_icon.png"
    };

    for (i = 0; i < NUM_PLAYWA_BITMAPS; i++) {
        bmp_path = new char[255];
        bmp_path[0] = '\0';
        strcat(bmp_path, BMP_PATH_BASE);
        strcat(bmp_path, bmp_path_names[i]);
        arr[i] = al_load_bitmap(bmp_path);
        assert(arr[i] != nullptr);
        delete[] bmp_path;
    }

    return arr;
}

ALLEGRO_BITMAP **generate_instr_bitmaps() {
    int	i;
    ALLEGRO_BITMAP	**arr = new ALLEGRO_BITMAP *[NUM_INSTR_BITMAPS];
    char	*bmp_path;
    char	bmp_path_names[][255] = {/* [0]*/ "bg_play.png",
            /* [1]*/ "instr_bonus_case.png",
            /* [2]*/ "atomic_bonus.png",
            /* [3]*/ "rallenty_bonus.png",
            /* [4]*/ "fire_bonus.png",
            /* [5]*/ "shield_bonus.png"
    };

    for (i = 0; i < NUM_INSTR_BITMAPS; i++) {
        bmp_path = new char[255];
        bmp_path[0] = '\0';
        strcat(bmp_path, BMP_PATH_BASE);
        strcat(bmp_path, bmp_path_names[i]);
        arr[i] = al_load_bitmap(bmp_path);
        assert(arr[i] != nullptr);
        delete[] bmp_path;
    }

    return arr;
}

ALLEGRO_FONT **generate_playwa_fonts() {
    int	i;
    ALLEGRO_FONT	**arr = new ALLEGRO_FONT *[NUM_PLAYWA_FONTS];
    int	fontsizes[] = {/* [0]*/ PLAYWA_GV.SCORE_FONTSIZE,
            /* [1]*/ PLAYWA_GV.HINT_FONTSIZE,
            /* [2]*/ PLAYWA_GV.ASTEROID_FONTSIZE,
            /* [3]*/ PLAYWA_GV.BONUS_NUM_FONTSIZE,
            /* [4]*/ PLAYWA_GV.BONUS_HINT_FONTSIZE
    };

    for (i = 0; i < NUM_PLAYWA_FONTS; i++) {
        arr[i] = al_load_font(FONT_PATH, fontsizes[i], 0);
        assert(arr[i] != nullptr);
    }

    return arr;
}

ALLEGRO_FONT **generate_instr_fonts() {
    int	i;
    ALLEGRO_FONT	**arr = new ALLEGRO_FONT *[NUM_INSTR_FONTS];
    int	fontsizes[] = {/* [0]*/ GENERAL_GV.HEAD_FONTSIZE,
            /* [1]*/ GENERAL_GV.BACK_FONTSIZE,
            /* [2]*/ INSTR_GV.SUBTITLE_FONTSIZE,
            /* [3]*/ INSTR_GV.TEXT_FONTSIZE
    };

    for (i = 0; i < NUM_INSTR_FONTS; i++) {
        arr[i] = al_load_font(FONT_PATH, fontsizes[i], 0);
        assert(arr[i] != nullptr);
    }

    return arr;
}

ALLEGRO_FONT **generate_menu_fonts() {
    int	i;
    ALLEGRO_FONT	**arr = new ALLEGRO_FONT *[NUM_MENU_FONTS];
    int	fontsizes[] = {/* [0]*/ MENU_GV.OPTION_FONTSIZE,
            /* [1]*/ MENU_GV.COPYRIGHT_FONTSIZE,
            /* [2]*/ GENERAL_GV.HEAD_FONTSIZE,
    };

    for (i = 0; i < NUM_MENU_FONTS; i++) {
        arr[i] = al_load_font(FONT_PATH, fontsizes[i], 0);
        assert(arr[i] != nullptr);
    }

    return arr;
}

ALLEGRO_FONT **generate_user_fonts() {
    int	i;
    ALLEGRO_FONT	**arr = new ALLEGRO_FONT *[NUM_USER_FONTS];
    int	fontsizes[] = {/* [0]*/ USR_GV.USERNAME_FONTSIZE,
            /* [1]*/ GENERAL_GV.HEAD_FONTSIZE,
            /* [2]*/ USR_GV.STATS_FONTSIZE,
            /* [3]*/ USR_GV.ENTER_FONTSIZE,
    };

    for (i = 0; i < NUM_USER_FONTS; i++) {
        arr[i] = al_load_font(FONT_PATH, fontsizes[i], 0);
        assert(arr[i] != nullptr);
    }

    return arr;
}

ALLEGRO_FONT **generate_settings_fonts() {
    int	i;
    ALLEGRO_FONT	**arr = new ALLEGRO_FONT *[NUM_SETTINGS_FONTS];
    int	fontsizes[] = {/* [0]*/ GENERAL_GV.HEAD_FONTSIZE,
            /* [1]*/ MENU_GV.OPTION_FONTSIZE,
            /* [2]*/ MENU_GV.COPYRIGHT_FONTSIZE
    };

    for (i = 0; i < NUM_SETTINGS_FONTS; i++) {
        arr[i] = al_load_font(FONT_PATH, fontsizes[i], 0);
        assert(arr[i] != nullptr);
    }

    return arr;
}

void destroy_arr_bitmaps(ALLEGRO_BITMAP **arr, const int num) {
    int	i;
    for (i = 0; i < num; i++)
        al_destroy_bitmap(arr[i]);

    delete[] arr;
}

void destroy_arr_fonts(ALLEGRO_FONT **arr, const int num) {
    int	i;
    for (i = 0; i < num; i++)
        al_destroy_font(arr[i]);

    delete[] arr;
}


//============================================
//                  Generali
//============================================
void
draw_background(ALLEGRO_BITMAP *bmp_bg, float &offset_bg, const bool playing) {
    al_draw_scaled_bitmap(bmp_bg, 0, 0, 1196, 748,
                              offset_bg, 0, display_info.width,
                              display_info.height, 0);
    al_draw_scaled_bitmap(bmp_bg, 0, 0, 1196, 748,
                              offset_bg - display_info.width,
                              0, display_info.width, display_info.height, 0);

    if (playing)
        offset_bg += 0.20;
    else
        offset_bg += 0.5;

    if (offset_bg >= display_info.width)
        offset_bg = 0;
}

void draw_head(char *head_str, ALLEGRO_FONT *font) {
    // Stampa ombra testo
    al_draw_text(font,
                 al_map_rgb(102, 104, 99),
                 display_info.width / 2 + GENERAL_GV.HEAD_TEXT_SHADOW_GAP,
                 GENERAL_GV.HEAD_TOP_OFFSET + GENERAL_GV.HEAD_TEXT_SHADOW_GAP,
                 ALLEGRO_ALIGN_CENTRE,
                 head_str);

    // Stampa testo
    al_draw_text(font,
                 al_map_rgb(255, 255, 255),
                 display_info.width / 2, GENERAL_GV.HEAD_TOP_OFFSET,
                 ALLEGRO_ALIGN_CENTRE,
                 head_str);
}

void draw_back(ALLEGRO_FONT *font, const bool pause) {
    char	str[255];

    if (!pause)
        strcpy(str, "< PREMI 'INVIO' PER TORNARE AL MENU PRINCIPALE");
    else
        strcpy(str, "< PREMI 'INVIO' PER RIPRENDERE A GIOCARE");

    // Stampa ombra testo
    al_draw_text(font,
                 SHADOW_COLOR,
                 GENERAL_GV.BACK_LEFT_OFFSET + GENERAL_GV.BACK_TEXT_SHADOW_GAP,
                 GENERAL_GV.BACK_TOP_OFFSET + GENERAL_GV.BACK_TEXT_SHADOW_GAP,
                 ALLEGRO_ALIGN_LEFT,
                 str);

    // Stampa testo
    al_draw_text(font,
                 al_map_rgb(125, 125, 125),
                 GENERAL_GV.BACK_LEFT_OFFSET, GENERAL_GV.BACK_TOP_OFFSET,
                 ALLEGRO_ALIGN_LEFT,
                 str);
}


//============================================
//                  Intro
//============================================
void draw_intro_init(ALLEGRO_BITMAP **arr_bitmaps, float &bg_offset) {
    for (float first_rest = 0;
         first_rest < 2.0; first_rest += BG_REFRESH_TIME * 40) {
        // Stampa sfondo
        draw_background(arr_bitmaps[3], bg_offset, 0);
        // Stampa titolo
        al_draw_scaled_bitmap(arr_bitmaps[0],
                              0, 0, 2880, 700,
                              display_info.width / 2 - MENU_GV.TITLE_W / 2,
                              display_info.height / 2 - MENU_GV.TITLE_H / 2,
                              MENU_GV.TITLE_W, MENU_GV.TITLE_H,
                              0);
        // Aggiorna il display
        al_flip_display();

        al_rest(BG_REFRESH_TIME);
    }
}

void draw_intro_title_slide(ALLEGRO_BITMAP **arr_bitmaps, float &bg_offset) {
    float	title_offset = display_info.height / 2 - MENU_GV.TITLE_H / 2;
    while (title_offset > MENU_GV.UPPER_OFFSET) {

        title_offset -= title_offset / MENU_GV.UPPER_OFFSET * 0.8;
        if (title_offset < MENU_GV.UPPER_OFFSET)
            title_offset = MENU_GV.UPPER_OFFSET;

        // Stampa sfondo
        draw_background(arr_bitmaps[3], bg_offset, 0);

        // Stampa titolo
        al_draw_scaled_bitmap(arr_bitmaps[0], 0, 0, 2880, 700,
                              display_info.width / 2 - MENU_GV.TITLE_W / 2,
                              title_offset,
                              MENU_GV.TITLE_W, MENU_GV.TITLE_H, 0);

        // Aggiorna il display
        al_flip_display();
        al_rest(BG_REFRESH_TIME);
    }
}

void draw_intro_menu_fadein(ALLEGRO_BITMAP **arr_bitmaps,
                            ALLEGRO_FONT **arr_fonts, float &bg_offset) {
    char	arr_scelte[][255] = {"Gioca",
                              "Impostazioni",
                              "Esci"};
    float	menu_opacity, LEFT_OFFSET, TOP_OFFSET;
    int	i;

    for (menu_opacity = 0; menu_opacity < 255; menu_opacity += 7.5) {

        // Stampa sfondo
        draw_background(arr_bitmaps[3], bg_offset, 0);

        // Stampa titolo
        draw_menu_title(arr_bitmaps[0]);

        // Setto blender (trasparenza)
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

        for (i = 0; i < NUM_OPTIONS; i++) {
            ALLEGRO_BITMAP *settings_option_b = (i == 0 ? arr_bitmaps[1]
                                                            : arr_bitmaps[2]);

            // Stampa opzioni menu (semi-trasparenti)
            LEFT_OFFSET = display_info.width / 2 - MENU_GV.OPTION_W / 2;
            TOP_OFFSET = 2 * MENU_GV.UPPER_OFFSET + MENU_GV.TITLE_H +
                             i * (MENU_GV.OPTION_H + 2 * MENU_GV.INTERNAL_OFFSET);

            al_draw_tinted_scaled_bitmap(settings_option_b,
                                         al_map_rgba(255, 255, 255,
                                                     menu_opacity),
                                         0, 0, 1024, 120,
                                         LEFT_OFFSET, TOP_OFFSET,
                                         MENU_GV.OPTION_W,
                                         MENU_GV.OPTION_H, 0);

            al_draw_text(arr_fonts[0],
                             al_map_rgba(246, 242, 212, menu_opacity),
                             LEFT_OFFSET + MENU_GV.OPTION_W / 2,
                             TOP_OFFSET + MENU_GV.OPTION_TEXT_OFFSET,
                             ALLEGRO_ALIGN_CENTRE,
                             arr_scelte[i]);

        }

        // Stampa copyright (semi-trasparente)
        al_draw_text(arr_fonts[1],
                     al_map_rgba(122, 124, 119, menu_opacity),
                     display_info.width / 2,
                     MENU_GV.COPYRIGHT_TOP_OFFSET,
                     ALLEGRO_ALIGN_CENTRE,
                     "© Word Asteroid - Corradini Matteo, 2019");

        // Aggiorna il display
        al_flip_display();

        al_rest(BG_REFRESH_TIME);
    }
}


//============================================
//                  Menu
//============================================
void draw_menu_title(ALLEGRO_BITMAP *bmp_title) {
    al_draw_scaled_bitmap(bmp_title,
                              0, 0, 2880, 700,
                              display_info.width / 2 - MENU_GV.TITLE_W / 2,
                              MENU_GV.UPPER_OFFSET, MENU_GV.TITLE_W,
                              MENU_GV.TITLE_H, 0);
}

void draw_menu_option(const int &index, ALLEGRO_BITMAP *bmp_option,
                      ALLEGRO_FONT *font, char *str_scelta,
                      const bool settings) {
    float	OPTION_LEFT_OFFSET, OPTION_TOP_OFFSET;

    OPTION_LEFT_OFFSET = display_info.width / 2 - MENU_GV.OPTION_W / 2;
    OPTION_TOP_OFFSET =
            (settings ? 0.3 : 2) * MENU_GV.UPPER_OFFSET + MENU_GV.TITLE_H +
            index * (MENU_GV.OPTION_H + 2 * MENU_GV.INTERNAL_OFFSET);

    al_draw_scaled_bitmap(bmp_option,
                              0, 0, 1024, 120, OPTION_LEFT_OFFSET,
                              OPTION_TOP_OFFSET,
                              MENU_GV.OPTION_W, MENU_GV.OPTION_H,
                              0);
    al_draw_text(font,
                 MENU_FONT_COLOR,
                 OPTION_LEFT_OFFSET + MENU_GV.OPTION_W / 2,
                 OPTION_TOP_OFFSET + MENU_GV.OPTION_TEXT_OFFSET,
                 ALLEGRO_ALIGN_CENTRE,
                 str_scelta);
}

void draw_menu_copyright(ALLEGRO_FONT *font) {
    al_draw_text(font,
                 MENU_CPY_COLOR,
                 display_info.width / 2,
                 MENU_GV.COPYRIGHT_TOP_OFFSET,
                 ALLEGRO_ALIGN_CENTRE,
                 "© Word Asteroid - Corradini Matteo 2019");
}


//============================================
//                  Playwa
//============================================
void draw_playwa_score_hint(const match_vars_t &match_vars,
                            ALLEGRO_FONT *font_score, ALLEGRO_FONT *font_hints,
                            const bool visible_hints) {
    char	*score;
    // Stampa score
    al_draw_text(font_score,
                 SHADOW_COLOR,
                 PLAYWA_GV.SCORE_LEFT_OFFSET +
                 PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                 PLAYWA_GV.SCORE_TOP_OFFSET +
                 1.5 * PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                 ALLEGRO_ALIGN_RIGHT,
                 "Score");
    al_draw_text(font_score,
                 al_map_rgb(132, 134, 129),
                 PLAYWA_GV.SCORE_LEFT_OFFSET,
                 PLAYWA_GV.SCORE_TOP_OFFSET,
                 ALLEGRO_ALIGN_RIGHT,
                 "Score");

    score = int_to_str_score(match_vars.score);
    al_draw_text(font_score,
                 SHADOW_COLOR,
                 PLAYWA_GV.SCORE_LEFT_OFFSET +
                 PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                 PLAYWA_GV.SCORE_TOP_OFFSET + PLAYWA_GV.TEXT_INTERNAL_OFFSET +
                 1.5 * PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                 ALLEGRO_ALIGN_RIGHT,
                 score);
    al_draw_text(font_score,
                 al_map_rgb(255, 255, 255),
                 PLAYWA_GV.SCORE_LEFT_OFFSET,
                 PLAYWA_GV.SCORE_TOP_OFFSET + PLAYWA_GV.TEXT_INTERNAL_OFFSET,
                 ALLEGRO_ALIGN_RIGHT,
                 score);
    delete[] score;

    // Stampa suggerimenti
    if (visible_hints) {
        al_draw_text(font_hints,
                     SHADOW_COLOR,
                     PLAYWA_GV.HINT_LEFT_OFFSET +
                     PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                     PLAYWA_GV.HINT_TOP_OFFSET +
                     1.5 * PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                     ALLEGRO_ALIGN_RIGHT,
                     "ESC: Pausa");
        al_draw_text(font_hints,
                     al_map_rgb(132, 134, 129),
                     PLAYWA_GV.HINT_LEFT_OFFSET,
                     PLAYWA_GV.HINT_TOP_OFFSET,
                     ALLEGRO_ALIGN_RIGHT,
                     "ESC: Pausa");
        al_draw_text(font_hints,
                     SHADOW_COLOR,
                     PLAYWA_GV.HINT_LEFT_OFFSET +
                     PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                     PLAYWA_GV.HINT_TOP_OFFSET +
                     2 * PLAYWA_GV.TEXT_INTERNAL_OFFSET / 3 +
                     1.5 * PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                     ALLEGRO_ALIGN_RIGHT,
                     "SHIFT: Nascondi suggerimenti");
        al_draw_text(font_hints,
                     al_map_rgb(132, 134, 129),
                     PLAYWA_GV.HINT_LEFT_OFFSET,
                     PLAYWA_GV.HINT_TOP_OFFSET +
                     2 * PLAYWA_GV.TEXT_INTERNAL_OFFSET / 3,
                     ALLEGRO_ALIGN_RIGHT,
                     "SHIFT: Nascondi suggerimenti");
    }
}

void
draw_playwa_shooter(const match_vars_t &match_vars, const bullet_t *arr_bullet,
                    const shooter_t &shooter, ALLEGRO_BITMAP **arr_bitmaps) {
    // Stampa shooter area (calcolo distanza per danger)
    if (al_get_timer_started(match_vars.timer_shield_bonus))
        al_draw_scaled_bitmap(arr_bitmaps[11],
                              0, 0, 500, 500,
                              display_info.width / 2 -
                              PLAYWA_GV.SHOOTER_AREA_RAD,
                              display_info.height / 2 -
                              PLAYWA_GV.SHOOTER_AREA_RAD,
                              PLAYWA_GV.SHOOTER_AREA_RAD * 2,
                              PLAYWA_GV.SHOOTER_AREA_RAD * 2, 0);
    else if (check_distance(match_vars.ast_queues, arr_bullet, shooter) <
             PLAYWA_GV.DANGER_RADIUS)
        al_draw_scaled_bitmap(arr_bitmaps[2],
                              0, 0, 500, 500,
                              display_info.width / 2 -
                              PLAYWA_GV.SHOOTER_AREA_RAD,
                              display_info.height / 2 -
                              PLAYWA_GV.SHOOTER_AREA_RAD,
                              PLAYWA_GV.SHOOTER_AREA_RAD * 2,
                              PLAYWA_GV.SHOOTER_AREA_RAD * 2, 0);
    else
        al_draw_scaled_bitmap(arr_bitmaps[1],
                              0, 0, 500, 500,
                              display_info.width / 2 -
                              PLAYWA_GV.SHOOTER_AREA_RAD,
                              display_info.height / 2 -
                              PLAYWA_GV.SHOOTER_AREA_RAD,
                              PLAYWA_GV.SHOOTER_AREA_RAD * 2,
                              PLAYWA_GV.SHOOTER_AREA_RAD * 2, 0);
    // Stampa shooter
    al_draw_scaled_rotated_bitmap(arr_bitmaps[0],
                                  212, 232,
                                  display_info.width / 2,
                                  display_info.height / 2,
                                  PLAYWA_GV.SHOOTER_SCALE,
                                  PLAYWA_GV.SHOOTER_SCALE,
                                  shooter.slope, 0);
                                                                
}

void
draw_playwa_asteroids_bullets(const match_vars_t &match_vars,
                              const bullet_t *arr_bullet,
                              ALLEGRO_BITMAP **arr_bitmaps,
                              ALLEGRO_FONT *font) {
    float	ast_shadow_x_gap, ast_shadow_y_gap, bullet_slope;
    ALLEGRO_BITMAP	*bmp;
    int	i;

    // Stampa asteroidi
    for (i = 0; i < N_QUEUES; i++)
        if (match_vars.ast_queues[i] != nullptr) {
            asteroid_t ast = match_vars.ast_queues[i]->asteroid;
            ast_shadow_x_gap = (ast.x < display_info.width / 2 ? -1 : 1) *
                               PLAYWA_GV.ASTEROID_SHADOW_GAP;
            ast_shadow_y_gap = (ast.y < display_info.height / 2 ? -1 : 1) *
                               PLAYWA_GV.ASTEROID_SHADOW_GAP;

            if (arr_bullet[i].x != 0) {
                bullet_slope = ast.y > display_info.height / 2 ?
                               M_PI_4 + atan(-1 /
                                             tan(match_vars.ast_queues[i]->asteroid.slope))
                                                               :
                               atan(-1 /
                                	tan(match_vars.ast_queues[i]->asteroid.slope));

                al_draw_scaled_rotated_bitmap(arr_bitmaps[3],
                                              10, 10,
                                              arr_bullet[i].x, arr_bullet[i].y,
                                              PLAYWA_GV.BULLET_SCALE,
                                              PLAYWA_GV.BULLET_SCALE,
                                              bullet_slope, 0);
            }

            // Selezione bitmap
            bmp = (match_vars.key_error != i ? ast.bmp : arr_bitmaps[10]);
            // Stampa ombra asteroide
            al_draw_tinted_scaled_bitmap(bmp,
                                         al_map_rgb(100, 100, 100),
                                         0, 0, 500, 500,
                                         ast.x + ast_shadow_x_gap,
                                         ast.y + ast_shadow_y_gap,
                                         ast.radius * 2,
                                         ast.radius * 2,
                                         0);
            // Stampa asteroide
            al_draw_scaled_bitmap(bmp,
                                  0, 0, 500, 500,
                                  ast.x, ast.y, ast.radius * 2, ast.radius * 2,
                                  0);

            // Stampa ombra testo
            al_draw_text(font,
                             SHADOW_COLOR,
                             ast.x + ast.radius +
                             PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                             ast.y + ast.radius - PLAYWA_GV.ASTEROID_FONTSIZE / 2 +
                             PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                             ALLEGRO_ALIGN_CENTRE,
                             ast.word);

            // Stampa testo
            al_draw_text(font,
                             al_map_rgb(255, 255, 255),
                             ast.x + ast.radius,
                             ast.y + ast.radius - PLAYWA_GV.ASTEROID_FONTSIZE / 2,
                             ALLEGRO_ALIGN_CENTRE,
                             ast.word);
        }
}

void draw_playwa_bonus_music(const match_vars_t &match_vars,
                             ALLEGRO_BITMAP **arr_bitmaps,
                             ALLEGRO_FONT *font_score,
                             ALLEGRO_FONT *font_bonus,
                             ALLEGRO_FONT *font_bonus_hint,
                             settings_t settings) {
    int	i;
    bool	trasparenza;
    string	s;
    char 	*bonus_num, *bonus_hint;

    // Stampa scritta "Bonus"
    al_draw_text(font_score,
                 SHADOW_COLOR,
                 1.3 * (display_info.width - PLAYWA_GV.SCORE_LEFT_OFFSET) +
                 PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                 PLAYWA_GV.SCORE_TOP_OFFSET +
                 1.5 * PLAYWA_GV.ASTEROID_TEXT_SHADOW_GAP,
                 ALLEGRO_ALIGN_LEFT,
                 "Bonus");
    al_draw_text(font_score,
                 al_map_rgb(132, 134, 129),
                 1.3 * (display_info.width - PLAYWA_GV.SCORE_LEFT_OFFSET),
                 PLAYWA_GV.SCORE_TOP_OFFSET,
                 ALLEGRO_ALIGN_LEFT,
                 "Bonus");

    // Stampa bonus
    for (i = 0; i < NUM_ITEMS; i++) {

        // Setto blender (trasparenza)
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

        // Stampa ombra bonus
        al_draw_scaled_bitmap(arr_bitmaps[9],
                              0, 0, 256, 128,
                              i * PLAYWA_GV.BONUS_LEFT_OFFSET +
                              (display_info.width -
                               PLAYWA_GV.SCORE_LEFT_OFFSET),
                              PLAYWA_GV.BONUS_TOP_OFFSET,
                              PLAYWA_GV.HEIGHT_BONUS * 2,
                              PLAYWA_GV.HEIGHT_BONUS,
                              0);
        trasparenza = false;
        if ((i == 1 && al_get_timer_started(match_vars.timer_rallenty_bonus)) ||
            (i == 3 && al_get_timer_started(match_vars.timer_shield_bonus)))
            trasparenza = true;
        // Stampa icona bonus
        al_draw_tinted_scaled_bitmap(arr_bitmaps[i + 4],
                                	 al_map_rgba_f(1, 1, 1,
                                                   (trasparenza ? 0.4 : 1)),
                                	 0, 0, 128, 128,
                                	 i * PLAYWA_GV.BONUS_LEFT_OFFSET +
                                	 (display_info.width -
                                	  PLAYWA_GV.SCORE_LEFT_OFFSET),
                                	 PLAYWA_GV.BONUS_TOP_OFFSET,
                                	 PLAYWA_GV.HEIGHT_BONUS,
                                	 PLAYWA_GV.HEIGHT_BONUS,
                                	 0);

        // Stampa numerosità
        s = to_string(match_vars.items[i]);
        bonus_num = new char[3];
        strcpy(bonus_num, s.c_str());

        al_draw_text(font_bonus,
                     al_map_rgba_f(1, 1, 1, (trasparenza ? 0.4 : 1)),
                     i * PLAYWA_GV.BONUS_LEFT_OFFSET +
                     (display_info.width - PLAYWA_GV.SCORE_LEFT_OFFSET) +
                     PLAYWA_GV.BONUS_LEFT_OFFSET / 1.6,
                     PLAYWA_GV.BONUS_TOP_OFFSET +
                     PLAYWA_GV.BONUS_NUM_FONTSIZE / 2,
                     ALLEGRO_ALIGN_CENTRE,
                     bonus_num);
        delete[] bonus_num;

        s = to_string(i + 1);
        bonus_hint = new char[3];
        bonus_hint[0] = 'F';
        strcpy(&bonus_hint[1], s.c_str());

        // Stampa suggerimento tasto
        al_draw_text(font_bonus_hint,
                     al_map_rgba(255, 255, 255, 128),
                     i * PLAYWA_GV.BONUS_LEFT_OFFSET +
                     (display_info.width - PLAYWA_GV.SCORE_LEFT_OFFSET) +
                     PLAYWA_GV.BONUS_LEFT_OFFSET / 2.3,
                     PLAYWA_GV.BONUS_TOP_OFFSET +
                     PLAYWA_GV.BONUS_NUM_FONTSIZE * 2,
                     ALLEGRO_ALIGN_CENTRE,
                     bonus_hint);

        delete[] bonus_hint;
    }

    // Settaggio blender (trasparenza)
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    // Stampa icona musica e icona suono (+suggerimenti)
    al_draw_tinted_scaled_bitmap(arr_bitmaps[12],
                                 al_map_rgba_f(1, 1, 1,
                                               settings.music == ON ? 1 : 0.4),
                                 0, 0, 128, 128,
                                 PLAYWA_GV.BONUS_LEFT_OFFSET / 6,
                                 (9 * display_info.height) / 10,
                                 PLAYWA_GV.HEIGHT_BONUS, PLAYWA_GV.HEIGHT_BONUS,
                                 0);
    al_draw_text(font_bonus_hint,
                 al_map_rgba(255, 255, 255, 128),
                 PLAYWA_GV.BONUS_LEFT_OFFSET / 2.7,
                 (34 * display_info.height) / 35,
                 ALLEGRO_ALIGN_CENTRE,
                 "F8");
    al_draw_tinted_scaled_bitmap(arr_bitmaps[13],
                                 al_map_rgba_f(1, 1, 1,
                                               settings.sound == ON ? 1 : 0.4),
                                 0, 0, 128, 128,
                                 (4 * PLAYWA_GV.BONUS_LEFT_OFFSET) / 5,
                                 (9 * display_info.height) / 10,
                                 PLAYWA_GV.HEIGHT_BONUS, PLAYWA_GV.HEIGHT_BONUS,
                                 0);
    al_draw_text(font_bonus_hint,
                 al_map_rgba(255, 255, 255, 128),
                 PLAYWA_GV.BONUS_LEFT_OFFSET * 1.005,
                 (34 * display_info.height) / 35,
                 ALLEGRO_ALIGN_CENTRE,
                 "F9");
}


//============================================
//                 Gameover
//============================================
void draw_stats_blocks(ALLEGRO_FONT *font) {
    char	arr_stats_str[][255] = {"Score:", "Asteroidi distrutti: "};
    int	i;
    float	left_offset, top_offset;

    for (i = 0; i < 2; i++) {

        left_offset = display_info.width / 6;
        top_offset = 4 * GENERAL_GV.HEAD_TOP_OFFSET +
                     i * (display_info.height / 9 + display_info.height / 175);

        // Stampa rettangolo di fondo
        al_draw_filled_rectangle(left_offset, top_offset,
                                 display_info.width - left_offset,
                                 top_offset + display_info.height / 9,
                                 al_map_rgba(0, 0, 0, 30));

        // Stampa nome stat
        al_draw_text(font,
                     SHADOW_COLOR,
                     (7 * left_offset) / 6 +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                     top_offset + display_info.height / 27 +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                     ALLEGRO_ALIGN_LEFT,
                     arr_stats_str[i]);
        al_draw_text(font,
                     al_map_rgb(100, 100, 100),
                     (7 * left_offset) / 6,
                     top_offset + display_info.height / 27,
                     ALLEGRO_ALIGN_LEFT,
                     arr_stats_str[i]);

    }
    // Stampa il rettangolo con le corrispondenze trovate
    left_offset = display_info.width / 6;
    top_offset = 4 * GENERAL_GV.HEAD_TOP_OFFSET +
                 i * (display_info.height / 9 + display_info.height / 175);
    // Stampa rettangolo di fondo
    al_draw_filled_rectangle(left_offset, top_offset,
                             display_info.width - left_offset,
                             top_offset + display_info.height / 2 + 10,
                             al_map_rgba(0, 0, 0, 30));

};

void draw_stat(const int &idx_stat, int stat_value, ALLEGRO_FONT *font) {
    float	left_offset, top_offset;
    char	*str = new char[255];

    left_offset = display_info.width / 6;
    top_offset = 4 * GENERAL_GV.HEAD_TOP_OFFSET + idx_stat *
                                                  (display_info.height / 9 +
                                                   display_info.height / 175);
    switch (idx_stat) {

        // Score
        case 0:
            strcpy(str, int_to_str_score(stat_value));
            break;

            // Asteroidi distrutti
        case 1: {
            string s = to_string(stat_value);
            strcpy(str, s.c_str());
            break;
        }
    }
    al_draw_text(font,
                 SHADOW_COLOR,
                 display_info.width - (7 * left_offset) / 6 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 top_offset + display_info.height / 27 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 ALLEGRO_ALIGN_RIGHT,
                 str);
    al_draw_text(font,
                 al_map_rgb(255, 255, 255),
                 display_info.width - (7 * left_offset) / 6,
                 top_offset + display_info.height / 27,
                 ALLEGRO_ALIGN_RIGHT,
                 str);
    delete[] str;
}

void draw_gameover_animation(const int &score_goal, const int &dast_goal,
                             ALLEGRO_BITMAP *bg_bmp, float &bg_offset,
                             ALLEGRO_FONT **arr_fonts) {
    // Variabili animazione
    int	idx_stat, h_score, h_dast = 0;

    // Animazione
    while (idx_stat < 2) {
        // Stampa sfondo
        draw_background(bg_bmp, bg_offset, 0);
        // Stampa titolo
        char *head_str = new char[255];
        strcpy(head_str, "Gameover");
        draw_head(head_str, arr_fonts[1]);
        delete[] head_str;
        // Stampa stats
        draw_stats_blocks(arr_fonts[2]);
        switch (idx_stat) {
            case 1:
                draw_stat(1, h_dast, arr_fonts[2]);
                if (dast_goal > h_dast)
                    h_dast += 1;
                else if (idx_stat == 1) idx_stat++;
                // Score
            case 0:
                draw_stat(0, h_score, arr_fonts[2]);
                if (score_goal > h_score)
                    h_score += 10;
                else if (idx_stat == 0) idx_stat++;

        }
        al_flip_display();
        al_rest(BG_REFRESH_TIME);
    }
}

void draw_playagain_button(ALLEGRO_FONT *font) {
    float	left_offset, top_offset;
    char	play_again[] = "Premi enter per rigiocare";


    left_offset = display_info.width / 6;
    top_offset = 4 * GENERAL_GV.HEAD_TOP_OFFSET +
                 6 * (display_info.height / 9 + display_info.height / 175) + 40;
    // Stampa tasto enter
    al_draw_filled_rectangle(left_offset, top_offset,
                             display_info.width - left_offset,
                             top_offset + display_info.height / 15,
                             al_map_rgba(92, 139, 155, 255));
    top_offset += 10;
    left_offset *= 3;
    al_draw_text(font, SHADOW_COLOR,
                 left_offset,
                 top_offset + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 ALLEGRO_ALIGN_CENTRE, play_again);
    al_draw_text(font, al_map_rgb(255, 255, 255), left_offset,
                 top_offset + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 ALLEGRO_ALIGN_CENTRE, play_again);
}

void draw_results(ALLEGRO_FONT *font, result_t res) {
    char	result_title[] = "Risultati:";
    char	no_match[] = "Nessun match trovato";
    int	i;

    al_draw_text(font, SHADOW_COLOR,
                 display_info.width / 6 + (1 * display_info.height) / 24 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 GENERAL_GV.RESULT_TOP_OFFSET + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 ALLEGRO_ALIGN_LEFT, result_title);
    al_draw_text(font, al_map_rgb(100, 100, 100),
                 display_info.width / 6 + (1 * display_info.height) / 24,
                 GENERAL_GV.RESULT_TOP_OFFSET,
                 ALLEGRO_ALIGN_LEFT, result_title);
    if (res.count_result == 0) {
        // No result found
        al_draw_text(font, SHADOW_COLOR,
                     display_info.width / 6 + (1 * display_info.height) / 24 +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                     GENERAL_GV.RESULT_TOP_OFFSET +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5 +
                     USR_GV.STATS_FONTSIZE,
                     ALLEGRO_ALIGN_LEFT,
                     no_match);
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     display_info.width / 6 + (1 * display_info.height) / 24,
                     GENERAL_GV.RESULT_TOP_OFFSET + USR_GV.STATS_FONTSIZE,
                     ALLEGRO_ALIGN_LEFT,
                     no_match);
        return;
    }
    for (i = 0; i < res.count_result; ++i) {
        // Stampa username
        al_draw_text(font,
                     SHADOW_COLOR,
                     display_info.width / 6 + (1 * display_info.height) / 24 +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                     GENERAL_GV.RESULT_TOP_OFFSET +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5 +
                     USR_GV.STATS_FONTSIZE * (i + 1),
                     ALLEGRO_ALIGN_LEFT,
                     res.pass_result[i]);
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     display_info.width / 6 + (1 * display_info.height) / 24,
                     GENERAL_GV.RESULT_TOP_OFFSET +
                     USR_GV.STATS_FONTSIZE * (i + 1),
                     ALLEGRO_ALIGN_LEFT,
                     res.pass_result[i]);
    }
}

//============================================
//                 Ask email
//============================================

void draw_username_block(const bool enter_active, ALLEGRO_FONT *font) {
    // Stampa rettangolo di fondo
    al_draw_filled_rectangle(display_info.width / 6,
                             USR_GV.USERNAME_BLOCK_TOP_OFFSET,
                             (5 * display_info.width) / 6,
                             USR_GV.USERNAME_BLOCK_TOP_OFFSET +
                             display_info.height / 10,
                             al_map_rgba(0, 0, 0, 50));
    // Stampa linea username
    al_draw_line(display_info.width / 6 + (1 * display_info.height) / 24,
                 USR_GV.USERNAME_BLOCK_TOP_OFFSET +
                 (1 * display_info.height) / 12,
                 (3 * display_info.width) / 4.3,
                 USR_GV.USERNAME_BLOCK_TOP_OFFSET +
                 (1 * display_info.height) / 12,
                 al_map_rgba(120, 120, 120, 80),
                 display_info.height / 400);
    // Stampa tasto enter
    al_draw_filled_rectangle(USR_GV.ENTER_LEFT_OFFSET,
                             USR_GV.ENTER_TOP_OFFSET - 10,
                             USR_GV.ENTER_LEFT_OFFSET + USR_GV.ENTER_WIDTH * 2,
                             USR_GV.ENTER_TOP_OFFSET + USR_GV.ENTER_HEIGHT * 2,
                             (enter_active ? al_map_rgba(92, 139, 155, 255)
                                           : al_map_rgba(135, 143, 146, 255)));
    al_draw_text(font, SHADOW_COLOR,
                 USR_GV.ENTER_LEFT_OFFSET + display_info.width / 18 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 0.7,
                 USR_GV.ENTER_TOP_OFFSET + display_info.height / 100 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 0.7,
                 ALLEGRO_ALIGN_CENTRE,
                 "Invia");
    al_draw_text(font, al_map_rgb(255, 255, 255),
                 USR_GV.ENTER_LEFT_OFFSET + display_info.width / 18,
                 USR_GV.ENTER_TOP_OFFSET + display_info.height / 100,
                 ALLEGRO_ALIGN_CENTRE,
                 "Invia");

}

void draw_username(char *username, const int &cur_pos, ALLEGRO_FONT *font,
                   const bool bar_visible) {
    if (cur_pos == 0) {
        // Stampa suggerimento
        al_draw_text(font,
                     al_map_rgba(120, 120, 120, 80),
                     display_info.width / 6 + (1 * display_info.height) / 20,
                     USR_GV.USERNAME_BLOCK_TOP_OFFSET +
                     display_info.height / 30,
                     ALLEGRO_ALIGN_LEFT,
                     "Username");
    }

    if (bar_visible) {
        username[cur_pos] = '|';
        username[cur_pos + 1] = '\0';
    } else
        username[cur_pos] = '\0';
    // Stampa username
    al_draw_text(font, SHADOW_COLOR,
                 display_info.width / 6 + (1 * display_info.height) / 24 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 USR_GV.USERNAME_BLOCK_TOP_OFFSET + display_info.height / 45 +
                 GENERAL_GV.BACK_TEXT_SHADOW_GAP * 1.5,
                 ALLEGRO_ALIGN_LEFT,
                 username);
    al_draw_text(font, al_map_rgb(255, 255, 255),
                 display_info.width / 6 + (1 * display_info.height) / 24,
                 USR_GV.USERNAME_BLOCK_TOP_OFFSET + display_info.height / 30,
                 ALLEGRO_ALIGN_LEFT,
                 username);
}


//============================================
//             Istruzioni (pausa)
//============================================
void draw_instructions(ALLEGRO_FONT **arr_fonts, ALLEGRO_BITMAP **arr_bitmaps) {
    // Istruzioni gioco
    char	game_instr[] = "Distruggi gli asteroidi prima che colpiscano la navicella digitando le parole al loro interno!";

    // Istruzioni bonus
    char	bonus_instr[][255] = {
            "Durante tutta la durata della partita, potrai accumulare quattro diversi tipi di",
            "bonus che potrai utilizzare per difendere la navicella nel migliore dei modi."};
    char	arr_bonus_names[][255] = {"ATOMIC",
                                   "RALLENTY",
                                   "FIRE",
                                   "SHIELD"};
    char	arr_bonus_instr[][255] = {"DISTRUGGE TUTTE GLI ASTEROIDI",
                                   "GLI ASTEROIDI VENGONO",
                                   "DISTRUGGE L'ASTEROIDE PIU' VICINO",
                                   "TUTTI GLI ASTEROIDI CHE"};
    char	arr_bonus_instr_2[][255] = {"IN CAMPO (TASTO F1).",
                                	 "RALLENTATI PER POCHI SECONDI",
                                	 "(TASTO F3).",
                                	 "TOCCANO LO SCUDO VENGONO"};
    char	arr_bonus_instr_3[][255] = {"",
                                	 "(TASTO F2).",
                                	 "",
                                	 "DISTRUTTI (TASTO F4)."};

    float	top_offset, left_offset;
    int	 i;

    top_offset = display_info.height / 5;
    left_offset = display_info.width / 17;
    // Stampa sottotitolo "istruzioni"
    al_draw_text(arr_fonts[2],
                 SHADOW_COLOR,
                 left_offset + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 2,
                 top_offset + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 2,
                 ALLEGRO_ALIGN_LEFT,
                 "ISTRUZIONI");
    al_draw_text(arr_fonts[2],
                 al_map_rgb(255, 255, 255),
                 left_offset,
                 top_offset,
                 ALLEGRO_ALIGN_LEFT,
                 "ISTRUZIONI");
    // Stampa istruzioni gioco
    top_offset += PLAYWA_GV.TEXT_INTERNAL_OFFSET;
    al_draw_text(arr_fonts[3],
                 al_map_rgb(150, 150, 150),
                 left_offset,
                 top_offset,
                 ALLEGRO_ALIGN_LEFT,
                 game_instr);
    // Stampa sottotitolo "bonus"
    top_offset += (3 * PLAYWA_GV.TEXT_INTERNAL_OFFSET) / 2;
    al_draw_text(arr_fonts[2],
                 SHADOW_COLOR,
                 left_offset + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 2,
                 top_offset + GENERAL_GV.BACK_TEXT_SHADOW_GAP * 2,
                 ALLEGRO_ALIGN_LEFT,
                 "BONUS");
    al_draw_text(arr_fonts[2],
                 al_map_rgb(255, 255, 255),
                 left_offset,
                 top_offset,
                 ALLEGRO_ALIGN_LEFT,
                 "BONUS");
    // Stampa istruzioni bonus
    top_offset += PLAYWA_GV.TEXT_INTERNAL_OFFSET;
    al_draw_text(arr_fonts[3],
                 al_map_rgb(150, 150, 150),
                 left_offset,
                 top_offset,
                 ALLEGRO_ALIGN_LEFT,
                 bonus_instr[0]);
    top_offset += (3 * PLAYWA_GV.TEXT_INTERNAL_OFFSET) / 4;
    al_draw_text(arr_fonts[3],
                 al_map_rgb(150, 150, 150),
                 left_offset,
                 top_offset,
                 ALLEGRO_ALIGN_LEFT,
                 bonus_instr[1]);
    // Stampa bonus cases
    top_offset += PLAYWA_GV.TEXT_INTERNAL_OFFSET * 1.4;
    for (i = 0; i < 4; i++) {

        float this_case_left_offset = left_offset +
                                	  (i % 2 != 0 ? left_offset / 2 +
                                                    INSTR_GV.BONUS_CASE_WIDTH
                                                  : 0);
        float this_case_top_offset = top_offset +
                                	 (i > 1 ? (10 * INSTR_GV.BONUS_CASE_WIDTH) /
                                              33 : 0);
        // Stampa fondo bonus
        al_draw_scaled_bitmap(arr_bitmaps[1], 0, 0, 1200, 300,
                              this_case_left_offset, this_case_top_offset,
                              INSTR_GV.BONUS_CASE_WIDTH,
                              INSTR_GV.BONUS_CASE_WIDTH / 4, 0);
        // Stampa logo bonus
        al_draw_scaled_bitmap(arr_bitmaps[i + 2], 0, 0, 128, 128,
                              this_case_left_offset +
                              INSTR_GV.BONUS_CASE_WIDTH / 24,
                              this_case_top_offset +
                              INSTR_GV.BONUS_CASE_WIDTH / 24,
                              INSTR_GV.BONUS_RADIUS,
                              INSTR_GV.BONUS_RADIUS, 0);
        // Stampa nome bonus
        al_draw_text(arr_fonts[3], SHADOW_COLOR,
                     this_case_left_offset + INSTR_GV.BONUS_CASE_WIDTH / 3.8 +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 2,
                     this_case_top_offset + INSTR_GV.BONUS_CASE_WIDTH / 24 +
                     GENERAL_GV.BACK_TEXT_SHADOW_GAP * 2,
                     ALLEGRO_ALIGN_LEFT, arr_bonus_names[i]);
        al_draw_text(arr_fonts[3], al_map_rgb(255, 255, 255),
                     this_case_left_offset + INSTR_GV.BONUS_CASE_WIDTH / 3.8,
                     this_case_top_offset + INSTR_GV.BONUS_CASE_WIDTH / 24,
                     ALLEGRO_ALIGN_LEFT, arr_bonus_names[i]);
        // Stampa descrizione bonus
        al_draw_text(arr_fonts[3], al_map_rgb(150, 150, 150),
                     this_case_left_offset + INSTR_GV.BONUS_CASE_WIDTH / 3.8,
                     this_case_top_offset + INSTR_GV.BONUS_CASE_WIDTH / 11,
                     ALLEGRO_ALIGN_LEFT, arr_bonus_instr[i]);
        al_draw_text(arr_fonts[3], al_map_rgb(150, 150, 150),
                     this_case_left_offset + INSTR_GV.BONUS_CASE_WIDTH / 3.8,
                     this_case_top_offset + INSTR_GV.BONUS_CASE_WIDTH / 11 +
                     PLAYWA_GV.TEXT_INTERNAL_OFFSET / 2,
                     ALLEGRO_ALIGN_LEFT, arr_bonus_instr_2[i]);
        al_draw_text(arr_fonts[3], al_map_rgb(150, 150, 150),
                     this_case_left_offset + INSTR_GV.BONUS_CASE_WIDTH / 3.8,
                     this_case_top_offset + INSTR_GV.BONUS_CASE_WIDTH / 11 +
                     PLAYWA_GV.TEXT_INTERNAL_OFFSET,
                     ALLEGRO_ALIGN_LEFT, arr_bonus_instr_3[i]);
    }
}
