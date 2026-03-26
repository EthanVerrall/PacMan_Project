#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
//from pacman_music
//#include "../include/music&sound/sound.h"
//#include "../include/music&sound/musical_notes.h"
//#include "../include/music&sound/tones.h"
//#include "serial.h"
#include "../include/serial.h"
#include "../include/utils/events.h"
#include "../include/behaviours/entities&sprites/pacman.h"
#include "../include/behaviours/entities&sprites/blinky.h"
#include "../include/behaviours/entities&sprites/clyde.h"
#include "../include/behaviours/entities&sprites/pinky.h"
#include "../include/behaviours/entities&sprites/inky.h"

//This function should work well 
void check_if_eat_ghost() {

//volatile uint32_t milliseconds;

//int main()
//{
	//initClock();
	//initSysTick();
	//setupIO();
	//initSound();
	
	//Creating a new grid, default drawing, and then destroying the grid
	//create_reset_grid();
	//draw_starting_grid();
	//destroy_grid();

	//pacman_intro();
	//while(1){
		//death_sound();
		//delay(300);
	//}

	//return 0;
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

void set_ghosts_mode(GhostMode mode){
	set_blinky_mode(mode);
	set_inky_mode(mode);
	set_pinky_mode(mode);
	set_clyde_mode(mode);
}

int main()
{	
	//set up grid and IO
	SET_UP_STM();
  	draw_current_page();
	turn_off_LEDS();

	while (get_active_menu_page() == menu_page_home) {

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
		flicker_text();
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

	bool button_pressed = false;
	uint8_t pellet_count = 111;
	const Point* target_point = NULL;
	uint8_t god_mode_timer = 0;

	turn_on_LEDS();
	create_reset_grid();
	draw_current_page();
	delay(1000);
	
	while (1)
	{
		
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
				
				god_mode_timer = 100;
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
		//eputs("Blinky target\r\n");
		//printDecimal(get_x_point_coord(entity_move_direction_store[3]));
		//printDecimal(get_y_point_coord(entity_move_direction_store[3]));
		//eputs("\r\n");
		
		//inky
		target_point = _inky_feed_next(get_inky_behaviour_change(), false);
		copy_point_values(entity_move_direction_store[5],target_point);
		//eputs("Inky target\r\n");
		//printDecimal(get_x_point_coord(entity_move_direction_store[5]));
		//printDecimal(get_y_point_coord(entity_move_direction_store[5]));
		//eputs("\r\n");

		//pinky
		target_point = _pinky_feed_next(get_pinky_behaviour_change(), false);
		copy_point_values(entity_move_direction_store[7],target_point);
		//eputs("Pinky target\r\n");
		//printDecimal(get_x_point_coord(entity_move_direction_store[7]));
		//printDecimal(get_y_point_coord(entity_move_direction_store[7]));
		//eputs("\r\n");

		//clyde
		target_point = _clyde_feed_next(get_clyde_behaviour_change(), false);
		copy_point_values(entity_move_direction_store[9],target_point);
		//eputs("Clyde target\r\n");
		//printDecimal(get_x_point_coord(entity_move_direction_store[9]));
		//printDecimal(get_y_point_coord(entity_move_direction_store[9]));
		//eputs("\r\n");

		remove_grid_state_point(get_blinky_position(), cell_blinky);
 		add_grid_state_point(entity_move_direction_store[3], cell_blinky);

		remove_grid_state_point(get_inky_position(), cell_inky);
 		add_grid_state_point(entity_move_direction_store[5], cell_inky);

		remove_grid_state_point(get_pinky_position(), cell_pinky);
 		add_grid_state_point(entity_move_direction_store[7], cell_pinky);

		remove_grid_state_point(get_clyde_position() ,cell_clyde);
		add_grid_state_point(entity_move_direction_store[9], cell_clyde);

		move_entities(entity_move_direction_store,entity_move_order,5);

		//set the internal positions of each entity to their new positions
		set_pacman_position(pacman_new_x, pacman_new_y);
		copy_point_values(get_blinky_position(), entity_move_direction_store[3]);
		copy_point_values(get_inky_position(), entity_move_direction_store[5]);
		copy_point_values(get_pinky_position(), entity_move_direction_store[7]);
		copy_point_values(get_clyde_position(), entity_move_direction_store[9]);

	
		if (god_mode_timer == 100)
		{
			set_ghosts_mode(fright);
		}
			
		/*
			Static_movement eat function checker, this checks if pacman is sharing a cell with a ghost
		    This eat function occurs after all movement and pacman simply eats all eligible ghosts, 
			they must be in fright mode in order to be eaten.
		*/	
		if (get_pacman_state() == God) {check_if_eat_ghost();}

		if (god_mode_timer > 0)
		{
			god_mode_timer--;
		}
		else if (get_pacman_state() == God)
		{
			set_ghosts_mode(chase);
			set_pacman_state(Mortal);
		}
		
		//This function should only really run once
		set_scatter_mode_to_chase_mode();
		
		for (int i = 1; i <= 4; ++i) {

			switch (entity_move_order[i]) {

				case entity_type_blinky:
				eputs("Blinky ");
				if(get_blinky_mode() == fright) eputs("is in fright mode.\r\n");
				if(get_blinky_mode() == chase) eputs("is in chase mode.\r\n");
				break;

				case entity_type_clyde: 
				eputs("Clyde ");
				if(get_clyde_mode() == fright) eputs("is in fright mode.\r\n");
				if(get_clyde_mode() == chase) eputs("is in chase mode.\r\n");
				break;

				case entity_type_inky: 
				eputs("Inky ");
				if(get_inky_mode() == fright) eputs("is in fright mode.\r\n");
				if(get_inky_mode() == chase) eputs("is in chase mode.\r\n");
				break;

				case entity_type_pinky:
				eputs("Pinky ");
				if(get_pinky_mode() == fright) eputs("is in fright mode.\r\n");
				if(get_pinky_mode() == chase) eputs("is in chase mode.\r\n");
				break;

				default:
				eputs("Logs are failing\r\n");
				break;
			}
		}
		eputs("\r\n");

		if(pellet_count == 0) {
			//normally we would go to a game ended or victory page and clean up, but for now we just clean up only
			eputs("game completed");
			break;
		}
	}	
	
	destroy_grid();
	return 0;
}