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
#include "../include/utils/point.h"
#include "../include/behaviours/entities&sprites/pacman.h"

typedef Ghosts Clyde;

/** 
 * Constructor for clyde
 * 
 * Clyde is set to be a singleton, meaning that only one instance of Clyde can exist at a time,
 * this prevents wasteful memory allocation and prevents bugs, 
 * also logically there should be only one instance of Clyde in the game.
 *
 * @param destroy a boolean that determines whether the function should destroy the existing clyde instead, and return null
 * @returns a pointer to the clyde struct, which contains all the information about clyde such as its current position, mode and scatter position
 */
Clyde* _clyde(bool destroy);

const Point* get_clyde_scatter_position();

const Point* get_clyde_position();

const Point* get_clyde_target_position();

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
 * @return the next position that Clyde is to move to based on its behaviour
*/
const Point _clyde_feed_next(const bool reset, const bool end);

const bool set_clyde_position(const uint8_t x, const uint8_t y);

const GhostMode get_clyde_mode();

const void set_clyde_mode(GhostMode mode);

const bool get_clyde_behaviour_change();

void set_clyde_behaviour_change(const bool change);

/** 
 * Destructor for clyde 
 * 
 * Frees the memory allocated for clyde and sets the pointer to null to prevent dangling pointers. 
 * This function should be called when clyde is no longer needed, such as when the game is exited or when clyde is reset.
*/
Clyde* destroy_clyde();


#endif