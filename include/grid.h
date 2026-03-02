#ifndef GRID_H
#define GRID_H
#include <stdint.h>
#include <stdbool.h>

#define grid_rows 128
#define grid_cols 160

enum grid_states{
    
    pacman = 0,
    ghost = 1,
    blank = 2,
    fruit = 3,
    cherry = 4,
    power_up = 5,
    wall = 6,
    gate = 7,


};

typedef struct Grid Grid;

Grid* get_instance();

bool destroy_grid();
 

#endif //GRID_H