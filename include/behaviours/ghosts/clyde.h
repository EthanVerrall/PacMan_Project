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

const Clyde* _clyde();

const Point* get_clyde_scatter_position();

const Point* get_clyde_position();

const Point* get_clyde_target_position();

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _clyde_feed_next(const bool reset);
#endif