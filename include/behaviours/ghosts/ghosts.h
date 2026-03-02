/**
 * This file includes the structures and types for ghosts
 * 
 * Blinky (red ghost) has a more agressive chase
 * meaning he chases pac man directly 
*/

#ifndef _GHOSTS_H
#define _GHOSTS_H

#include "../../point.h"

typedef struct
{
    char ghost_type;
    Point* position;
} Ghosts;


#endif