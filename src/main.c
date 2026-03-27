#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/serial.h"
#include "../include/utils/events.h"
#include "../include/behaviours/entities&sprites/pacman.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/clyde.h"
#include "../include/behaviours/entities&sprites/pinky.h"
#include "../include/behaviours/entities&sprites/inky.h"

//This function should work well 
void check_if_eat_ghost_static() {

	if (has_grid_state_point(get_pacman_position(),cell_blinky) && (get_blinky_mode() == fright))
	{	
		set_blinky_mode(chase);
		remove_grid_state_point(get_blinky_position(),cell_blinky);
		set_blinky_position(10,7);
		add_grid_state_point(get_blinky_position(),cell_blinky);
		eat_ghost(entity_type_blinky);
		
	}
	if (has_grid_state_point(get_pacman_position(),cell_pinky) && (get_pinky_mode() == fright))
	{
		set_pinky_mode(chase);
		remove_grid_state_point(get_pinky_position(),cell_pinky);
		set_pinky_position(10,8);
		add_grid_state_point(get_pinky_position(),cell_pinky);
		eat_ghost(entity_type_pinky);
	}
	if (has_grid_state_point(get_pacman_position(),cell_inky) && (get_inky_mode() == fright))
	{
		set_inky_mode(chase);
		remove_grid_state_point(get_inky_position(),cell_inky);
		set_inky_position(10,6);
		add_grid_state_point(get_inky_position(),cell_inky);
		eat_ghost(entity_type_inky);
	}
	if (has_grid_state_point(get_pacman_position(),cell_clyde) && (get_clyde_mode() == fright))
	{
		set_clyde_mode(chase);
		remove_grid_state_point(get_clyde_position(),cell_clyde);
		set_clyde_position(10,9);
		add_grid_state_point(get_clyde_position(),cell_clyde);
		eat_ghost(entity_type_clyde);
	}
}

void set_scatter_mode_to_chase_mode() {

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
}

void check_if_eat_ghost_real_time(const Point* const point_array[], const int8_t pacmans_move_pos, 
    const enum entity_type move_order[], bool is_ghost_eaten[], const uint8_t number_of_entities) {

	Point* pacs_current = create_deep_copy(point_array[(pacmans_move_pos*2)]);
	Point* pacs_target = create_deep_copy(point_array[(pacmans_move_pos*2) + 1]);

	for (uint8_t i = 0; i < number_of_entities; ++i) {

		switch (move_order[i])
		{
			case entity_type_blinky:	
				if (get_blinky_mode() == fright && 
				compare_points(point_array[(i*2) + 1],pacs_current) &&
				compare_points(point_array[(i*2)],pacs_target)) {
					is_ghost_eaten[i] = true;
				}
					
				break;
			case entity_type_inky:
				if (get_inky_mode() == fright &&
				compare_points(point_array[(i*2) + 1],pacs_current) &&
				compare_points(point_array[(i*2)],pacs_target)) {
					is_ghost_eaten[i] = true;
				}
				break;
			case entity_type_pinky:
				if (get_pinky_mode() == fright &&
				compare_points(point_array[(i*2) + 1],pacs_current) &&
				compare_points(point_array[(i*2)],pacs_target)) {
					is_ghost_eaten[i] = true;
				}
				break;
			case entity_type_clyde:
				if (get_clyde_mode() == fright &&
				compare_points(point_array[(i*2) + 1],pacs_current) &&
				compare_points(point_array[(i*2)],pacs_target)) {
					is_ghost_eaten[i] = true;
				}
				break;

			case entity_type_pacman: is_ghost_eaten[i] = false;
				break;

			default:
				eputs("Error with function check_if_eat_ghost_real_time(), unknown entity, function aborted.\r\n");
				break;
		}
	}
//Freeing points
	pacs_current = destroy_point(pacs_current);
	pacs_target = destroy_point(pacs_target);
}

void set_ghosts_mode(GhostMode mode){
	set_blinky_mode(mode);
	set_inky_mode(mode);
	set_pinky_mode(mode);
	set_clyde_mode(mode);
}

void reset_eaten_ghosts(bool is_ghost_eaten[], const enum entity_type move_order[], const uint8_t number_of_entities) {

	for (uint8_t i = 0; i < number_of_entities; ++i) {

		if (is_ghost_eaten[i] == true) {

			switch (move_order[i]) {

			case entity_type_blinky:
				remove_grid_state_point(get_blinky_position(),cell_blinky);
				add_grid_state(10,7,cell_blinky);
				set_blinky_position(10,7);
				set_blinky_mode(chase);
				break;

			case entity_type_inky:
				remove_grid_state_point(get_inky_position(),cell_inky);
				add_grid_state(10,6,cell_inky);
				set_inky_position(10,6);
				set_inky_mode(chase);
				break;

			case entity_type_pinky:
				remove_grid_state_point(get_pinky_position(),cell_pinky);
				add_grid_state(10,8,cell_pinky);
				set_pinky_position(10,8);
				set_pinky_mode(chase);
				break;

			case entity_type_clyde:
				remove_grid_state_point(get_pinky_position(),cell_clyde);
				add_grid_state(10,9,cell_clyde);
				set_clyde_position(10,9);
				set_clyde_mode(chase);
				break;

			case entity_type_pacman: 
				continue;

			default:
				eputs("Error with reset_eaten_ghosts function, unknown entity type.\r\n");
				break;
			}
		}
		is_ghost_eaten[i] = false;
	}
}

//Tomorrow -- reset to defaults function
void restart_game();

//Tomorrow -- cleanup function
void exit_game();

int main()
{	
	//set up grid and IO
	SET_UP_STM();
	turn_off_LEDS();
	draw_current_page();

	while (1) {


		while (get_active_menu_page() == menu_page_home) {

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
				move_cursor(MOVE_CURSOR_left);
				delay(25);
			}
		}

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
			entity_type_pacman, entity_type_blinky, entity_type_inky, entity_type_pinky, entity_type_clyde
		};

		bool play_game = true;
		bool button_pressed = false;
		uint8_t pellet_count = 111;
		const Point* target_point = NULL;
		uint8_t god_mode_timer = 0;
		bool is_ghost_eaten[] = {false, false, false, false, false};

		turn_on_LEDS();
		create_reset_grid();
		draw_current_page();
		delay(1000);

		while (play_game)
		{	
			while (get_active_menu_page() == menu_page_pause) {	
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
				move_cursor(MOVE_CURSOR_left);
				delay(25);
				}

				//Exit pause menu and resume the game
				if (get_active_menu_page() == menu_page_game) {
					draw_current_page();

					delay(2000);
				}

				if (get_active_menu_page() == menu_page_home) {

					//exit_game();
					play_game = false;
					draw_current_page();
					delay(25);
				}
			}
			//Break to exit the game
			if (!play_game) break;

			//check for button presses first
			//for now we would just check directly, but for the case that we would want to save time,
			//there would be a function that would check a list of numbers representing the button pressed

			//all buttons (arrow buttons and not pause) do in the game page: chang`e pacmans dx and dy
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
				remove_grid_state_point(entity_move_direction_store[0], cell_pacman);

				if(has_grid_state_point(entity_move_direction_store[1],cell_pellet)) {
					pellet_count--;
					remove_grid_state(pacman_new_x, pacman_new_y, cell_pellet);
					add_grid_state(pacman_new_x, pacman_new_y, cell_blank);
				}

				if(has_grid_state_point(entity_move_direction_store[1],cell_cherry)) {
					remove_grid_state(pacman_new_x, pacman_new_y, cell_cherry);
					add_grid_state(pacman_new_x, pacman_new_y, cell_blank);
				}

				if(has_grid_state_point(entity_move_direction_store[1],cell_power_up)) {
					remove_grid_state(pacman_new_x, pacman_new_y, cell_power_up);
					add_grid_state(pacman_new_x, pacman_new_y, cell_blank);

					god_mode_timer = 15;
					set_pacman_state(God);
				}

				add_grid_state(pacman_new_x, pacman_new_y, cell_pacman);
			}
			else
			{
				pacman_new_x = get_x_point_coord(get_pacman_position());
				pacman_new_y = get_y_point_coord(get_pacman_position());
			}
		

			//run algo on ghosts based on pacman's current position

			//Blinky
			target_point = _blinky_feed_next(get_blinky_behaviour_change(),false);
			copy_point_values(entity_move_direction_store[3],target_point);

			//inky
			target_point = _inky_feed_next(get_inky_behaviour_change(), false);
			copy_point_values(entity_move_direction_store[5],target_point);

			//pinky
			target_point = _pinky_feed_next(get_pinky_behaviour_change(), false);
			copy_point_values(entity_move_direction_store[7],target_point);

			//clyde
			target_point = _clyde_feed_next(get_clyde_behaviour_change(), false);
			copy_point_values(entity_move_direction_store[9],target_point);

			//Updating grid states

			remove_grid_state_point(get_blinky_position(), cell_blinky);
 			add_grid_state_point(entity_move_direction_store[3], cell_blinky);

			remove_grid_state_point(get_inky_position(), cell_inky);
 			add_grid_state_point(entity_move_direction_store[5], cell_inky);

			remove_grid_state_point(get_pinky_position(), cell_pinky);
 			add_grid_state_point(entity_move_direction_store[7], cell_pinky);

			remove_grid_state_point(get_clyde_position() ,cell_clyde);
			add_grid_state_point(entity_move_direction_store[9], cell_clyde);

			/*
				Pacman will check if the direction he is moving too will collide with a ghost
				therefore he will simply eat the ghost if it is ellgibale to be eaten.
				This checks for moving ghosts, dynamic moving eat function
			*/

			if (get_pacman_state() == God) {check_if_eat_ghost_real_time(
				entity_move_direction_store,
				0,
				entity_move_order,
				is_ghost_eaten, 
				5);
			}

			//Visual drawing for this turn of the game
			move_entities(entity_move_direction_store,entity_move_order,5, is_ghost_eaten);


			//set the internal positions of each entity to their new positions

			set_pacman_position(pacman_new_x, pacman_new_y);
			copy_point_values(get_blinky_position(), entity_move_direction_store[3]);
			copy_point_values(get_inky_position(), entity_move_direction_store[5]);
			copy_point_values(get_pinky_position(), entity_move_direction_store[7]);
			copy_point_values(get_clyde_position(), entity_move_direction_store[9]);

			//Reset ghosts we collided with
			reset_eaten_ghosts(is_ghost_eaten,entity_move_order,5);

			//Starting the counter for pacmans god mode and setting ghosts to fright mode
			if (god_mode_timer == 15)
			{
				set_ghosts_mode(fright);
			}

			/*
				Static_movement eat function checker, this checks if pacman is sharing a cell with a ghost
			    This eat function occurs after all movement and pacman simply eats all eligible ghosts, 
				they must be in fright mode in order to be eaten.
			*/	
			if (get_pacman_state() == God) {check_if_eat_ghost_static();}

			if (god_mode_timer > 0)
			{
				god_mode_timer--;
			}
			else if (get_pacman_state() == God)
			{
				set_ghosts_mode(chase);
				set_pacman_state(Mortal);
			}

			//This function should only really run once - once ghosts reach their scatter position after the start of the game
			//they will switch to chase mode and go after pacman, this will reset their feed cache and run our algorithm and A* again
			set_scatter_mode_to_chase_mode();

			if(pellet_count == 0) {
				//normally we would go to a game ended or victory page and clean up, but for now we just clean up only
				eputs("Game Completed, you win.\r\n");
				break;
			}

			//Check if the user wants to pause
			if (is_button_pause_pressed()) {
				set_menu_page(menu_page_pause);
				draw_current_page();
			}
		}	

		//--------------------------------------------------------------------------
		//Free target point and all !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//WE MUST STILL DO THIS 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//--------------------------------------------------------------------------	
	}
	return 0;	
}
