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
#include "../include/behaviours/algo.h"
#include "../include/grid.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Ghosts Ghosts;

typedef enum {
    chase,
    scatter,
    fright
} GhostMode;

Ghosts* create_ghost(
    char ghost_type,
    Point* current_position,
    GhostMode current_mode,
    Point* scatter_pos
);

void delete_ghost(Ghosts* ghost_to_delete);

//this cannot be reset... and is only initialized in the create ghost "constructor" function
const Point* get_ghost_scatter_position(const Ghosts* ghost);

const Point* get_ghost_position(const Ghosts* ghost);

const bool set_ghost_position(Ghosts* ghost, const uint8_t x, const uint8_t y);

const GhostMode get_ghost_mode(const Ghosts* ghost);

const void set_ghost_mode(Ghosts* ghost,const GhostMode mode);

/**
 * Get the type of the ghost. This is used to determine the behaviour of the ghost in the chase mode
 *
 * B for blinky, P for pinky, I for inky and C for clyde 
*/
const char get_ghost_type(const Ghosts* ghost);


#endif