/**
 * This file includes the structures and types for ghosts
 * 
 * Blinky (red ghost) has a more agressive chase meaning he chases pac man directly 
*/

#ifndef _GHOSTS_H
#define _GHOSTS_H

//check for pacman creation
#ifdef PACMAN_H
   typedef Pacman Pacman;
#endif

#define MAX_FEED_CAPACITY 50

#include "../include/utils/point.h"
#include "../include/utils/arr.h"
#include "../include/utils/random.h"
#include "../include/behaviours/algo.h"
#include "../include/grid.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Ghosts Ghosts;

//Ghost mode is used to determine the behaviour of the ghost, and therefore the algorithm it uses to chase pacman
typedef enum {
    chase,
    scatter,
    fright
} GhostMode;

//This is the "constructor" function for the ghost, it creates a new ghost with the given parameters and returns a pointer to it
Ghosts* create_ghost(
    char ghost_type, //B for blinky, P for pinky, I for inky and C for clyde
    Point* current_position, //current position of the ghost on the grid
    GhostMode current_mode, //current mode of the ghost, which determines its behaviour
    Point* scatter_pos, //ghosts constant scatter position on the grid, which is the position the ghost goes to when it is in scatter mode
    bool is_behaviour_changed // keep track of whether the ghost has changed its behaviour since the last time it was in scatter mode, used to determine whether the ghost should change its target when it is in chase mode
);

void delete_ghost(Ghosts* ghost_to_delete);

//this cannot be reset... and is only initialized in the create ghost "constructor" function
const Point* get_ghost_scatter_position(const Ghosts* ghost);

/** 
 * Get the current position of the ghost, which is used to determine the next move of the ghost and to draw the ghost on the screen
 * 
 * @param ghost a pointer to the ghost struct, which contains the current position of the ghost on the grid
 * @return a pointer to the current position of the ghost, which is a Point struct containing the x and y coordinates of the ghost on the grid
*/
const Point* get_ghost_position(const Ghosts* ghost);

/** 
 * Set the current position of the ghost, which is used to update the position of the ghost on the grid and to draw the ghost on the screen
 * 
 * @param ghost a pointer to the ghost struct, which contains the current position of the ghost on the grid
 * @param x the new x coordinate of the ghost on the grid, which is an unsigned 8 bit integer valid grid point
 * @param y the new y coordinate of the ghost on the grid, which is an unsigned 8 bit integer valid grid point
 * @return true if the position was successfully updated, and false if the position was not updateds
*/
const bool set_ghost_position(Ghosts* ghost, const uint8_t x, const uint8_t y);

/**
 * Get the current mode of the ghost, which is used to determine its behaviour
 * 
 * @param ghost a pointer to the ghost struct, which contains the current mode of the ghost
 * @return the current mode of the ghost, which is a GhostMode enum value
*/
const GhostMode get_ghost_mode(const Ghosts* ghost);

/** Set the current mode of the ghost, which is used to determine its behaviour
 * 
 * @param ghost a pointer to the ghost struct, which contains the current mode of the ghost
 * @param mode the new mode of the ghost, which is a GhostMode enum value
 * @return true if the mode was successfully updated, and false if the mode was not updated
*/
const void set_ghost_mode(Ghosts* ghost,const GhostMode mode);

/**
 * Get the type of the ghost. This is used to determine the behaviour of the ghost in the chase mode
 *
 * B for blinky, P for pinky, I for inky and C for clyde 
 * 
 * @param ghost a pointer to the ghost struct, which contains the type of the ghost
 * @return the type of the ghost, which is a char value representing the ghost type
*/
const char get_ghost_type(const Ghosts* ghost);

/** 
 * Get whether the ghost has changed its behaviour since the last time it was in scatter mode, which is used to determine whether the ghost should change its target 
 * This is used to force a cache reset for the ghosts feed path, so that the ghost can update its target when it is in chase mode, and therefore change its behaviour accordingly
 * 
 * @param ghost a pointer to the ghost struct, which contains the is_behaviour_changed variable of the ghost
 * @return true if the ghost has changed its behaviour since the last time it was in scatter or chase mode
*/
const bool get_ghost_behaviour_change(const Ghosts* ghost);

/** 
 * Sets the ghosts behaviour change, which would be used to force cache resets, or maybe change other metadata about the ghost
 * 
 * @param ghost a pointer to the ghost struct, which contains the is_behaviour_changed variable of the ghost
 * @param is_behaviour_changed the new value for the is_behaviour_changed variable of the ghost
*/
void set_ghost_behaviour(Ghosts* ghost,const bool is_behaviour_changed);


#endif