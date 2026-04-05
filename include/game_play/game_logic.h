#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../include/behaviours/entities&sprites/pacman.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/clyde.h"
#include "../include/behaviours/entities&sprites/pinky.h"
#include "../include/behaviours/entities&sprites/inky.h"

#include "../include/grid.h"
#include "../include/utils/point.h"

#include "../include/frontend&drawing/draw_manager.h"

#include "../include/music&sound/tones.h"
#include "../include/serial.h"
#include "../include/utils/events.h"

/*
    This function starts the game, it sets up all ghosts and pacman
    Creates a new grid, creates caches for our A* Algorithms to use
    Creates all other variables on the stack to track gameplay
    
    //Further helper functions are encapsulated in the c file
*/
void play_game();

#endif //!GAME_LOGIC_H