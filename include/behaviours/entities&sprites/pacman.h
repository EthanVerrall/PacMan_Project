#ifndef PACMAN_H
#define PACMAN_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/utils/point.h"

//Pacman direction is used to determine the direction of pacman, essentially where pacman should move to next on the grid
typedef enum {
    PAC_LEFT,
    PAC_TOP,
    PAC_RIGHT,
    PAC_BOTTOM,
    PAC_NONE
} PacDirection;

//Pacman state is used to determine the state of pacman, essentially whether pacman can eat ghosts or not, and whether ghosts can eat pacman or not
typedef enum{
    God, Mortal
}PacState;

//pacman definition
typedef struct Pacman Pacman;

/** 
 * Constructor for pacman
 * 
 * Pacman is set to be a singleton, meaning that only one instance of Pacman can exist at a time,
 * this prevents wasteful memory allocation and prevents bugs, 
 * also logically there should be only one instance of Pacman in the game
 * *
 * @param destroy a boolean that determines whether the function should destroy the existing pacman instead,
 * and return null, this is used when pacman dies and needs to be reset, or when the game is exited and pacman needs to be destroyed to free memory
 * @returns a pointer to the pacman struct, which contains all the information about pacman
 * */
Pacman* _pacman(bool destroy);

PacState get_pacman_state();

void set_pacman_state(const PacState newstate);

Point* get_pacman_position();

void set_pacman_position(const uint8_t x, const uint8_t y);

/**
 * Get the direction of pacman
 * 
 * Pacman's direction is based on his change in dy and dx, which are determined by the direction that the player inputs, 
 * and whether pacman is able to move in that direction or not
 * 
 * @returns the direction of pacman, which is an enum value of type PacDirection, which can be PAC_LEFT, PAC_TOP, PAC_RIGHT, PAC_BOTTOM or PAC_NONE
 * PAC_NONE is used when pacman is not moving, which can be the case at the start of the game, or when pacman is colliding with a wall 
 */
PacDirection get_pacman_direction();

void set_pacman_direction(const PacDirection newdirection);

/**
 * Get the x velocity of pacman
 * 
 * Pacman's velocity is determined by his direction, 
 * if pacman is moving left or right, his velocity in the x direction is -1 or 1 respectively, 
 * and if pacman is moving up or down, his velocity in the x direction is 0
 * 
 * @returns the x velocity of pacman, which is an 8 bit signed integer, which can be -1, 0 or 1
 */
int8_t get_pac_dx();

/**
 * Get the y velocity of pacman
 * 
 * Pacman's velocity is determined by his direction, 
 * if pacman is moving up or down, his velocity in the y direction is -1 or 1 respectively, 
 * and if pacman is moving left or right, his velocity in the y direction is 0
 * 
 * @returns the y velocity of pacman, which is an 8 bit signed integer, which can be -1, 0 or 1
 */
int8_t get_pac_dy();

/**
 * Get the number of lives that pacman has left
 * 
 * Pacman starts with 4 lives, and loses a life when he collides with a ghost while he is in mortal state,
 * when pacman loses all his lives, the game is over and pacman needs to be reset to start a new game
 */
uint8_t get_pacman_life();

/** 
 * Sets the lives pacman has left
 * Pacman starts with 4 lives, and loses a life if he collides with a ghost in his mortal state
 * 
 * Checks for a valid decrease in pacman's life, i.e you can only decrease his life by 1,
 * also checks for a valid life value, which is betweeen 0 and 4
*/
void set_pacman_life(uint8_t life);


/**
 * Destructor for pacman
 * Frees the memory allocated for pacman and sets the pointer to null to prevent dangling pointers.
 * This function should be called when pacman is no longer needed, such as when the game is exited or when pacman is reset.
 */
Pacman* destroy_pacman();



#endif//!PACMAN_H