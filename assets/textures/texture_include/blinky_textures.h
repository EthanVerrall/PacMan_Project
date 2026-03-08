#ifndef BLINKY_TEXTURES_H
#define BLINKY_TEXTURES_H
#include <stdint.h>

//Selecting the correct texture for when blinky is moving
enum blinky_textures {

    //Direction the eye is looking in,
    //matches the way he moves
    blinky_right_eye = 0,
    blinky_bottom_eye = 1,
    blinky_left_eye = 2,
    blinky_top_eye = 3
};

//Foward declaring to save space, in the case this
//needs to be including in mutiple files

extern const uint16_t blinky_textures[4][64];

#endif //BLINKY_TEXTURES_H