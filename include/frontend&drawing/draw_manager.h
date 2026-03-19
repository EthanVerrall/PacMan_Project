#ifndef DRAW_MANAGER
#define DRAW_MANAGER

//Requires all asset includes and display.h and grid.h -- This library handle and draw everything
#include "../assets/texture_include/blinky_textures.h"
#include "../assets/texture_include/clyde_textures.h"
#include "../assets/texture_include/inky_textures.h"
#include "../assets/texture_include/pacman_textures.h"
#include "../assets/texture_include/pickups_textures.h"
#include "../assets/texture_include/pinky_textures.h"
#include "../assets/texture_include/wall_textures.h"
#include "../assets/texture_include/blank_textures.h"
#include "../include/grid.h"
#include "../include/frontend&drawing/display.h"
#include "../include/utils/point.h"
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

//Function to draw the starting state of the game, only use this once per game.
bool draw_starting_grid ();

void move_entities(const Point* const point_array[], const enum entity_type entity_array[], const uint8_t num_entites_to_animate);

#endif //DRAW_MANAGER