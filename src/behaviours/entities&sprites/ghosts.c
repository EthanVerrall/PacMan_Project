#include "../include/behaviours/entities&sprites/ghosts.h"

struct Ghosts
{
    char ghost_type;
    Point* position;
    GhostMode currentMode;
    Point* scatter_position;
    bool is_behaviour_changed;
};

Ghosts* create_ghost(
    char ghost_type,
    Point* current_position,
    GhostMode current_mode,
    Point* scatter_pos,
    bool is_behaviour_changed
){  
    Ghosts* ghost = (Ghosts*) malloc(sizeof(Ghosts));
    ghost->currentMode = current_mode;
    ghost->ghost_type = ghost_type;
    ghost->position = current_position;
    ghost->scatter_position = scatter_pos;
    ghost->is_behaviour_changed = is_behaviour_changed;
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
const Point* get_ghost_scatter_position(const Ghosts* ghost){
    return ghost->scatter_position;
}

const Point* get_ghost_position(const Ghosts* ghost){
    return ghost->position;
}

const bool set_ghost_position(Ghosts* ghost, const uint8_t x, const uint8_t y){
    //check that the position set is one that is not out of bounds
    //also make sure the current position is not a wall... sanity check
    if (get_grid_state(x,y) && !is_grid_state(x, y, cell_wall)){
        //set the points using the point functionality
        ghost->position->x = x;
        ghost->position->y = y;
        return true;
    }
    return false;
}

const GhostMode get_ghost_mode(const Ghosts* ghost){
    return ghost->currentMode;
}

const void set_ghost_mode(Ghosts* ghost,const GhostMode mode){
    ghost->currentMode = mode;
    ghost->is_behaviour_changed = true;
}

const char get_ghost_type(const Ghosts* ghost){
    return ghost->ghost_type;
}

const bool get_ghost_behaviour_change(const Ghosts* ghost){
    return ghost->is_behaviour_changed;
}

void set_ghost_behaviour(Ghosts* ghost,const bool is_behaviour_changed){
    ghost->is_behaviour_changed = is_behaviour_changed;
}