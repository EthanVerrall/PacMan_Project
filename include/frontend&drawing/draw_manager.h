#ifndef DRAW_MANAGER
#define DRAW_MANAGER

//This manager file needs all assets included to it, must be able to see where things are and what it is drawing
/*
    Include all ghosts and pacman

    Include the music to play delays in between animation frames

    Include all menus and main_menu texture

    Include the grid to track game state, needs to know where things are 
    positioned in order to draw to the screen at the correct spot.

    Include the scoreboard so we can access and draw it
*/

//This file also has many internal helper functions that cannot be used outside the .c 
//file and are therefore not defined here in the header to encapsulate them

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
#include "../include/music&sound/tones.h"
#include <stdbool.h>
#include <stdint.h>

//Leaving open space at the top to account for the score during game time
#define HEIGHT_OFFSET 8

//The different types of entites we are drawing during game time
//This helps us know which point relates to which texture when being drawn during the game
enum entity_type {

    entity_type_blinky = 1,
    entity_type_inky = 2,
    entity_type_pinky = 3,
    entity_type_clyde = 4,
    entity_type_pacman = 5
};

/*
    This function is very important.

    This function handles all live gameplay movement, it takes in a collection of paired points
    being source and target, notes what entity relates to the current pair, if that entity is being eaten by pacman
    and then figures out direction so we know which correct texture to pick based on direction as well.
    For example ghosts eyes look in the direction they are moving.
*/
void move_entities(const Point point_array[], const enum entity_type entity_array[],
    const uint8_t num_entites_to_animate, bool is_ghost_eaten[]);

//This function just redraws eaten ghosts in their correct starting spot in the cage/box that is in the middle of the screen
void eat_ghost(const enum entity_type ghost);

//Plays a cool animation where the ghost goes over pacman and eats him before we deduct a life and start a new round
void draw_pacman_dying(const Point pac_current, const Point ghost_current, enum entity_type ghost);

//Calling this function will redraw the current active menu
void draw_current_page();

//This function is used to make text flash yellow and blue based on either cursor position or unique menu details
void flicker_text();

#endif //DRAW_MANAGER