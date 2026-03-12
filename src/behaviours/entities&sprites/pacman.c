#include "../../../include/behaviours/entities&sprites/pacman.h"

struct Pacman
{
    //something to do....
    uint8_t dx; //change in x direction
    uint8_t dy; //change in y direction
    uint8_t lives;
    Point* position;
    PacState state;
};

Pacman* _pacman(){
    Pacman* pacman = NULL;

    if (pacman) return pacman;

    pacman = malloc(sizeof(Pacman));

    pacman->dx = 0;
    pacman->dy = 0;
    
    return pacman;
}

PacState get_pacman_state(){
    Pacman* pacman = _pacman();
    return pacman->state;
}

void set_pacman_state(const PacState newstate){
    Pacman* pacman = _pacman();
    pacman->state = newstate;
}

Point* get_pacman_position(){
    Pacman* pacman = _pacman();
    return pacman->position;
}

void set_pacman_position(const uint8_t x, const uint8_t y){
    Pacman* pacman = _pacman();
    set_x_point_coord(x,pacman->position);
    set_y_point_coord(y,pacman->position);
}

PacDirection get_pacman_direction(){
    Pacman* pacman = _pacman();
    if (pacman->dx > 0 && pacman->dy == 0) return RIGHT;
    if (pacman->dx < 0 && pacman->dy == 0) return LEFT;
    if (pacman->dy < 0 && pacman->dx == 0) return TOP;
    if (pacman->dy > 0 && pacman->dy == 0) return BOTTOM;

    return NONE;
}

void set_pacman_direction(const PacDirection newdirection){
    Pacman* pacman = _pacman();
    if (newdirection == LEFT){
        pacman->dx = -1;
        pacman->dy = 0;
    }
    if (newdirection == BOTTOM){
        pacman->dx = 0;
        pacman->dy = 1;
    }
    if (newdirection == RIGHT){
        pacman->dx = 1;
        pacman->dy = 0;
    }
    if (newdirection == TOP){
        pacman->dx = 0;
        pacman->dy = -1;
    }
    
}