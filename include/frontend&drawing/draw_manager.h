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
#include <stdbool.h>

//Leaving open space at the top to account for the score during game time
#define HEIGHT_OFFSET 8

//Function to draw the starting state of the game, only use this once per game.
bool draw_starting_grid ();

#endif //DRAW_MANAGER