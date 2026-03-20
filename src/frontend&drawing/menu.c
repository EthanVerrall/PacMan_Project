#include "../include/frontend&drawing/menu.h"
#include "../include/serial.h"

//Default starting menu for pacman, the home page
static enum menu_page active_menu = menu_page_home;

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