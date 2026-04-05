#include "../include/utils/events.h"
#include "../include/frontend&drawing/draw_manager.h"
#include "../include/frontend&drawing/menu.h"
#include "../include/game_play/game_logic.h"
#include "../include/music&sound/tones.h"

int main()
{	
	//Turn on IO and setup micro-controller
	SET_UP_STM();

	//This loop ensures we are always running once powered on
	while (1) {

		//Since we are currently not in the game, we do not need the leds on
		turn_off_LEDS();

		//This should always draw the home menu
		draw_current_page();

		//This loop will just keep checking for cursor movements and flicker text based on the below three pages
		//main menu
		//options menu
		//scoreboard menu
		while ( 
			(get_active_menu_page() == menu_page_home) || 
			(get_active_menu_page() == menu_page_options) ||
			(get_active_menu_page() == menu_page_scoreboard)
			) {

			flicker_text();
			if (is_button_up_pressed()) {
				move_cursor(MOVE_CURSOR_UP);
				delay(25);
			}
			if (is_button_right_pressed()) {
				move_cursor(MOVE_CURSOR_RIGHT);
				delay(25);
			}
			if (is_button_down_pressed()) {
				move_cursor(MOVE_CURSOR_DOWN);
				delay(25);
			}
			if (is_button_left_pressed()) {
				move_cursor(MOVE_CURSOR_LEFT);
				delay(25);
			}
		}
		//Starts the game
		play_game();
	}
	//Application end, theoretically unreachable in our case 
	return 0;	
}
