#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../include/serial.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

enum Score {

    score_pellet = 10,
    score_cherry = 100,
    score_powerup = 50,
    score_eat_ghost = 200,
    score_life = 75
};

//-----------------------------------
//Score functions for the users points
//-----------------------------------

void reset_score();

void update_score(const enum Score score);

uint16_t get_score();

//-----------------------------------
//String functions for the users name
//-----------------------------------

void input_user_name();

const char* get_user_name();

void reset_user_name();

//-----------------------------------
//Scoreboard functions
//-----------------------------------

const char* get_scoreboard_names(const uint8_t name_number);

uint16_t  get_scoreboard_scores(const uint8_t score_number);

bool update_highscores();

#endif //!SCOREBOARD_H