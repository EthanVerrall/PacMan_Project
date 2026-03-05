#include "../include/grid.h"
#include <stdint.h>
#include <stdlib.h>

struct Grid {

    uint8_t grid_index [grid_rows][grid_cols]; 
};

Grid* get_instance() {

    static Grid* singleton_grid = NULL;

    //Creating a new grid, since we don't have one yet
    if (!singleton_grid) {

        singleton_grid = calloc(1,sizeof(Grid));

        //Checking if calloc failed
        if (!singleton_grid) {

            printf("Error with creating a grid. Calloc failed, function returned NULL.\n");
            return NULL;
        } 
        //Calloc succeeded, return the address of our static heap grid
        //Also fill grid with default state, so the game can start the same always
        else {
            //Grid was able to default with starting game state
            if(!set_reset_grid(singleton_grid)){

            //Grid failed to default initialse but created properly on the heap
            //print a message to state so
            printf("Grid was created but failed to initialize with starting game state values.\n");

            }
            return singleton_grid;
        }

    } 
    //Grid already exists - just return it
    else {
        return singleton_grid;
    }  
}

bool set_reset_grid(Grid* const singleton_grid) {

    
}

void update_grid_position_type(const uint8_t grid_index[][], const uint8_t state_bit_mask) {

    
} 

Grid* destroy_grid(Grid* _grid) {

    if (!_grid) {

        printf("Your grid was already NULL, nothing to free.\n");
    }

    free(_grid);
    return NULL;
}