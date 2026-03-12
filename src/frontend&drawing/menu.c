/* #include <stdint.h>
#include "../include/frontend&drawing/menu.h"
#include "../include/frontend&drawing/display.h"

#define TITLE_X 30 // "PAC-MAN" title x
#define TITLE_Y 15 // "PAC-MAN" title y

#define COLOUR -1 // this should hopefully display as white .~.
#define SELECTED_COLOUR RGBToWord(-1, -1, 0); // should hopefully be yellow
#define TEXT_X 40 // the menu's starting x
#define TEXT_Y 100 // the menu's y
#define ITEM_SPACING 3 //the spacing between text (excluding character height)
#define TEXT_HEIGHT 7 // change to 14 if you want to use printTextX2

#define CURSOR_X TEXT_X-10 // changes how far the cursor is from the selectd text


enum menu_selection {
    start = 0,
    profiles = 1,
    leaderboard = 2,
    settings = 3
};

enum menu_selection current_selection = START;


// displays a menu thing with hard-coded text, and the "PAC-MAN"(tm)(r) title
void display_menu()
{  
    const char title[] = "Pac-Man";
    const char* text[] = {"Start Game", "Manage Profiles", "Leaderboard", "Options"};

    printTextX2(title, TITLE_X, TITLE_Y, COLOUR, 0);

    uint8_t i;
    for (i = 0; i < sizeof(text); i++) {
        // draw the text, with an origin and spacing defined w/ macros
        printText(text[i], TEXT_X, TEXT_Y + (ITEM_SPACING + 7)*i, COLOUR, 0);
    }
}


void flash_title()
{
    const char title[] = "Pac-Man";

    
}

void flash_selected_text(enum menu_selection current_selection)
{
    const char* text[] = {"Start Game", "Manage Profiles", "Leaderboard", "Options"};

    
}


// draws new cusor
void draw_menu_cursor(enum menu_selection current_selection){
    // draws rectangle beside selected item. ugly code.
    drawRectangle(CURSOR_X, TEXT_Y + (ITEM_SPACING+ 7) * current_selection, 3, 3, COLOUR);
    destroy_prev_cursor(current_selection);

}

// destroys cursor before the current selection
void destroy_prev_cursor(enum menu_selection current_selection){
    // draws rectangle beside selected item. ugly code.
    current_selection = prev_menu_item(current_selection);
    drawRectangle(CURSOR_X, TEXT_Y + (ITEM_SPACING+ 7) * current_selection, 3, 3, 0);// note the 0 at the colour position (end).
}


// plus 1 from the enum
void next_menu_item(enum menu_selection current_selection){
    if (current_selection == SETTINGS)
    {
        current_selection = start;
    }
    else {
        current_selection++;
    }
}

// minus 1 from the enum
void prev_menu_item(enum menu_selection current_selection){
    if (current_selection == START)
    {
        current_selection = SETTINGS;
    }
    else {
        current_selection--;
    }
}

// ugghh, despite my best efforts, i am failing to understand what i am doing.
// mainly a thing of not understanding how to interface w/ display funcs, and how to enum */