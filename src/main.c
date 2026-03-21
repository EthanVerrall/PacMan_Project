#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/serial.h"
#include "../include/utils/events.h"

int main()
{	
	SET_UP_STM();
	draw_current_page();

	while (get_active_menu_page() == menu_page_home) {

		if (is_button_up_pressed()) {
			move_cursor(MOVE_CURSOR_UP);
		}
		if (is_button_right_pressed()) {
			move_cursor(MOVE_CURSOR_RIGHT);
		}
		if (is_button_down_pressed()) {
			move_cursor(MOVE_CURSOR_DOWN);
		}
		if (is_button_left_pressed()) {
			move_cursor(MOVE_CURSOR_left);
		}
		flicker_text();
	}
	create_reset_grid();
	draw_current_page();
	destroy_grid();

	return 0;
}