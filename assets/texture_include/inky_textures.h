#ifndef INKY_TEXTURES_H
#define INKY_TEXTURES_H
#include <stdint.h>

//Selecting the correct texture for when inky is moving
enum inky_textures {

    //Direction the eye is looking in,
    //matches the way he moves
    inky_right_eye = 0,
    inky_bottom_eye = 1,
    inky_left_eye = 2,
    inky_top_eye = 3
};

//Forward declaring to save space, in the case this
//needs to be included in mutiple files

extern const uint16_t inky_array[4][64];

#endif //INKY_TEXTURES_H