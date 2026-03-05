#ifndef GRID_H
#define GRID_H
#include <stdint.h>
#include <stdbool.h>

#define grid_tile_row 
#define grid_tile_col 

//
#define pacman 1<<0
#define ghost 1<<1
#define blank 1<<2
#define fruit 1<<3
#define cherry 1<<4
#define power_up 1<<5
#define wall 1<<6
#define gate 1<<7

typedef struct Grid Grid;

Grid* get_instance();

bool set_reset_grid();

void update_grid_position_type(const uint8_t grid_index[][], const uint8_t state_bit_mask);

Grid* destroy_grid(Grid* _grid);
 

#endif //GRID_H


