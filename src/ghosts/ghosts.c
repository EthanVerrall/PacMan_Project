#include "../../include/behaviours/ghosts/ghosts.h"

typedef struct
{
    char ghost_type;
    Point* position;
    GhostMode currentMode;
    Point* scatter_position;
} Ghosts;

Ghosts* create_ghost(
    const char ghost_type,
    Point* current_position,
    GhostMode current_mode,
    const Point* scatter_pos
){
    Ghosts* ghost = (Ghosts*) malloc(sizeof(Ghosts));
    ghost->currentMode = current_mode;
    ghost->ghost_type = ghost_type;
    ghost->position = current_position;
    ghost->scatter_position = scatter_pos;
    return ghost;
}


void delete_ghost(Ghosts* ghost_to_delete){
    //free inner pointers
    free(ghost_to_delete->scatter_position);
    free(ghost_to_delete->position);

    //free main struct
    free(ghost_to_delete);

    //prevent use after free
    ghost_to_delete = NULL;
}

//function does not check for nullness. User of this function should check,
// if need be for null values
const Point* get_ghost_scatter_position(Ghosts* ghost){
    return ghost->scatter_position;
}

const Point* get_ghost_position(Ghosts* ghost){
    return ghost->position;
}

const bool set_ghost_position(Ghosts* ghost, const uint8_t x, const uint8_t y){
    //check that the position set is one that is not out of bounds
    //also make sure the current position is not a wall... sanity check
    if (get_grid_state(x,y) && !is_grid_state(x, y, cell_wall)){
        //set the points using the point functionality
        set_x_point_coord(x,ghost->position);
        set_y_point_coord(y,ghost->position);
        return true;
    }
    return false;
}

const GhostMode get_ghost_mode(Ghosts* ghost){
    return ghost->currentMode;
}

const void set_ghost_mode(Ghosts* ghost,GhostMode mode){
    ghost->currentMode = mode;
}