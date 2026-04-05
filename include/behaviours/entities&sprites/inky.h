/**
 * This file includes the behaviours and movement patterns for Inky
 * 
 * Inky is the most unpredictable ghost, he has a unique chase behaviour where he targets a position that is determined by both pacmans position and blinky's position,
 * in scatter mode he goes to his scatter position, and in fright mode he runs to a random position on the grid
*/

#ifndef _GHOST_INKYs
#define _GHOST_INKY

#include "ghosts.h"
#include "../include/utils/point.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/pacman.h"

typedef Ghosts Inky;

/** 
 * Constructor for inky
 * 
 * Inky is set to be a singleton, meaning that only one instance of Inky can exist at a time,
 * this prevents wasteful memory allocation and prevents bugs, 
 * also logically there should be only one instance of Inky in the game.
 *
 * @param destroy a boolean that determines whether the function should destroy the existing inky instead, and return null
 * @returns a pointer to the inky struct, which contains all the information about inky such as its current position, mode and scatter position
 */
Inky* _inky(bool destroy);

const Point* get_inky_scatter_position();

const Point* get_inky_position();

const Point* get_inky_target_position();

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
 * @return the next position that Inky is to move to based on its behaviour
*/
const Point _inky_feed_next(const bool reset, const bool end);

const bool set_inky_position(const uint8_t x, const uint8_t y);

const GhostMode get_inky_mode();

const void set_inky_mode(GhostMode mode);

const bool get_inky_behaviour_change();

void set_inky_behaviour_change(const bool change);

/** 
 * Destructor for inky 
 * 
 * Frees the memory allocated for inky and sets the pointer to null to prevent dangling pointers. 
 * This function should be called when inky is no longer needed, such as when the game is exited or when inky is reset.
*/
Inky* destroy_inky();


#endif