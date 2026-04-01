#ifndef DRAW_MANAGER
#define DRAW_MANAGER

//Requires all asset includes and display.h and grid.h -- This library handles and draws everything
#include "../assets/texture_include/blinky_textures.h"
#include "../assets/texture_include/clyde_textures.h"
#include "../assets/texture_include/inky_textures.h"
#include "../assets/texture_include/pacman_textures.h"
#include "../assets/texture_include/fright_ghost_textures.h"
#include "../assets/texture_include/pickups_textures.h"
#include "../assets/texture_include/pinky_textures.h"
#include "../assets/texture_include/wall_textures.h"
#include "../assets/texture_include/blank_textures.h"
#include "../assets/texture_include/main_menu_title.h"
#include "../include/behaviours/entities&sprites/pacman.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/inky.h"
#include "../include/behaviours/entities&sprites/pinky.h"
#include "../include/behaviours/entities&sprites/clyde.h"
#include "../include/grid.h"
#include "../include/frontend&drawing/display.h"
#include "../include/utils/point.h"
#include "../include/frontend&drawing/menu.h"
#include "../include/game_play/scoreboard.h"
#include <stdbool.h>
#include <stdint.h>

//Leaving open space at the top to account for the score during game time
#define HEIGHT_OFFSET 8

enum entity_type {

    entity_type_blinky = 1,
    entity_type_inky = 2,
    entity_type_pinky = 3,
    entity_type_clyde = 4,
    entity_type_pacman = 5
};

void move_entities(const Point point_array[], const enum entity_type entity_array[],
    const uint8_t num_entites_to_animate, bool is_ghost_eaten[]);

void eat_ghost(const enum entity_type ghost);

void draw_pacman_dying(const Point pac_current, const Point ghost_current, enum entity_type ghost);

void draw_current_page();

void flicker_text();

#endif //DRAW_MANAGER