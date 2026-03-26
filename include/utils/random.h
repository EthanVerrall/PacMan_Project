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
*/
uint8_t get_random_number(uint32_t seed);

/** 
 * Gets a random number between the start and the end
 * start and end inclusive
*/
uint8_t get_random_number_in_range(uint32_t seed, uint8_t start, uint8_t end);

Point* get_random_point_on_grid(uint32_t seed);

#endif //!RANDOM_H