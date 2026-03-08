#ifndef PICKUPS_H
#define PICKUPS_H
#include <stdint.h>

enum pickups_textures {

    pickups_pellet = 0,
    pickups_powerup = 1,
    pickups_cherry = 2
};

const extern uint16_t pickups_textures[3][64];

#endif //PICKUPS_H