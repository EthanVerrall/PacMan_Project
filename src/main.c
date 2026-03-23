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
	delay(1000);

	const Point* entity_array[] = {

		create_point(10,7),
		create_point(9,7),

		create_point(10,8),
		create_point(9,8)
	};
	
	const enum entity_type move_order[] = {
		entity_type_blinky, entity_type_pinky
	};

	move_entities(entity_array, move_order, 2, false);

	for (int i = 0; i < 2; ++i) {
		move_point(-1,0,entity_array[0]);
		move_point(-1,0,entity_array[1]);
		move_point(-1,0,entity_array[2]);
		move_point(-1,0,entity_array[3]);
		if (i == 1) break;
		move_entities(entity_array, move_order, 2, false);
	}

	set_point_coord(get_x_point_coord(entity_array[0]),get_y_point_coord(entity_array[0]) - 1, entity_array[1]);
	set_point_coord(get_x_point_coord(entity_array[2]),get_y_point_coord(entity_array[2]) + 1, entity_array[3]);
	move_entities(entity_array, move_order, 2, true);

	
		move_point(0,-1,entity_array[0]);
		move_point(0,-1,entity_array[1]);
		move_point(0,+1,entity_array[2]);
		move_point(0,+1,entity_array[3]);
		move_entities(entity_array, move_order, 2, true);

		move_point(0,-1,entity_array[0]);
		move_point(0,-1,entity_array[1]);
		move_point(0,+1,entity_array[2]);
		move_point(0,+1,entity_array[3]);
		move_entities(entity_array, move_order, 2, false);
	
	
	destroy_grid();

	return 0;
}