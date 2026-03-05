#include "../include/grid.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
128 by 160
the score at the top will be 16 pixels in height
grid must fit 128 by 144
4*4 pixels = one tile
grid array is now [28][32] = 896 bytes
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
        //1st row - one above the board
        blank, 28, 

        //2nd row - row of walls
        wall, 28,

        //3rd row
        wall, 1, pellet, 12, wall, 2, pellet, 12, wall, 1,

        //4th row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 5, pellet, 1, wall, 2, pellet, 1, wall, 5, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //5th row
        wall, 1, power_up, 1, wall, 4, pellet, 1, wall, 5, pellet, 1, wall, 2, pellet, 1, wall, 5, pellet, 1, wall, 4, power_up, 1, wall, 1,

        //6th row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 5, pellet, 1, wall, 2, pellet, 1, wall, 5, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //7th row
        wall, 1, pellet, 26, wall, 1,

        //8th row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 2, pellet, 1, wall, 8, pellet, 1, wall, 2, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //9th row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 2, pellet, 1, wall, 8, pellet, 1, wall, 2, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //10th row
        wall, 1, pellet, 6, wall, 2, pellet, 4, wall, 2, pellet, 4, wall, 2, pellet, 6, wall, 1,

        //11th row
        wall, 6, pellet, 1, wall, 5, blank, 1, wall, 2, blank, 1, wall, 5, pellet, 1, wall, 6,

        //12th row
        blank, 5, wall, 1, pellet, 1, wall, 5, blank, 1, wall, 2, blank, 1, wall, 5, pellet, 1, wall, 1, blank, 5,

        //13th row
        blank, 5, wall, 1, pellet, 1, wall, 2, blank, 4, ghost, 2, blank, 4, wall, 2, pellet, 1, wall, 1, blank, 5,

        //14th row
        blank, 5, wall, 1, pellet, 1, wall, 2, blank, 1, wall, 3, gate, 2, wall, 3, blank, 1, wall, 2, pellet, 1, wall, 1, blank, 5,

        //15th row
        wall, 6, pellet, 1, wall, 2, blank, 1, wall, 1, blank, 6, wall, 1, blank, 1, wall, 2, pellet, 1, wall, 6,

        //16th row
        blank, 6, pellet, 1, blank, 3, wall, 1, ghost, 6, wall, 1, blank, 3, pellet, 1, blank, 6,

        //17th row,
        wall, 6, pellet, 1, wall, 2, blank, 1, wall, 1, blank, 6, wall, 1, blank, 1, wall, 2, pellet, 1, wall, 6,

        //18th row
        blank, 5, wall, 1, pellet, 1, wall, 2, blank, 1, wall, 8, blank, 1, wall, 2, pellet, 1, wall, 1, blank, 5,

        //19th row
        blank, 5, wall, 1, pellet, 1, wall, 2, blank, 10, wall, 2, pellet, 1, wall, 1, blank, 5,

        //20th row
        blank, 5, wall, 1, pellet, 1, wall, 2, blank, 10, wall, 2, pellet, 1, wall, 1, blank, 5,

        //21st row
        wall, 6, pellet, 1, wall, 2, blank, 1, wall, 8, blank, 1, wall, 2, pellet, 1, wall, 6,

        //22nd row
        wall, 1, pellet, 12, wall, 2, pellet, 12, wall, 1,

        //23rd row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 5, pellet, 1, wall, 2, pellet, 1, wall, 5, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //24th row
        wall, 1, pellet, 1, wall, 4, pellet, 1, wall, 5, pellet, 1, wall, 2, pellet, 1, wall, 5, pellet, 1, wall, 4, pellet, 1, wall, 1,

        //25th row
        wall, 1, power_up, 1, pellet, 2, wall, 2, pellet, 7, pacman, 2, pellet, 7, wall, 2, pellet, 2, power_up, 1, wall, 1,

        //26th row
        wall, 3, pellet, 1, wall, 2, pellet, 1, wall, 2, pellet, 1, wall, 8, pellet, 1, wall, 2, pellet, 1, wall, 2, pellet, 1, wall, 3,

        //27th row
        wall, 3, pellet, 1, wall, 2, pellet, 1, wall, 2, pellet, 1, wall, 8, pellet, 1, wall, 2, pellet, 1,wall, 2,pellet, 1,wall, 3,

        //28th row
        wall, 1, pellet, 6, wall, 2, pellet, 4, wall, 2, pellet, 4,wall, 2,pellet, 6, wall, 1,

        //29th row
        wall, 1, pellet, 1, wall, 10, pellet, 1, wall, 2, pellet, 1, wall, 10, pellet, 1, wall, 1,

        //30th row
        wall, 1, pellet, 1, wall, 10, pellet, 1, wall, 2, pellet, 1, wall, 10, pellet, 1, wall, 1,

        //31st row
        wall, 1, pellet, 26, wall, 1,

        //32nd row
        wall, 28
    };

    

}
