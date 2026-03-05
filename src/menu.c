#include <stdint.h>
#include "../include/menu.h"
#include "../include/display.h"


#define COLOUR -1 // this should hopefully display as white .~.
#define TEXT_X 40 // the menu's starting x
#define TEXT_Y 100 // the menu's y
#define ITEM_SPACING 3 //the spacing between text (excluding character height)
#define TEXT_HEIGHT 7 // change to 14 if you want to use printTextX2

#define CURSOR_X TEXT_X-5 // changes how far the cursor is from the selectd text


enum menu_selection {
    START,
    PROFILES,
    LEADERBOARD,
    SETTINGS
};

enum menu_selection current_selection = START;


// takes a string list, displays it as a menu thing
void display_menu(char* text[])
{  
    uint8_t i;
    for (i = 0; i < sizeof(text); i++) {
        // draw the text, with an origin and spacing defined w/ macros
        printText(text[i], TEXT_X, TEXT_Y + (ITEM_SPACING + 7)*i, COLOUR, 0);
    }
}


// dont mind the fact that it doesnt destroy the old cursor `.`~*
void draw_menu_cursor(){
    // draws rectangle beside selected item. ugly code.
    drawRectangle(CURSOR_X, TEXT_Y + (ITEM_SPACING+ 7) * current_selection, 3, 3, COLOUR);
}


// both plus/ minus 1 from the enum, then update the cursor
void next_menu_item(){
    current_selection++;
    draw_menu_cursor();
}


void prev_menu_item(){
    current_selection--;
    draw_menu_cursor();
}

// ugghh, despite my best efforts, i am failing to understand what i am doing.
// mainly a thing of not understanding how to interface w/ display funcs, and how to enum