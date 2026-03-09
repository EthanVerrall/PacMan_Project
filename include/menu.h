#include <stdint.h>

typedef enum menu_selection menu_selection;

enum menu_selection {
    START,
    PROFILES,
    LEADERBOARD,
    SETTINGS
};

void display_menu();
void draw_menu_cursor(enum menu_selection current_selection);
void next_menu_item(enum menu_selection current_selection);
void prev_menu_item(enum menu_selection current_selection);