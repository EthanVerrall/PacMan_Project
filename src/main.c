#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/serial.h"
#include "../include/utils/events.h"
#include "../include/behaviours/entities&sprites/pacman.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/clyde.h"
#include "../include/behaviours/entities&sprites/pinky.h"
#include "../include/behaviours/entities&sprites/inky.h"

int main()
{	
	//set up grid and IO
	SET_UP_STM();
  	draw_current_page();
	turn_on_LEDS();

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

	//set up ghosts and pacman
	Pacman* pacman_ref = _pacman();

	Blinky* blinky_ref = _blinky();
	Clyde* clyde_ref = _clyde();
	Pinky* pinky_ref = _pinky();
	Inky* inky_ref = _inky();

	Point* entity_move_direction_store[] = {
		
		//pacman movement
		get_pacman_position(),
		create_point(0,0),
		

		//blinky movement
		get_blinky_position(), 
		create_point(0,0),

		//inky movement
		get_inky_position(),
		create_point(0,0),
		
		//pinky movement
		get_pinky_position(),
		create_point(0,0),
		

		//clyde movement
		get_clyde_position(),
		create_point(0,0),
		

	}; 

	const enum entity_type entity_move_order[] = {
		entity_type_pacman,entity_type_inky, entity_type_blinky, entity_type_pinky, entity_type_clyde
	};

	bool button_pressed = false;
	uint8_t pellet_count = 111;
	Point* target_point = NULL;
	
	draw_current_page();

	while (1)
	{
	
		//check for button presses first
		//for now we would just check directly, but for the case that we would want to save time,
		//there would be a function that would check a list of numbers representing the button pressed

		//all buttons (arrow buttons and not pause) do in the game page: change pacmans dx and dy
		//Should  act like a toggle tho, so we only care about one press per loop
		if(button_pressed = is_button_down_pressed()) set_pacman_direction(PAC_BOTTOM);
		else if(button_pressed = is_button_right_pressed()) set_pacman_direction(PAC_RIGHT);
		else if(button_pressed = is_button_left_pressed()) set_pacman_direction(PAC_LEFT);
		else if(button_pressed = is_button_up_pressed()) set_pacman_direction(PAC_TOP);

		//BIG NOTE: We would need to decide if the ghosts come out immediately or if not, we set a timer for each ghost to leave their posts
		//I like the timer idea, they could just start in scatter mode tbh and they go straight to their courners
		//Do whatever is easiest tho
		//we want to change pacman's position
		//pacman in entity pos is 0 (old), 1 (new)
		uint8_t pacman_new_x = get_x_point_coord(get_pacman_position()) + get_pac_dx();
		uint8_t pacman_new_y = get_y_point_coord(get_pacman_position()) + get_pac_dy();

		//wrapping pacman when he goes offscreen...........
		pacman_new_y = pacman_new_y == 16 ? 0 : pacman_new_y;
		pacman_new_y = pacman_new_y == 255 ? 15 : pacman_new_y;

		if (!has_grid_state(pacman_new_x, pacman_new_y, cell_wall | cell_gate))
		{
			set_point_coord(pacman_new_x, pacman_new_y,entity_move_direction_store[1]);
			remove_grid_state(get_x_point_coord(get_pacman_position()), get_y_point_coord(get_pacman_position()), cell_pacman);
			if(has_grid_state(pacman_new_x, pacman_new_y,cell_pellet)) {
				pellet_count--;
				remove_grid_state(pacman_new_x, pacman_new_y, cell_pellet);
				add_grid_state(pacman_new_x, pacman_new_y, cell_blank);
			}
			add_grid_state(pacman_new_x, pacman_new_y, cell_pacman);
		}
		else
		{
			set_pacman_direction(PAC_NONE);
			pacman_new_x = get_x_point_coord(get_pacman_position());
			pacman_new_y = get_y_point_coord(get_pacman_position());
		}
	

		//run algo on ghosts based on pacman's current position

		//blinky is in array 2,3
	
		//Blinky
		target_point = _blinky_feed_next(false,false);
		copy_point_values(entity_move_direction_store[3],target_point);
		eputs("Blinky target\r\n");
		printDecimal(get_x_point_coord(entity_move_direction_store[3]));
		printDecimal(get_y_point_coord(entity_move_direction_store[3]));
		eputs("\r\n");

		//free(target_point);
		
		//inky
		target_point = _inky_feed_next(false, false);
		copy_point_values(entity_move_direction_store[5],target_point);
		eputs("Inky target\r\n");
		printDecimal(get_x_point_coord(entity_move_direction_store[5]));
		printDecimal(get_y_point_coord(entity_move_direction_store[5]));
		eputs("\r\n");
		//free(target_point);

		//pinky
		target_point = _pinky_feed_next(false, false);
		copy_point_values(entity_move_direction_store[7],target_point);
		eputs("Pinky target\r\n");
		printDecimal(get_x_point_coord(entity_move_direction_store[7]));
		printDecimal(get_y_point_coord(entity_move_direction_store[7]));
		eputs("\r\n");
		//free(target_point);
		//clyde
		target_point = _clyde_feed_next(false, false);
		copy_point_values(entity_move_direction_store[9],target_point);
		eputs("Clyde target\r\n");
		printDecimal(get_x_point_coord(entity_move_direction_store[9]));
		printDecimal(get_y_point_coord(entity_move_direction_store[9]));
		eputs("\r\n");
		//free(target_point);


		remove_grid_state(get_x_point_coord(get_blinky_position()), get_y_point_coord(get_blinky_position()),cell_blinky);
 		add_grid_state(get_x_point_coord(entity_move_direction_store[3]), get_y_point_coord(entity_move_direction_store[3]), cell_blinky);

		remove_grid_state(get_x_point_coord(get_inky_position()), get_y_point_coord(get_inky_position()),cell_inky);
 		add_grid_state(get_x_point_coord(entity_move_direction_store[5]), get_y_point_coord(entity_move_direction_store[5]), cell_inky);

		remove_grid_state(get_x_point_coord(get_pinky_position()), get_y_point_coord(get_pinky_position()),cell_pinky);
 		add_grid_state(get_x_point_coord(entity_move_direction_store[7]), get_y_point_coord(entity_move_direction_store[7]), cell_pinky);

		remove_grid_state(get_x_point_coord(get_clyde_position()), get_y_point_coord(get_clyde_position()),cell_clyde);
		add_grid_state(get_x_point_coord(entity_move_direction_store[9]), get_y_point_coord(entity_move_direction_store[9]), cell_clyde);

		move_entities(entity_move_direction_store,entity_move_order,5);

		//set the internal positions of each entity to their new positions
		set_pacman_position(pacman_new_x, pacman_new_y);
		set_blinky_position(get_x_point_coord(entity_move_direction_store[3]), get_y_point_coord(entity_move_direction_store[3]));
		set_inky_position(get_x_point_coord(entity_move_direction_store[5]), get_y_point_coord(entity_move_direction_store[5]));
		set_pinky_position(get_x_point_coord(entity_move_direction_store[7]), get_y_point_coord(entity_move_direction_store[7]));
		set_clyde_position(get_x_point_coord(entity_move_direction_store[9]), get_y_point_coord(entity_move_direction_store[9]));

		if (get_blinky_mode() == scatter && compare_points(get_blinky_position(),get_blinky_scatter_position()))
		{	
			set_blinky_mode(chase);
		}
		if (get_inky_mode() == scatter && compare_points(get_inky_position(),get_inky_scatter_position()))
		{	
			set_inky_mode(chase);
		}
		if (get_pinky_mode() == scatter && compare_points(get_pinky_position(),get_pinky_scatter_position()))
		{	
			set_pinky_mode(chase);
		}

		if (get_clyde_mode() == scatter && compare_points(get_clyde_position(),get_clyde_scatter_position()))
		{	
			set_clyde_mode(chase);
		}
		

		if(pellet_count == 0) {
			//normally we would go to a game ended or victory page and clean up, but for now we just clean up only
			eputs("game completed");
			break;
		}

	}

	destroy_grid();

	return 0;
}