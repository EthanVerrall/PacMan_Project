#include "../include/frontend&drawing/menu.h"
#include "../include/serial.h"

//Default starting menu for pacman, the home page
static enum menu_page active_menu = menu_page_home;

//Position for the cursor
static int8_t cursor_position = 0;

void redraw_white_text(int8_t cursor_position, const enum menu_page active_menu);

void set_menu_page(const enum menu_page new_menu) {

    switch (new_menu) {

        case menu_page_home:
        case menu_page_game:
        case menu_page_pause:
        //Expected menu passed to function
            active_menu = new_menu;
            break;

        //Unexpected menu passed to function
        default:
            eputs("set_menu_page function failed. Invalid enum used, refer to enum menu_page in menu.h file.\r\n");
            break;
    }
}

enum menu_page get_active_menu_page() {

    return active_menu;
}

int8_t get_cursor_position() {

    return cursor_position;
}

void move_cursor(const int8_t cursor_direction) {

    if (get_active_menu_page() == menu_page_home) {

        switch (cursor_direction)
        {
        case MOVE_CURSOR_RIGHT:
            //Change to game
            if (cursor_position == 0) {
                set_menu_page(menu_page_game);
                cursor_position = 0;
            }
            
            //Other features not implemented yet
        break;
        
        case MOVE_CURSOR_DOWN:
            if (cursor_position < 2) {
                redraw_white_text(cursor_position, menu_page_home);
                ++cursor_position;
            } 
            break;

        case MOVE_CURSOR_UP:
            if (cursor_position > 0) {
                redraw_white_text(cursor_position, menu_page_home);
                --cursor_position;
            }
            break;    
        
        case MOVE_CURSOR_left:
        //Do nothing
        break;

        default:
            eputs("Unexpected cursor movement on the home page.\r\nCursor value: ");
            printDecimal(cursor_position);
        break;
        }
    }

    if (get_active_menu_page() == menu_page_pause) {

        switch (cursor_direction) {

            case MOVE_CURSOR_RIGHT:
            //Resume the game
            if (cursor_position == 0) {
                set_menu_page(menu_page_game);
                cursor_position = 0;
            }
            
            //Restarts the game
            if (cursor_position == 1) {
                set_menu_page(menu_page_game);
                cursor_position = 0;
                //Will need to call a function or have a function pointer perhaps?
                //Ask joshua about this one???
            }

            //Exits the game
            if (cursor_position == 2) {
                set_menu_page(menu_page_home);
                cursor_position = 0;
                //Will need to call a function or have a function pointer perhaps?
                //Ask joshua about this one???
            }
        break;
        
        case MOVE_CURSOR_DOWN:
            if (cursor_position < 2) {
                redraw_white_text(cursor_position, menu_page_pause);
                ++cursor_position;
            } 
            break;

        case MOVE_CURSOR_UP:
            if (cursor_position > 0) {
                redraw_white_text(cursor_position, menu_page_pause);
                --cursor_position;
            }
            break;    
        
        case MOVE_CURSOR_left:
        //Do nothing
        break;

        default:
            eputs("Unexpected cursor movement on the pause page.\r\nCursor value: ");
            printDecimal(cursor_position);
        break;
        }
    }
}