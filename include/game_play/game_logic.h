#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../include/behaviours/entities&sprites/pacman.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/clyde.h"
#include "../include/behaviours/entities&sprites/pinky.h"
#include "../include/behaviours/entities&sprites/inky.h"

#include "../include/grid.h"
#include "../include/utils/point.h"

#include "../include/frontend&drawing/draw_manager.h"

#include "../include/music&sound/tones.h"
#include "../include/serial.h"
#include "../include/utils/events.h"

void play_game();

#endif //!GAME_LOGIC_H