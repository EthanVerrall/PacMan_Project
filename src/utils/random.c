#include "../include/utils/random.h"

uint64_t linear_congruence_rand(const uint32_t seed){
    static uint32_t iterator = 1;
    static uint64_t stored_seed = 0;

    if (iterator == 1 && stored_seed != seed) stored_seed = seed;

    //prevent zero division
    if (stored_seed == 0) stored_seed = 42; //use 42 for default seed
    
    //if we have reached the max range, we just reset to 2
    if (iterator == (1 << 16)) iterator = 2;

    for (uint32_t i = 0; i < iterator; i++)
        stored_seed = (((stored_seed * MLTP) + ADDER) % (MODDER));
    
    return stored_seed;
}


uint8_t get_random_number(uint32_t seed){
    if (!seed) seed = 42;
    uint64_t random_number = linear_congruence_rand(seed);

    return random_number % (1 << 8);
}

uint8_t get_random_number_in_range(uint32_t seed, const uint8_t start, const uint8_t end){
    if (!seed) seed = 42;
    uint64_t random_number = linear_congruence_rand(seed);

    return ((random_number % (1 << 8)) % (end + 1)) + start;
}