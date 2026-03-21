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
	create_reset_grid();
	set_menu_page(menu_page_game);

	//set up ghosts and pacman
	Pacman* pacman_ref = _pacman();

	Blinky* blinky_ref = _blinky();
	Clyde* clyde_ref = _clyde();
	Pinky* pinky_ref = _pinky();
	Inky* inky_ref = _inky();

	Point* entity_move_direction_store[] = {
		//pacman movement
		//get_pacman_position(),create_point(0,0),
		//blinky movement
		get_blinky_position(), 
		create_point(0,0)
	}; 

	const enum entity_type entity_move_order[] = {
		entity_type_blinky, entity_type_pacman
	};

	bool button_pressed = false;
	uint8_t pellet_count = 111;

	
	draw_current_page();

	while (1)
	{
	/*
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
	*/

		//run algo on ghosts based on pacman's current position

		//blinky is in array 2,3
		
		Point* temp_point = _blinky_feed_next(false,false);
		set_point_coord(
			get_x_point_coord(temp_point),
			get_y_point_coord(temp_point),
			entity_move_direction_store[1]
		);

		free(temp_point);

		remove_grid_state(get_x_point_coord(get_blinky_position()), get_y_point_coord(get_blinky_position()),cell_blinky);
 		add_grid_state(get_x_point_coord(entity_move_direction_store[1]), get_y_point_coord(entity_move_direction_store[1]), cell_blinky);


		move_entities(entity_move_direction_store,entity_move_order,1);

		//set the internal positions of each entity to their new positions
//		set_pacman_position(pacman_new_x, pacman_new_y);
		set_point_coord(get_x_point_coord(entity_move_direction_store[1]), get_y_point_coord(entity_move_direction_store[1]), entity_move_direction_store[0]);

		if (get_blinky_mode() == scatter && compare_points(get_blinky_position(),get_blinky_scatter_position()))
		{	
			set_blinky_mode(chase);
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