/**
 * This file includes the behaviours and movement patterns for clyde
 * 
 * @note From the Wiki
 * Clyde actually does directly chase Pac-Man (exactly the way Blinky does) most of the time.
 *  But when Clyde gets within an eight-space radius of Pac-Man, he starts to retreat to the lower-left corner of the maze, which is where he targets during "scatter" mode.
*/

#ifndef _GHOST_CLYDE
#define _GHOST_CLYDE

#include "ghosts.h"
#include "../../point.h"

typedef Ghosts Clyde;

Point* get_clyde_target_position(Clyde* clyde);
#endif