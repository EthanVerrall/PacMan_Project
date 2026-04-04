#include "../include/utils/events.h"
#include "../include/frontend&drawing/draw_manager.h"
#include "../include/frontend&drawing/menu.h"
#include "../include/game_play/game_logic.h"
#include "../include/music&sound/tones.h"

int main()
{	
	//Turn on IO and setup micro-controller
	SET_UP_STM();

	while (1) {

		turn_off_LEDS();
		draw_current_page();

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

		play_game();
	}
	return 0;	
}
