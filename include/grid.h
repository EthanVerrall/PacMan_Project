#ifndef GRID_H
#define GRID_H
#include "../include/utils/point.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define GRID_ROW_COUNT 20
#define GRID_COL_COUNT 16

/*
128 by 160
the score at the top will be 8 pixels in height
grid must fit 128 by 152
8*8 pixels = one tile
Grid array is now [20][16] = 640 bytes
Each array element is a uint16_t bitmask tracking the games pixels/state
*/

/*
    How this "class" works.

    The grid follows a singleton design pattern. When creating a grid you can only ever have one alive at a time.
    The grid class will make sure it tracks itself and does not dangle, you will never have a pointer to it or need to track it's
    lifetime yourself. 
    
    You simply call the function create_reset_grid() and a new grid will be made. When you are done with your grid you simply call
    the function destroy_grid() and the grid will be free'd from memory. You can always check if your grid is alive with the function
    is_grid_alive().

    Note if you ever try to make another grid with create_reset_grid() - you will just reset the same grid to default 
    starting game values. If you ever try to use a grid function without having created one first, you will just get an error message
    and a boolean false value.
    
    Example:
    
    int main () {

        if (create_reset_grid()) 
        {

            //Do what you must here on the grid
        }   

        destroy_grid();

        return 0;
    }
*/


/*
    Different states of bitmasks for the grid.
    Assign states to cells in the grid to represent.
    what is currently at that cell.
*/
enum cell_state {

    cell_pacman = (1<<0),
    cell_blinky = (1<<1),
    cell_inky = (1<<2),
    cell_pinky = (1<<3),
    cell_clyde = (1<<4),
    cell_blank = (1<<5),
    cell_pellet = (1<<6),
    cell_cherry = (1<<7),
    cell_power_up = (1<<8),
    cell_wall = (1<<9),
    cell_gate = (1<<10)                                                               
};

typedef struct Grid Grid;

//Creates a new grid if one does not already exist.
//Sets the grid to default values.
bool create_reset_grid();

//Overwrites the entire bitmask state on the grid at the specified point
void set_grid_state(const uint8_t row, const uint8_t col, const uint16_t state_bit_mask);

void set_grid_state_point(const Point* const point, const uint16_t state_bit_mask);

//Appends a bitmask state on the grid at the specified point using (grid[x][y] |= state_bit_mask)
void add_grid_state(const uint8_t row, const uint8_t col, const uint16_t state_bit_mask);

void add_grid_state_point(const Point* const point, const uint16_t state_bit_mask);

//Removes a bitmask state on the grid at the specified point using (grid[x][y] &= ~state_bit_mask)  
void remove_grid_state(const uint8_t row, const uint8_t col, const uint16_t state_bit_mask);

void remove_grid_state_point(const Point* const point, const uint16_t state_bit_mask);

//Returns the bitmask state on the grid at the specified point
uint16_t get_grid_state(const uint8_t row, const uint8_t col);

uint16_t get_grid_state_point(const Point* const point);

//Checks the bitmask state on the grid at the specified point, 
//Only true if the exact cell state completely matches the bitmask perfectly
bool is_grid_state(const uint8_t row, const uint8_t col, const uint16_t state_bit_mask);

bool is_grid_state_point(const Point* const point, const uint16_t state_bit_mask);

//Checks the bitmask state on the grid at the specified point,
//Returns true if the grid cell contains at least this state, 
//Function does not care about the other states the cell might contain.
bool has_grid_state(const uint8_t row, const uint8_t col, const uint16_t state_bit_mask);

bool has_grid_state_point(const Point* const point, const uint16_t state_bit_mask);

//Compare two points on the grid by their bitmask states,
//pass two points, returns true if the masks match each other
bool compare_grid_states(const uint8_t row_1, const uint8_t col_1, 
                         const uint8_t row_2, const uint8_t col_2);

bool compare_grid_states_point(const Point* const point_1, 
                               const Point* const point_2);                         

//Returns true if our grid is currently heap allocated on memory 
bool is_grid_alive();

//Frees the singleton grid from heap memory
void destroy_grid();
 
#endif //GRID_H