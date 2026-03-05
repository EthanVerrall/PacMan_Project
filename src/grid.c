#include "../include/grid.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
128 by 160
the score at the top will be 16 pixels in height
grid must fit 128 by 144
4*4 pixels = one tile
grid array is now [32][36] = 1152 bytes
each array element is a uint8_t for a bitmask tracking the games pixels/state
Sprites will therefore move by 4 units of x and y when moving since they will be drawn to fill an entire tile
*/

struct Grid {

    uint8_t grid_index [GRID_TILE_ROW][GRID_TILE_COL]; 
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

    uint8_t cols_entered = 0;


    const uint8_t grid_pattern[] = 
    {   
        //First row - one above the board
        blank, 28, 

        //Second row - row of walls
        wall, 28,

        //Third row
        wall, 1, pellet, 12, wall, 2, pellet, 12, wall, 1,

        //Fourth row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 5, pellet, 1, wall, 2, pellet, 1, wall, 5, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //Fith row
        

    };

}
