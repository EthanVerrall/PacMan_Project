#ifndef MENU_H
#define MENU_H

#include <stdint.h>

#define MOVE_CURSOR_RIGHT 0
#define MOVE_CURSOR_DOWN 1
#define MOVE_CURSOR_left 2
#define MOVE_CURSOR_UP 3

/*
    Workflow order for Friday:

    idea, a static variable locked behind menu.c only must use functions to edit it

    Adjust redraw_entire_grid function()
    Wrap it and encapsulate behind draw_current_page in draw_manager.h/c
    Get a bitmap for a nice pacman logo
    Make the main menu
    draw the main menu
    then draw the grid afterwards
*/

enum menu_page {

    menu_page_home = 1,
    menu_page_game = 2,
    menu_page_pause = 3
    //More to follow
};

void set_menu_page(const enum menu_page new_menu);

void move_menu_cursor(const int8_t cursor_direction); //This will come later

enum menu_page get_active_menu_page();

#endif //MENU_H