#include "../include/grid.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Global variable to store our one and only grid
//The enter file always needs to see the state of this pointer, this is the cleanest and simplest solution
//Just go global
static Grid* singleton_grid = NULL;   

struct Grid {

    uint8_t grid_index [GRID_ROW_COUNT][GRID_COL_COUNT]; 
};

//Internal Helper function - used to create a new grid on the heap (SINGLETON)
bool create_singleton_grid() {

    //Cannot create a new grid if we already have one
    if (singleton_grid) {

        printf("Cannot create a new grid, grid is already pointing to valid heap memory.\n");
        return false;
    }
    //Making a new grid on the heap
    else {
        
        singleton_grid = malloc(sizeof(Grid));

        if (!singleton_grid) {

            printf("Error in creating a new grid, function malloc failed to allocate memory!\n");
            return false;
        }

        return true;
    }
}

bool create_reset_grid() {

    //Checking if a grid already exists -- otherwise create a new one
    if (!singleton_grid) {

        if (!create_singleton_grid()) {
            printf("Function create_reset_grid failed!\nGrid was unable to be created.\n");
            return false;
        }
    }

    //Original states that the board/grid will always start at 
    const uint8_t grid_pattern[] = 
    {   
        //1st row - one above the board
        blank, 28, 

        //2nd row - row of walls top edge of the board/grid
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

        //32nd row - row of walls bottom edge of the board/grid
        wall, 28
    };

    /*
        Below is the algorithm used to fill our grid with a defualt starting state based
        on the above preset const pattern, the idea is that if I want to modify my grids
        level layout, I just adjust the pattern of pairs and the blow algorithm will go ahead
        and always fill the rows and cols to match the above pairs.
    */

    //Tracks the number of states I have entered
    //Once I have entered 28 different states I know my row is done
    uint8_t no_of_enteries = 0;

    //Tracks the starting position of my current pair from my const pattern
    //The pair index will always increment in twos, so the pair always points to
    //the bit mask, add one to see how many times to add our current pairs bit mask
    int current_pair = 0;

    //Loop through every row in our grid
    for (uint8_t row = 0; row < GRID_ROW_COUNT; ++row) {

        //Tracks the current col we are indexing in our grid
        uint8_t col = 0;

        //Reset enteries to 0 after entering 28 col bit masks -- this lets us know when we are moving to a new row
        no_of_enteries = 0;

        //If less than 28, we are still in the same row
        while (no_of_enteries < GRID_COL_COUNT) {

            //See how many enteries we have to use for the current pairs bit mask into our grid array
            for (uint8_t i = 0; i < grid_pattern[current_pair + 1]; ++i) {

                //Here we now set our grids[row][col] to the bit mask we wanted from the pattern pair
                //and then just increment our counters
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

void set_grid_state(const uint8_t x_point, const uint8_t y_point, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        printf("Unable to update grid position, grid does not exist!\n");
    } 
    else {
        //Checking if our points our in valid arrray bounds
        if (x_point < GRID_ROW_COUNT && y_point < GRID_COL_COUNT) 
        {
            singleton_grid->grid_index[x_point][y_point] = state_bit_mask;
        } 
        else 
        {
            printf("Out of range for x and y point when accessing the grid, set_grid_state() failed\n.");
        }
    }
}

void add_grid_state(const uint8_t x_point, const uint8_t y_point, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        printf("Unable to update grid position, grid does not exist!\n");
    } 
    else {
        //Checking if our points our in valid arrray bounds
        if (x_point < GRID_ROW_COUNT && y_point < GRID_COL_COUNT) 
        {
            singleton_grid->grid_index[x_point][y_point] |= state_bit_mask;
        } 
        else 
        {
            printf("Out of range for x and y point when accessing the grid, add_grid_state() failed.\n");
        }   
    }
}

uint8_t get_grid_state(const uint8_t x_point, const uint8_t y_point) {

    //Checking if our grid is created
    if (!singleton_grid) {

        printf("Unable to retrieve grid positions state, grid does not exist!\n");
        
        return 0;
    } 
    else {
        //Checking if our points our in valid arrray bounds
        if (x_point < GRID_ROW_COUNT && y_point < GRID_COL_COUNT) 
        {
            return singleton_grid->grid_index[x_point][y_point];
        } 
        else 
        {
            printf("Out of range for x and y point when accessing the grid, get_grid_state() failed\n.Returned value 0.\n");
            return 0;
        } 
    }
}

bool is_grid_state(const uint8_t x_point, const uint8_t y_point, const uint8_t state_bit_mask) {

    //Checking if our grid is created
    if (!singleton_grid) {

        printf("Unable to check grid positions state, grid does not exist!\n");
        
        return false;
    } 
    else {
        //Checking if our points our in valid arrray bounds
        if (x_point < GRID_ROW_COUNT && y_point < GRID_COL_COUNT) 
        {
            if (singleton_grid->grid_index[x_point][y_point] == state_bit_mask) {

                return true;
            }
            else {
                return false;
            }
        } 

        printf("Out of range for x and y point when accessing the grid, is_grid_state() failed\n.Returned false.\n");
        return false;
    }
}

bool compare_grid_states(const uint8_t x_point_1, const uint8_t y_point_1, 
                         const uint8_t x_point_2, const uint8_t y_point_2) {
    
    //Checking if our grid is created
    if (!singleton_grid) {

        printf("Unable to compare both grid position states, grid does not exist!\n");
        
        return false;
    } 
    else {
        //Checking if our points our in valid arrray bounds
        if (x_point_1 < GRID_ROW_COUNT && x_point_2 < GRID_ROW_COUNT && y_point_1 < GRID_COL_COUNT && y_point_2 < GRID_COL_COUNT) {

            if (singleton_grid->grid_index[x_point_1][y_point_1] == singleton_grid->grid_index[x_point_2][y_point_2]) {

                return true;
            } 
            else {
                return false;
            }  
        }
        
        printf("Out of range for x and y point when accessing the grid, compare_grid_states() failed\n.Returned false.\n");
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

        printf("Your grid was already NULL, nothing to free.\n");
    }
    
    //Destroying our grid and marking global variable as NULL
    free(singleton_grid);
    singleton_grid = NULL;
}