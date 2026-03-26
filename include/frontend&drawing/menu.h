#ifndef MENU_H
#define MENU_H

#include "../include/frontend&drawing/draw_manager.h"
#include <stdint.h>

#define MOVE_CURSOR_RIGHT 0
#define MOVE_CURSOR_DOWN 1
#define MOVE_CURSOR_left 2
#define MOVE_CURSOR_UP 3

enum menu_page {

    menu_page_home = 1,
    menu_page_game = 2,
    menu_page_pause = 3
    //More to follow
};

void set_menu_page(const enum menu_page new_menu);

void move_cursor(const int8_t cursor_direction);

enum menu_page get_active_menu_page();

int8_t get_cursor_position();

#endif //MENU_H