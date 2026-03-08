#ifndef PACMAN_TEXTURES_H
#define PACMAN_TEXTURES_H
#include <stdint.h>

//Selecting the correct texture for when pacman is moving
enum pacman_textures {

    //Mouth is closed
    pacman_right_closed = 0, 
    pacman_bottom_closed = 1,
    pacman_left_closed = 2,
    pacman_top_closed = 3,

    //Mouth is open
    pacman_right_open = 4,
    pacman_bottom_open = 5,
    pacman_left_open = 6,
    pacman_top_open = 7
};

//Foward declaring to save space, in the case this
//needs to be including in mutiple files

extern const uint16_t pacman_textures[8][64];
#endif //PACMAN_TEXTURES_H