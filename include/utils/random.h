#ifndef RANDOM_H
#define RANDOM_H

#define MLTP 1664525
#define ADDER 1013904223
//our modder would be a uint32_t 
#define MODDER (1 << 16)

#include <stdint.h>
#include "./point.h"
#include "../grid.h"

uint64_t linear_congruence_rand(uint32_t seed);

/** 
 * Gets a random number using the linear_congruence algorithm
 * 
 * The random number is said to be pseudo random because it is generated using a deterministic algorithm,
 * which means that if you provide the same seed, you will get the same random number
*/
uint8_t get_random_number(uint32_t seed);

/** 
 * Gets a random number between the start and the end
 * start and end inclusive
 * 
 * The random number is generated using the linear_congruence algorithm and the seed provided
 * The random number is guaranteed to be between the start and the end inclusive
*/
uint8_t get_random_number_in_range(uint32_t seed, uint8_t start, uint8_t end);

/** 
 * Gets a random point on the grid using the seed provided and the linear_congruence algorithm
 * The point is guaranteed to be a valid point on the grid,
 * which means it is guaranteed to be within the grid and is guaranteed to not be a wall
 * The point on the grid is not guaranteed to not be in the ghost house, so it may land in the ghost house,
 * In the case that that is not desired, the programmer can check if the point is in the ghost house and if it is, 
 * call the function again with a different seed until they get a point that is not in the ghost house 
*/
Point* get_random_point_on_grid(uint32_t seed);

#endif //!RANDOM_H