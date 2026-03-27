/**
 * This file includes the behaviours and movement patterns for blinky
 * 
 * Blinky (red ghost) has a more agressive chase
 * meaning he chases pac man directly 
*/

#ifndef _GHOST_BLINKY
#define _GHOST_BLINKY

#include "ghosts.h"
#include "../include/utils/point.h"
#include "../include/behaviours/entities&sprites/pacman.h"

typedef Ghosts Blinky;

Blinky* _blinky();

const Point* get_blinky_scatter_position();

const Point* get_blinky_position();

const Point* get_blinky_target_position();

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
 * end is a boolean that is sent to the function to free the cache... i.e in the case that the game is ended
*/
const Point* _blinky_feed_next(const bool reset, const bool end);

const bool set_blinky_position(const uint8_t x, const uint8_t y);

const GhostMode get_blinky_mode();

const void set_blinky_mode(GhostMode mode);

const bool get_blinky_behaviour_change();

void set_blinky_behaviour_change(const bool change);

Blinky* destroy_blinky();

#endif