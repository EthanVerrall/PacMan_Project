#ifndef GRID_H
#define GRID_H
#include <stdint.h>
#include <stdbool.h>

#define GRID_ROW_COUNT 20
#define GRID_COL_COUNT 16

/*
128 by 160
the score at the top will be 8 pixels in height
grid must fit 128 by 152
8*8 pixels = one tile
Grid array is now [20][16] = 320 bytes
Each array element is a uint8_t bitmask tracking the games pixels/state
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

        if (create_reset_grid();) 
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
    cell_ghost = (1<<1),
    cell_blank = (1<<2),
    cell_pellet = (1<<3),
    cell_cherry = (1<<4),
    cell_power_up = (1<<5),
    cell_wall = (1<<6),
    cell_gate = (1<<7),                                                                
};

typedef struct Grid Grid;

//Creates a new grid if one does not already exist.
//Sets the grid to default values.
bool create_reset_grid();

//Overwrites the entire bitmask state on the grid at the specified point
void set_grid_state(uint8_t x_point, uint8_t y_point, const uint8_t state_bit_mask);

//Appends a bitmask state on the grid at the specified point using ( |= ) bitwise or equals
void add_grid_state(uint8_t x_point, uint8_t y_point, const uint8_t state_bit_mask);

//Returns the bitmask state on the grid at the specified point
uint8_t get_grid_state(uint8_t x_point, uint8_t y_point);

//Checks the bitmask state on the grid at the specified point, 
//Only true if the exact cell state completely matches the bitmask perfectly
bool is_grid_state(uint8_t x_point, uint8_t y_point, const uint8_t state_bit_mask);

//Checks the bitmask state on the grid at the specified point,
//Returns true if the grid cell contains at least this state, 
//Function does not care about the other states the cell might contain.
bool has_grid_state(uint8_t x_point, uint8_t y_point, const uint8_t state_bit_mask);

//Compare two points on the grid by their bitmask states,
//pass two points, returns true if the masks match each other
bool compare_grid_states(uint8_t x_point_1, uint8_t y_point_1, 
                         uint8_t x_point_2, uint8_t y_point_2);

//Returns true if our grid is currently heap allocated on memory 
bool is_grid_alive();

//Frees the singleton grid from heap memory
void destroy_grid();
 
#endif //GRID_H