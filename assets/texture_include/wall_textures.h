#ifndef WALL_TEXTURES_H
#define WALL_TEXTURES_H
#include <stdint.h>

//Selecting texture to choose the correct wall shape to draw to the screen
enum wall_textures {

    //Wall curves

    wall_curve_top_left = 0,
    wall_curve_top_right = 1,
    wall_curve_bottom_left = 2,
    wall_curve_bottom_right = 3,

    //Basic wall shapes

    wall_horizontal = 4,
    wall_vertical = 5,
    wall_gate = 6,

    //Three sided wall, like a T junction

    wall_tri_right = 7,
    wall_tri_top = 8,
    wall_tri_left = 9,
    wall_tri_bottom = 10
};

//Forward declaring to save space, in the case this
//needs to be included in mutiple files

extern const uint16_t const wall_array[11][64];

#endif //WALL_TEXTURES_H