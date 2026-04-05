#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../include/serial.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//This enum is used to track how many points each "thing" is worth when playing pacman
//The idea is we use these enums to update score since enums implicitly convert to ints when used 
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

//Resets the current playing users score to zero
void reset_score();

//Updates the current playing users score based of the enum integral value
void update_score(const enum Score score);

//Returns the current playing users score
uint16_t get_score();

//-----------------------------------
//String functions for the users name
//-----------------------------------

//Asks the user to enter a 5 character length name using the serial monitor
void input_user_name();

//Returns the current playing users name as a string (char pointer since c does not have strings :/ )
const char* get_user_name();

//Resets the current playing users name to '\0', null terminate the string essentially
void reset_user_name();

//-----------------------------------
//Scoreboard functions
//-----------------------------------

//The below functions two allow us to get the top 3 scoreboard names and scores of all time

const char* get_scoreboard_names(const uint8_t name_number);

uint16_t  get_scoreboard_scores(const uint8_t score_number);

/*
    This function will be called at the end of a winning game,
    it looks at the current person that played and if their score is better than any of the 
    current top 3 scores, will then push this score into the top 3 at the correct position
    and shift all down, popping scores that no longer  fit in the top 3, saves name and score
    returns true if new highscore, false otherwise
*/    
bool update_highscores();

#endif //!SCOREBOARD_H