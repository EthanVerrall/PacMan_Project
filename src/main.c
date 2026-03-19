#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/serial.h"
#include "../include/utils/events.h"
#include <stdlib.h>

int main()
{
	SET_UP_STM();
	create_reset_grid();
	draw_starting_grid();

	const enum entity_type move_order[] = {entity_type_pacman};

	Point* point_array[] = {

	create_point(10,4), //0 pacman current
	create_point(0,0), //1 pacman target
	};


	//Testing off screen wrapping
	for (int i = 0; i < 5; ++i) {
		
		//Setting targets based on current position
		set_point_coord(get_x_point_coord(point_array[0]), get_y_point_coord(point_array[0]) - 1, point_array[1]);
		
		//Check if target is in bounds
		if (get_y_point_coord(point_array[1]) == 255) {
			set_y_point_coord(15, point_array[1]);
		}

		if (get_y_point_coord(point_array[1]) == 16) {
			set_y_point_coord(0,point_array[1]);
		}

		eputs("Iteration: ");
		printDecimal(i + 1);
		eputs("\r\n");
		printDecimal(get_x_point_coord(point_array[0]));
		printDecimal(get_y_point_coord(point_array[0]));
		eputs("\r\n");
		printDecimal(get_x_point_coord(point_array[1]));
		printDecimal(get_y_point_coord(point_array[1]));
		eputs("\r\n\r\n");

		//Physical move
		move_entities(point_array, move_order, 1);

		//Updating current point to what target was
		set_y_point_coord(get_y_point_coord(point_array[1]), point_array[0]);
	}
	//Testing off screen wrapping

	//More Testing
	set_point_coord(10,14, point_array[1]);
	move_entities(point_array, move_order, 1);
	set_y_point_coord(get_y_point_coord(point_array[1]), point_array[0]);
	move_point(0,-1,point_array[1]);
	move_entities(point_array, move_order, 1);
	set_y_point_coord(get_y_point_coord(point_array[1]), point_array[0]);

	//Wrapping right to left of the screen
	for (int i =0; i < 6; ++i) {

		//Setting targets based on current position
		set_point_coord(get_x_point_coord(point_array[0]), get_y_point_coord(point_array[0]) + 1, point_array[1]);

		//Check if target is in bounds
		if (get_y_point_coord(point_array[1]) == 255) {
			set_y_point_coord(15, point_array[1]);
		}

		if (get_y_point_coord(point_array[1]) == 16) {
			set_y_point_coord(0,point_array[1]);
		}

		//Physical move
		move_entities(point_array, move_order, 1);

		//Updating current point to what target was
		set_y_point_coord(get_y_point_coord(point_array[1]), point_array[0]);

	}

	//Freein grid
	destroy_grid();
	
	//Cleaning up points
	for (int i = 0; i < 2; ++i) {

		point_array[i] = destroy_point(point_array[i]);
	}

	return 0;
}