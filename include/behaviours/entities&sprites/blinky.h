/**
 * This file includes the behaviours and movement patterns for blinky
 * 
 * Blinky is the most basic ghost, he simply chases pacman directly in chase mode, 
 * and goes to his scatter position in scatter mode, 
 * and runs to a random position on the grid in fright mode
*/

#ifndef _GHOST_BLINKY
#define _GHOST_BLINKY

#include "ghosts.h"
#include "../include/utils/point.h"
#include "../include/behaviours/entities&sprites/pacman.h"

typedef Ghosts Blinky;

/** 
 * Constructor for blinky
 * 
 * Blinky is set to be a singleton, meaning that only one instance of Blinky can exist at a time,
 * this prevents wasteful memory allocation and prevents bugs, 
 * also logically there should be only one instance of Blinky in the game.
 *
 * @param destroy a boolean that determines whether the function should destroy the existing blinky instead, and return null
 * @returns a pointer to the blinky struct, which contains all the information about blinky such as its current position, mode and scatter position
 */
Blinky* _blinky(bool destroy);

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
 * 
 * @param reset a boolean that determines if the function should force a call to the pathfinding algorithm or it should use the cache
 * @param end a boolean that is sent to the function to free the cache... i.e in the case that the game is ended
 * @return the next position that Blinky is to move to based on its behaviour
*/
Point _blinky_feed_next(const bool reset, const bool end);

const bool set_blinky_position(const uint8_t x, const uint8_t y);

const GhostMode get_blinky_mode();

const void set_blinky_mode(GhostMode mode);

const bool get_blinky_behaviour_change();

void set_blinky_behaviour_change(const bool change);

/** 
 * Destructor for blinky 
 * 
 * Frees the memory allocated for blinky and sets the pointer to null to prevent dangling pointers. 
 * This function should be called when blinky is no longer needed, such as when the game is exited or when blinky is reset.
*/
Blinky* destroy_blinky();

#endif