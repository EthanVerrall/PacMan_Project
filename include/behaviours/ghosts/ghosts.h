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

#include "../../point.h"
#include <stdlib.h>


typedef enum {
    chase,
    scatter,
    fright
} GhostMode;

typedef struct
{
    char ghost_type;
    Point* position;
    GhostMode currentMode;
    Point* scatter_position;
} Ghosts;

Ghosts* create_ghost(
    const char ghost_type,
    Point* current_position,
    GhostMode current_mode,
    const Point* scatter_pos
);

void delete_ghost(Ghosts* ghost_to_delete);

const Point* get_ghost_scatter_position(Ghosts* ghost);

const Point* get_ghost_position(Ghosts* ghost);


#endif