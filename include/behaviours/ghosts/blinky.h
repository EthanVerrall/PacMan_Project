/**
 * This file includes the behaviours and movement patterns for blinky
 * 
 * Blinky (red ghost) has a more agressive chase
 * meaning he chases pac man directly 
*/

#ifndef _GHOST_BLINKY
#define _GHOST_BLINKY

#include "ghosts.h"
#include "../../point.h"

typedef Ghosts Blinky;

Point get_blinky_next_position(Blinky* blinky);

#endif