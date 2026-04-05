/**
 * This file includes the behaviours and movement patterns for pinky 
 * 
 * Pinky (ghost) has a strategic chase
 * she predicts where pac man would likely go to.. and tries to intercept
*/

#ifndef _GHOST_PINKY
#define _GHOST_PINKY

#include "ghosts.h"
#include "../include/utils/point.h"
#include "../include/behaviours/entities&sprites/pacman.h"

typedef Ghosts Pinky;

/** 
 * Constructor for pinky
 * 
 * Pinky is set to be a singleton, meaning that only one instance of Pinky can exist at a time,
 * this prevents wasteful memory allocation and prevents bugs, 
 * also logically there should be only one instance of Pinky in the game.
 *
 * @param destroy a boolean that determines whether the function should destroy the existing pinky instead, and return null
 * @returns a pointer to the pinky struct, which contains all the information about pinky such as its current position, mode and scatter position
 */
Pinky* _pinky(bool destroy);

const Point* get_pinky_scatter_position();

const Point* get_pinky_target_position();

const Point* get_pinky_position();

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
 * @return the next position that Pinky is to move to based on its behaviour
*/
const Point _pinky_feed_next(const bool reset, const bool end);

const bool set_pinky_position(const uint8_t x, const uint8_t y);

const GhostMode get_pinky_mode();

const void set_pinky_mode(GhostMode mode);

const bool get_pinky_behaviour_change();

void set_pinky_behaviour_change(const bool change);

/** 
 * Destructor for pinky 
 * 
 * Frees the memory allocated for pinky and sets the pointer to null to prevent dangling pointers. 
 * This function should be called when pinky is no longer needed, such as when the game is exited or when pinky is reset.
*/
Pinky* destroy_pinky();

#endif