#include "../../../include/behaviours/entities&sprites/pacman.h"

struct Pacman
{
    //something to do....
    int8_t dx; //change in x direction
    int8_t dy; //change in y direction
    uint8_t lives;
    Point* position;
    PacState state;
};

Pacman* _pacman(){
    static Pacman* pacman = NULL;

    if (pacman) return pacman;

    pacman = malloc(sizeof(Pacman));

    pacman->dx = 0;
    pacman->dy = 0;

    pacman->position = create_point(15,7);
    pacman->state = Mortal;
    pacman->lives = 4;

    
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
    set_point_coord(x, y, pacman->position);
}

PacDirection get_pacman_direction(){
    Pacman* pacman = _pacman();
    if (pacman->dx ==  0 && pacman->dy ==  1) return PAC_RIGHT;
    if (pacman->dx ==  0 && pacman->dy == -1) return  PAC_LEFT;
    if (pacman->dx == -1 && pacman->dy ==  0) return  PAC_TOP;
    if (pacman->dx ==  1 && pacman->dy ==  0) return PAC_BOTTOM;
 
    return  PAC_NONE;
}

int8_t get_pac_dx(){
    Pacman* pacman = _pacman();
    return pacman->dx;
}

int8_t get_pac_dy(){
    Pacman* pacman = _pacman();
    return pacman->dy;
}

void set_pacman_direction(const PacDirection newdirection){
    Pacman* pacman = _pacman();
    if (newdirection ==  PAC_LEFT){
        pacman->dx = 0;
        pacman->dy = -1;
    }
    if (newdirection ==  PAC_BOTTOM){
        pacman->dx = 1;
        pacman->dy = 0;
    }
    if (newdirection ==  PAC_RIGHT){
        pacman->dx = 0;
        pacman->dy = 1;
    }
    if (newdirection ==  PAC_NONE){
        pacman->dx = 0;
        pacman->dy = 0;
    }
    if (newdirection ==  PAC_TOP){
        pacman->dx = -1;
        pacman->dy = 0;
    }
    
}