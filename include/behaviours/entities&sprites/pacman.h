#ifndef PACMAN_H
#define PACMAN_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/utils/point.h"

typedef enum {
    PAC_LEFT,
    PAC_TOP,
    PAC_RIGHT,
    PAC_BOTTOM,
    PAC_NONE
} PacDirection;

typedef enum{
    God, Mortal
}PacState;

//pacman definition
typedef struct Pacman Pacman;

Pacman* _pacman();

PacState get_pacman_state();

void set_pacman_state(const PacState newstate);

Point* get_pacman_position();

void set_pacman_position(const uint8_t x, const uint8_t y);

PacDirection get_pacman_direction();

void set_pacman_direction(const PacDirection newdirection);

int8_t get_pac_dx();

int8_t get_pac_dy();

uint8_t get_pacman_life();

void set_pacman_life(uint8_t life);

Pacman* destroy_pacman();



#endif//!PACMAN_H