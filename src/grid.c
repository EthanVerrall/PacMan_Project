#include "../include/grid.h"
#include "../include/serial.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Global variable to store our one and only grid
//The entire file always needs to see the state of this pointer, this is the cleanest and simplest solution
static Grid* singleton_grid = NULL;   

struct Grid {

    uint8_t grid_index [GRID_ROW_COUNT][GRID_COL_COUNT]; 
};

//Internal Helper function - used to create a new grid on the heap (SINGLETON)
bool create_singleton_grid() {

    //Cannot create a new grid if we already have one
    if (singleton_grid) {

        eputs("Cannot create a new grid, grid is already pointing to valid heap memory.\r\n");
        return false;
    }
    //Making a new grid on the heap
    else {
        
        singleton_grid = malloc(sizeof(Grid));

        if (!singleton_grid) {

            eputs("Error in creating a new grid, function malloc failed to allocate memory!\r\n");
            return false;
        }

        return true;
    }
}

bool create_reset_grid() {

    //Checking if a grid already exists -- otherwise create a new one
    if (!singleton_grid) {

        if (!create_singleton_grid()) {
            eputs("Function create_reset_grid failed!\nGrid was unable to be created.\r\n");
            return false;
        }
    }

    //Original states that the board/grid will always start with 
    const uint8_t grid_pattern[] = 
    {   
        //1st row -- one above the board -- The score goes here
        cell_blank, 16,

        //2nd row -- row of walls top edge of the board/grid
        cell_wall, 16,

        //3rd row
        cell_wall, 1, cell_power_up, 1, cell_pellet, 12, cell_power_up, 1, cell_wall, 1,

        //4th row
        cell_wall, 1, cell_pellet, 1, cell_wall, 2, cell_pellet, 1, cell_wall, 1, cell_pellet, 1, 
        cell_wall, 2, 
        cell_pellet, 1, cell_wall, 1, cell_pellet, 1, cell_wall, 2, cell_pellet, 1, cell_wall, 1,

        //5th row
        cell_wall, 1, cell_pellet, 1, cell_wall, 2, cell_pellet, 1, cell_wall, 1,
        cell_pellet, 4,
        cell_wall, 1, cell_pellet, 1, cell_wall, 2, cell_pellet, 1, cell_wall, 1,

        //6th row
        cell_wall, 1, cell_pellet, 4, cell_wall, 1, cell_pellet, 1,
        cell_wall, 2,
        cell_pellet, 1, cell_wall, 1, cell_pellet, 4, cell_wall, 1,

        //7th row
        cell_wall, 1, cell_pellet, 1, cell_wall, 2, cell_pellet, 3, 
        cell_wall, 2,
        cell_pellet, 3, cell_wall, 2, cell_pellet, 1, cell_wall, 1,

        //8th row
        cell_wall, 1, cell_pellet, 4, 
        cell_wall, 6,
        cell_pellet, 4, cell_wall, 1,

        //9th row
        cell_wall, 4, cell_pellet, 1, cell_blank, 6, cell_pellet, 1, cell_wall, 4,

        //10th row
        cell_wall, 4, cell_pellet, 1, cell_wall, 2, 
        cell_gate, 2, 
        cell_wall, 2, cell_pellet, 1, cell_wall, 4,

        //11th row -- middle of the board/grid pacman can wrap to the other side in this row
        cell_blank, 4, cell_pellet, 1, cell_wall, 1, 
        cell_blank|cell_ghost, 4, //--Ghosts will draw on top of the board
        cell_wall, 1, cell_pellet, 1, cell_blank, 4,

        //12th row
        cell_wall, 4, cell_pellet, 1, cell_wall, 6, cell_pellet, 1, cell_wall, 4,

        //13th row -- this row has the cherry, cherry will spawn more left in the row
        cell_wall, 4, cell_pellet, 1, cell_blank, 2, 
        cell_cherry, 1, 
        cell_blank, 3, cell_pellet, 1, cell_wall, 4,

        //14th row
        cell_wall, 1, cell_pellet, 4, cell_wall, 1, cell_pellet, 1,
        cell_wall, 2,
        cell_pellet, 1, cell_wall, 1, cell_pellet, 4, cell_wall, 1,

        //15th row
        cell_wall, 1, cell_pellet, 1, cell_wall, 4, cell_pellet, 1,
        cell_wall, 2,
        cell_pellet, 1, cell_wall, 4, cell_pellet, 1, cell_wall, 1,

        //16th row -- this row has pacman, he will also spawn more to the left, same column as the cherry
        cell_wall, 1, cell_pellet, 3, cell_wall, 1, cell_pellet, 2, 
        cell_blank|cell_pacman, 1, //Pacman will draw on top of the board
        cell_pellet, 3, cell_wall, 1, cell_pellet, 3, cell_wall, 1,

        //17th row,
        cell_wall, 1, cell_pellet, 1, cell_wall, 1, cell_pellet, 3, 
        cell_wall, 4, 
        cell_pellet, 3, cell_wall, 1, cell_pellet, 1, cell_wall, 1,

        //18th row
        cell_wall, 1, cell_pellet, 1, cell_wall, 3, 
        cell_pellet, 6,
        cell_wall, 3, cell_pellet, 1, cell_wall, 1,

        //19th row
        cell_wall, 1, cell_power_up, 1, cell_pellet, 4,
        cell_wall, 4,
        cell_pellet, 4, cell_power_up, 1, cell_wall, 1,

        //20th row -- row of walls bottom edge of the board/grid, 
        //Note: blank space unreachable is okay :) was a design choice 
        cell_wall, 7, cell_blank, 2, cell_wall, 7
    };

    //Safety check to assure my pattern has 320 cell enteries
    //Must pass otherwise game is impossible and grid will refuse to draw
    //Consider a critical failure!
    {
        int safety_check = 0;
        int i = 1; 
        while (i < sizeof(grid_pattern)) {

            safety_check += grid_pattern[i];
            i += 2;
        }
        
        if (safety_check != 320) {

            eputs("Grid was not created, pattern used to fill grid did not contain 320 total cell enteries.\r\n"
            "Grid was destroyed, heap memory was freed.\r\n");

            free(singleton_grid);
            singleton_grid = NULL;
            return false;
        }
    }

    /*
        Below is the algorithm used to fill our grid cells with a default starting state based
        on the above preset const pattern, the idea is that if I want to modify my grids
        level layout, I just adjust the pattern of pairs above and the below algorithm will
        fill the rows and cols to match the above pairs.
    */

    //Tracks the number of cells I have entered
    //Once I have entered 20 different cells I know my row is done
    uint8_t no_of_enteries = 0;

    //Tracks the starting position of my current pair from my const pattern
    //The pair index will always increment in twos, so the pair always points to
    //the bitmask, add one index onto this value to see how many columns we need to enter that bitmask for
    int current_pair = 0;

    //Loop through every row in our grid
    for (uint8_t row = 0; row < GRID_ROW_COUNT; ++row) {

        //Tracks the current col we are indexing in our grid
        uint8_t col = 0;

        //Reset enteries to 0 after entering 20 column bit masks -- this lets us know when we are moving to a new row
        no_of_enteries = 0;

        //If less than 20, we are still in the same row
        while (no_of_enteries < GRID_COL_COUNT) {

            //Inserting the current pair bitmask into our grid array
            for (uint8_t i = 0; i < grid_pattern[current_pair + 1]; ++i) {

                //Here we now set our grids[row][col] to the bitmask we wanted from the pattern pair
                //and then just increment our counters afterwards and repeat until done
                singleton_grid->grid_index[row][col] = grid_pattern[current_pair];
                ++col;
                ++no_of_enteries;
            }

            //Go to next pair
            current_pair += 2;
        }
    }

    return true;
}

void set_grid_state(const uint8_t row, const uint8_t col, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Unable to update grid position, grid does not exist!\r\n");
    } 
    else {

        //Checking if our points our in valid arrray bounds
        if (row < GRID_ROW_COUNT && col < GRID_COL_COUNT) 
        {
            singleton_grid->grid_index[row][col] = state_bit_mask;
        } 
        else 
        {
            eputs("Out of range for x and y point when accessing the grid, set_grid_state() failed\r\n.");
        }
    }
}

void add_grid_state(const uint8_t row, const uint8_t col, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Unable to update grid position, grid does not exist!\r\n");
    } 
    else {

        //Checking if our points our in valid arrray bounds
        if (row < GRID_ROW_COUNT && col < GRID_COL_COUNT) 
        {
            singleton_grid->grid_index[row][col] |= state_bit_mask;
        } 
        else 
        {
            eputs("Out of range for x and y point when accessing the grid, add_grid_state() failed.\r\n");
        }   
    }
}

uint8_t get_grid_state(const uint8_t row, const uint8_t col) {

    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Unable to retrieve grid positions state, grid does not exist!\r\n");
        
        return 0;
    } 
    else {

        //Checking if our points our in valid arrray bounds
        if (row < GRID_ROW_COUNT && col < GRID_COL_COUNT) 
        {
            return singleton_grid->grid_index[row][col];
        } 
        else 
        {
            eputs("Out of range for x and y point when accessing the grid, get_grid_state() failed\n.Returned value 0.\r\n");
            return 0;
        } 
    }
}

bool is_grid_state(const uint8_t row, const uint8_t col, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Unable to check grid positions state, grid does not exist!\r\n");
        return false;
    } 
    else {

        //Checking if our points our in valid arrray bounds
        if (row < GRID_ROW_COUNT && col < GRID_COL_COUNT) 
        {
            if (singleton_grid->grid_index[row][col] == state_bit_mask) {

                return true;
            }
            else {
                return false;
            }
        } 

        eputs("Out of range for x and y point when accessing the grid, is_grid_state() failed\n.Returned false.\r\n");
        return false;
    }
}

bool has_grid_state(const uint8_t row, const uint8_t col, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Unable to check grid positions state, grid does not exist!\r\n");
        
        return false;
    } 
    else {

        //Checking if our points our in valid arrray bounds
        if (row < GRID_ROW_COUNT && col < GRID_COL_COUNT) 
        {
            if (singleton_grid->grid_index[row][col] & state_bit_mask) {

                return true;
            }
            else {
                return false;
            }
        } 

        eputs("Out of range for x and y point when accessing the grid, has_grid_state() failed.\r\nReturned false.\r\n");
        return false;
    }
}

bool compare_grid_states(const uint8_t row_1, const uint8_t col_1, 
                         const uint8_t row_2, const uint8_t col_2 ) {
    
    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Unable to compare both grid position states, grid does not exist!\r\n");
        
        return false;
    } 
    else {

        //Checking if our points our in valid arrray bounds
        if (row_1 < GRID_ROW_COUNT && row_2 < GRID_ROW_COUNT && col_1 < GRID_COL_COUNT && col_2 < GRID_COL_COUNT) {

            if (singleton_grid->grid_index[row_1][col_1] == singleton_grid->grid_index[row_2][col_2]) {

                return true;
            } 
            else {
                return false;
            }  
        }
        
        eputs("Out of range for x and y point when accessing the grid, compare_grid_states() failed.\r\nReturned false.\r\n");
        return false;
    }
}

bool is_grid_alive() {

    if (singleton_grid) return true;

    return false;
}

void destroy_grid() {

    //Checking if our grid is created
    if (!singleton_grid) {

        eputs("Your grid was already NULL, nothing to free.\r\n");
    }
    
    //Destroying our grid and marking global variable as NULL
    free(singleton_grid);
    singleton_grid = NULL;
}
