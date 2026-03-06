/**
 * This file includes the behaviours and movement patterns for Inky
*/

#ifndef _GHOST_INKY
#define _GHOST_INKY

#include "ghosts.h"
#include "../../point.h"

typedef Ghosts Inky;

const Inky* _inky();

const Point* get_inky_scatter_position();

const Point* get_inky_position();

const Point* get_inky_target_position();


#endif