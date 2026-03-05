#include <stdint.h>

typedef enum menu_selection menu_selection;

enum menu_selection {
    START,
    PROFILES,
    LEADERBOARD,
    SETTINGS
};

void display_menu(char* text[]);
void draw_menu_cursor();
void next_menu_item();
void next_prev_item();