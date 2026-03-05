#ifndef GRID_H
#define GRID_H
#include <stdint.h>
#include <stdbool.h>

#define GRID_TILE_ROW 32
#define GRID_TILE_COL 28

/*
128 by 160
the score at the top will be 16 pixels in height
grid must fit 128 by 144
4*4 pixels = one tile
grid array is now [28][32] = 896 bytes
each array element is a uint8_t for a bitmask tracking the games pixels/state
Sprites will therefore move by 4 units of x and y when moving since they will be drawn to fill an entire tile
*/
#define pacman 1<<0
#define ghost 1<<1
#define blank 1<<2
#define pellet 1<<3
#define cherry 1<<4
#define power_up 1<<5
#define wall 1<<6
#define gate 1<<7

typedef struct Grid Grid;

//Function done
Grid* get_instance();

//Busy here
bool set_reset_grid();

//Not done
void update_grid_position_type(const uint8_t grid_index[][], const uint8_t state_bit_mask);

//Not Done
Grid* destroy_grid(Grid* _grid);
 
#endif //GRID_H


