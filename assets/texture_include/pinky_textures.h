#ifndef PINKY_TEXTURES_H
#define PINKY_TEXTURES_H
#include <stdint.h>

//Selecting the correct texture for when pinky is moving
enum pinky_textures {

    //Direction the eye is looking in,
    //matches the way he moves
    pinky_right_eye = 0,
    pinky_bottom_eye = 1,
    pinky_left_eye = 2,
    pinky_top_eye = 3

};

//Foward declaring to save space, in the case this
//needs to be including in mutiple files

extern const uint16_t pinky_array[4][64];

#endif //PINKY_TEXTURES_H