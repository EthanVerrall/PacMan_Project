#ifndef MENU_H
#define MENU_H

#include <stdint.h>

#define MOVE_CURSOR_RIGHT 0
#define MOVE_CURSOR_DOWN 1
#define MOVE_CURSOR_LEFT 2
#define MOVE_CURSOR_UP 3

enum menu_page {

    menu_page_home = 1,
    menu_page_game = 2,
    menu_page_pause = 3,
    menu_page_restart = 4,
    menu_page_options = 5,
    menu_page_name_request = 6,
    menu_page_scoreboard = 7,
};

void set_menu_page(const enum menu_page new_menu);

void move_cursor(const int8_t cursor_direction);

enum menu_page get_active_menu_page();

int8_t get_cursor_position();

#endif //MENU_H