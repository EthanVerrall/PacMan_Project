#include "../../include/behaviours/ghosts/ghosts.h"

Ghosts* create_ghost(
    const char ghost_type,
    Point* current_position,
    GhostMode current_mode,
    Point* scatter_pos
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