#include "../include/utils/random.h"

uint64_t linear_congruence_rand(const uint32_t seed){
    static uint32_t iterator = 1;
    static uint64_t stored_seed = 0;

    if (iterator == 1 && stored_seed != seed) stored_seed = seed;

    //prevent zero division
    if (stored_seed == 0) stored_seed = 42; //use 42 for default seed
    
    //if we have reached the max range, we just reset to 2
    if (iterator == (1 << 16)) iterator = 2;

    stored_seed = (((stored_seed * MLTP) + ADDER) % (MODDER));

    iterator++;
    
    return stored_seed;
}


uint8_t get_random_number(uint32_t seed){
    if (!seed) seed = 42;
    uint64_t random_number = linear_congruence_rand(seed);

    return random_number % (1 << 8);
}

uint8_t get_random_number_in_range(uint32_t seed, uint8_t start, uint8_t end){
    if (start > end) {
        //if the start is greater than the end, just swap them and continue on
        uint8_t tmp = start;
        start = end;
        end = tmp;
    }

    if (!seed) seed = 42;

    uint64_t random_number = linear_congruence_rand(seed);

    uint8_t range = end - start + 1;

    return (random_number % range) + start;
}

Point* get_random_point_on_grid(uint32_t seed){
    //select a random point on the board range
    //ensuring we do not check outside the board range on search for empty spot
    uint8_t rand_x = get_random_number_in_range(seed, 2, GRID_ROW_COUNT - 2);
    uint8_t rand_y = get_random_number_in_range(seed, 1, GRID_COL_COUNT - 2);

    //check that the range is not a wall
    if(!has_grid_state(rand_x,rand_y, cell_wall)) return create_point(rand_x, rand_y);

    //if it ends up being a wall, check around the wall
    for (int8_t i = -1; i <= 1; i++) {
        for (int8_t j = -1; j <= 1; j++){
            //our current spot already, which is a wall
            if (i == 0 && j == 0) continue;

            //we don't need to check for boundaries here, as we get a number that is inward enough to not cross boundaries
            if(!has_grid_state(rand_x + i,rand_y + j, cell_wall)) return create_point(rand_x + i,rand_y + j);
        }
    }

    //return NULL if all areas around wall are also walls, which is highly unlikely for the game
    return NULL;
    
}