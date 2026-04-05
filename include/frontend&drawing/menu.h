#ifndef MENU_H
#define MENU_H

#include <stdint.h>

/*
    This menu manager allows us to move an "artificial" cursor around when not playing the game.
    It is meant to feel like and mimic and arcade style machine game from the 80/90s

    We track the current active page and where the cursor is at all times and update it based on events fed to the
    functions from button presses.
*/

//Cursor movment
#define MOVE_CURSOR_RIGHT 0
#define MOVE_CURSOR_DOWN 1
#define MOVE_CURSOR_LEFT 2
#define MOVE_CURSOR_UP 3

//All our different menus
enum menu_page {

    menu_page_home = 1,
    menu_page_game = 2,
    menu_page_pause = 3,
    menu_page_restart = 4,
    menu_page_options = 5,
    menu_page_name_request = 6,
    menu_page_scoreboard = 7,
};

//Change which menu is currently active
void set_menu_page(const enum menu_page new_menu);

//Move / navigate the "Artificial" cursor
void move_cursor(const int8_t cursor_direction);

//See what page is currently active
enum menu_page get_active_menu_page();

//See where the cursor is currently
int8_t get_cursor_position();

#endif //MENU_H