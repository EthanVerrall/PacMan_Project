#include "../include/game_play/scoreboard.h"

//Scorebaord holding the top 3 names and scores
static char scoreboard_names[3][6] = {"\0", "\0", "\0"};
static uint16_t scoreboard_scores[3] = {0,0,0};

//The current user who is playing a match of pacman
static uint16_t current_score = 0;
static char current_user_name[13] = {"\0"};

const char* get_scoreboard_names(const uint8_t name_number) {
    return scoreboard_names[name_number];
}

uint16_t  get_scoreboard_scores(const uint8_t score_number) {
    return scoreboard_scores[score_number];
}

bool update_highscores() {
    
    //Where we are pushing to the scoreboard. If minus 1 then no new highscore was achieved.
    int8_t push_position = -1;
    
    //Temp will read the current name and score from the scoreboard and make a temp copy
    char temp_name[6] = {""};
    uint16_t temp_score = 0;

    //Push will put the new name and score into the scoreboard
    char pushed_name[6] = {""};
    uint16_t pushed_score = 0;

    for (uint8_t i = 0; i < 3; ++i) {

        if (current_score > scoreboard_scores[i]) {
            push_position = i;
            break; 
        }
    }

    if (push_position == -1) return false;

    //ensuring the current user score is being pushed first
    strncpy(pushed_name,current_user_name,5);
    pushed_name[5] = '\0';
    pushed_score = current_score;

    while (push_position < 3) {

        //Saved the previous values so I can push them down and re-order the scoreboard
        strcpy(temp_name,scoreboard_names[push_position]);
        temp_score = scoreboard_scores[push_position];
        
        //Pushing new values into the scoreboard
        strcpy(scoreboard_names[push_position],pushed_name);
        scoreboard_scores[push_position] = pushed_score;
        
        //Rewrite push to hold temp since next iteration it will be saved pushed down into the scoreboard
        strcpy(pushed_name, temp_name);
        pushed_score = temp_score;

        ++push_position;
    }

    return true;
}

void input_user_name() {

    eputs("Enter your name. Name is 5 characters long.\r\n");
    for (uint8_t i = 0; i < 5; ++i) {
        eputs("Char ");
        printDecimal(i + 1);
        eputs(": ");
        current_user_name[i] = egetchar();
    }
    strcat(current_user_name, " Score:");
}

const char* get_user_name() {

    return current_user_name;
} 

void reset_user_name() {
    for (uint8_t i = 0; i < 12; ++i) {
        current_user_name[i] = '\0';
    }
}

void reset_score() {

    current_score = 0;
}

void update_score(const enum Score score) {

    current_score += (uint16_t)score;
}

uint16_t get_score() {

    return current_score;
}