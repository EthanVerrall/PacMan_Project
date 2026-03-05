/**
 * This file includes the behaviours and movement patterns for pinky 
 * 
 * Pinky (ghost) has a strategic chase
 * she predicts where pac man would likely go to.. and tries to intercept
*/

#ifndef _GHOST_PINKY
#define _GHOST_PINKY

#include "ghosts.h"
#include "../../point.h"

typedef Ghosts Pinky;

Point* get_pinky_target_position(Pinky* pinky);

#endif