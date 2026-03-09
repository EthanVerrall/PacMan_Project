#ifndef CLYDE_TEXTURES_H
#define CLYDE_TEXTURES_H
#include <stdint.h>

//Selecting the correct texture for when clyde is moving
enum clyde_textures {

    //Direction the eye is looking in,
    //matches the way he moves
    clyde_right_eye = 0,
    clyde_bottom_eye = 1,
    clyde_left_eye = 2,
    clyde_top_eye = 3
};

//Foward declaring to save space, in the case this
//needs to be including in mutiple files

extern const uint16_t clyde_array[4][64];

#endif //CLYDE_TEXTURES_H