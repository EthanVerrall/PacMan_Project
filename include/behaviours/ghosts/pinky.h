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

const Pinky* _pinky();

const Point* get_pinky_scatter_position();

const Point* get_pinky_target_position();

const Point* get_pinky_position();

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _pinky_feed_next(const bool reset);

#endif