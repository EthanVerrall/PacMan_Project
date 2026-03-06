#ifndef GRID_H
#define GRID_H
#include <stdint.h>
#include <stdbool.h>

#define GRID_ROW_COUNT 32
#define GRID_COL_COUNT 28

/*
128 by 160
the score at the top will be 16 pixels in height
grid must fit 128 by 144
4*4 pixels = one tile
Grid array is now [28][32] = 896 bytes
Each array element is a uint8_t for a bitmask tracking the games pixels/state
Sprites will therefore move by 4 units of x and y when moving since they will be drawn to fill an entire tile
*/

#define pacman (1<<0)
#define ghost (1<<1)
#define blank (1<<2)
#define pellet (1<<3)
#define cherry (1<<4)
#define power_up (1<<5)
#define wall (1<<6)
#define gate (1<<7)

typedef struct Grid Grid;

//Creates a new grid if one does not already exist.
//Sets the grid to default values.
bool create_reset_grid();

//Overwrites the entire bit mask state on the grid at the specified point
void set_grid_state(const uint8_t x_point, const uint8_t y_point, const uint8_t state_bit_mask);

//Appends a bit mask state on the grid at the specified point using ( |= ) bitwise or equals
void add_grid_state(const uint8_t x_point, const uint8_t y_point, const uint8_t state_bit_mask);

//Returns the bit mask state on the grid at the specified point
uint8_t get_grid_state(const uint8_t x_point, const uint8_t y_point);

//Checks the bit mask state on the grid at the specified point, 
//true if it matches the same state bit mask you passed as a parameter
bool is_grid_state(const uint8_t x_point, const uint8_t y_point, const uint8_t state_bit_mask);

//Compare two points on the grid by their bit mask states,
//pass two points, returns true if the masks match each other
bool compare_grid_states(const uint8_t x_point_1, const uint8_t y_point_1, 
                         const uint8_t x_point_2, const uint8_t y_point_2);

//Returns true if our grid is currently heap allocated on memory 
bool is_grid_alive();

//Frees the singleton grid from heap memory
void destroy_grid();
 
#endif //GRID_H