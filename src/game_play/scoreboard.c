#include "../include/game_play/scoreboard.h"

static uint16_t current_score = 0;
static char user_name[12] = {'\0'};

void input_user_name() {

    eputs("Enter your name.\r\n");
    for (uint8_t i = 0; i < 5; ++i) {
        eputs("Char ");
        printDecimal(i + 1);
        eputs(": ");
        user_name[i] = egetchar();
    }
    strcat(user_name, " Score:");
}

const char* get_user_name() {

    return user_name;
} 

void reset_user_name() {
    for (uint8_t i = 0; i < 12; ++i) {
        user_name[i] = '\0';
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