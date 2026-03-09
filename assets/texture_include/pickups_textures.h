#ifndef PICKUPS_H
#define PICKUPS_H
#include <stdint.h>

//Selecting the correct texture for pickups
//These are tiles that are not walls and must be eaten or moved on
enum pickups_textures {

    pickups_pellet = 0,
    pickups_powerup = 1,
    pickups_cherry = 2
};

//Foward declaring to save space, in the case this
//needs to be including in mutiple files

const extern uint16_t pickups_array[3][64];

#endif //PICKUPS_H