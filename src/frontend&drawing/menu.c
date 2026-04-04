#include "../include/frontend&drawing/menu.h"
#include <stdbool.h>

//Default starting menu for pacman, the home page
static enum menu_page active_menu = menu_page_home;

//Position for the cursor
static int8_t cursor_position = 0;

//Forward declares,  these functions are needed from draw manager to be able to seamlessly
//switch between menus and redraw text as white while the cursor moves

void draw_current_page();

void reset_text(int8_t cursor_position, const enum menu_page active_menu);

//Also need the functions that let me toggle the music setting on and off

void turn_on_music(const bool music_flag);

bool get_music_setting();


void set_menu_page(const enum menu_page new_menu) {

    switch (new_menu) {

        case menu_page_home:
        case menu_page_game:
        case menu_page_pause:
        case menu_page_restart:
        case menu_page_options:
        case menu_page_name_request:
        case menu_page_scoreboard:
        //Expected menu passed to function
            active_menu = new_menu;
            break;

        //Unexpected menu passed to function
        //Abort the function
        default:
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

                //Change to game menu
                if (cursor_position == 0) {
                    set_menu_page(menu_page_name_request);
                    cursor_position = 0;
                }
                
                //Change to scoreboard menu
                if (cursor_position == 1) {
                    set_menu_page(menu_page_scoreboard);
                    cursor_position = 0;
                    draw_current_page();
                }

                //Change to options menu
                if (cursor_position == 2) {
                    set_menu_page(menu_page_options);
                    cursor_position = 0;
                    draw_current_page();
                }
            
            break;
        
            case MOVE_CURSOR_DOWN:

                if (cursor_position < 2) {
                    reset_text(cursor_position, menu_page_home);
                    ++cursor_position;
                } 
            break;

            case MOVE_CURSOR_UP:
            
                if (cursor_position > 0) {
                    reset_text(cursor_position, menu_page_home);
                    --cursor_position;
                }
            break;    
        
            case MOVE_CURSOR_LEFT:
            //Do nothing
            break;

            default:
            break;
        }
        return;
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
                set_menu_page(menu_page_restart);
                cursor_position = 0;
            }

            //Exits the game
            if (cursor_position == 2) {
                set_menu_page(menu_page_home);
                cursor_position = 0;
            }
            break;
        
            case MOVE_CURSOR_DOWN:
            if (cursor_position < 2) {
                reset_text(cursor_position, menu_page_pause);
                ++cursor_position;
            } 
            break;

            case MOVE_CURSOR_UP:
            if (cursor_position > 0) {
                reset_text(cursor_position, menu_page_pause);
                --cursor_position;
            }
            break;    
        
            case MOVE_CURSOR_LEFT:
            //Do nothing
            break;
            
            default:
            break;
        }
        return;
    }


    if (get_active_menu_page() == menu_page_options) {

        switch (cursor_direction) {

            case MOVE_CURSOR_UP:
            //do nothing
            break;

            case MOVE_CURSOR_DOWN:
            //do nothing
            break;

            case MOVE_CURSOR_RIGHT:

                //Toggling music on and off
                if (get_music_setting()) {
                    turn_on_music(false);
                }
                else {
                    turn_on_music(true);
                }
                reset_text(0,menu_page_options);
                break;

            case MOVE_CURSOR_LEFT:
                set_menu_page(menu_page_home);
                //Cursor should be zero anyways but lets reset it to be safe
                cursor_position = 0;
                draw_current_page();
                break;

            default:
            break;
        }
        return;
    }

    if (get_active_menu_page() == menu_page_scoreboard) {

        switch (cursor_direction) {

            case MOVE_CURSOR_LEFT:

                set_menu_page(menu_page_home);
                //Cursor should be zero anyways but lets reset it to be safe
                cursor_position = 0;    
                draw_current_page();
                break;

            case MOVE_CURSOR_UP:
            //do nothing
            break;

            case MOVE_CURSOR_RIGHT:
            //do nothing
            break;
            
            case MOVE_CURSOR_DOWN:
            //do nothing
            break;
        }
        return;
    }
    
}