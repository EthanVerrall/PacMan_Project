#include "../include/game_play/game_logic.h"

void pac_eats_target_cell(Point move_pair[], uint8_t pacman_new_x, uint8_t pacman_new_y,
	bool is_cell_eaten[], uint8_t* pellet_count, uint8_t* god_mode_timer) {

		if (is_cell_eaten[0] == true) {

			//dereference pellet count and decrement
			(*pellet_count)--;
			update_score(score_pellet);
			remove_grid_state(pacman_new_x, pacman_new_y, cell_pellet);
			add_grid_state(pacman_new_x, pacman_new_y, cell_blank);

			is_cell_eaten[0] = false;
		} 
		else if (is_cell_eaten[1] == true) {
			
			update_score(score_cherry);
			remove_grid_state(pacman_new_x, pacman_new_y, cell_cherry);
			add_grid_state(pacman_new_x, pacman_new_y, cell_blank);

			is_cell_eaten[1] = false;
		}
		else if (is_cell_eaten[2] == true) {
			update_score(score_powerup);
			remove_grid_state(pacman_new_x, pacman_new_y, cell_power_up);
			add_grid_state(pacman_new_x, pacman_new_y, cell_blank);
			*god_mode_timer = 15;

			is_cell_eaten[2] = false;
		}
}

void check_if_eat_ghost_static(Point move_pair[]) {

	if (has_grid_state_point(get_pacman_position(),cell_blinky) && (get_blinky_mode() == fright))
	{	
		set_blinky_mode(chase);
		remove_grid_state_point(get_blinky_position(),cell_blinky);
		set_blinky_position(10,7);
		add_grid_state_point(get_blinky_position(),cell_blinky);
		copy_point_values(&move_pair[2],get_blinky_position());
		update_score(score_eat_ghost);
		eat_ghost(entity_type_blinky);
	}
	if (has_grid_state_point(get_pacman_position(),cell_inky) && (get_inky_mode() == fright))
	{
		set_inky_mode(chase);
		remove_grid_state_point(get_inky_position(),cell_inky);
		set_inky_position(10,6);
		add_grid_state_point(get_inky_position(),cell_inky);
		copy_point_values(&move_pair[4],get_inky_position());
		update_score(score_eat_ghost);
		eat_ghost(entity_type_inky);
	}
	if (has_grid_state_point(get_pacman_position(),cell_pinky) && (get_pinky_mode() == fright))
	{
		set_pinky_mode(chase);
		remove_grid_state_point(get_pinky_position(),cell_pinky);
		set_pinky_position(10,8);
		add_grid_state_point(get_pinky_position(),cell_pinky);
		copy_point_values(&move_pair[6],get_pinky_position());
		update_score(score_eat_ghost);
		eat_ghost(entity_type_pinky);
	}
	if (has_grid_state_point(get_pacman_position(),cell_clyde) && (get_clyde_mode() == fright))
	{
		set_clyde_mode(chase);
		remove_grid_state_point(get_clyde_position(),cell_clyde);
		set_clyde_position(10,9);
		add_grid_state_point(get_clyde_position(),cell_clyde);
		copy_point_values(&move_pair[8],get_clyde_position());
		update_score(score_eat_ghost);
		eat_ghost(entity_type_clyde);
	}
}

void check_if_eat_ghost_real_time(const Point point_array[], const int8_t pacmans_move_pos, 
    const enum entity_type move_order[], bool is_ghost_eaten[], const uint8_t number_of_entities) {

	const Point pacs_current = create_deep_copy_stack(&point_array[(pacmans_move_pos*2)]);
	const Point pacs_target = create_deep_copy_stack(&point_array[(pacmans_move_pos*2) + 1]);

	for (uint8_t i = 0; i < number_of_entities; ++i) {

		switch (move_order[i])
		{
			case entity_type_blinky:	
				if (get_blinky_mode() == fright && 
				compare_points(&point_array[(i*2) + 1],&pacs_current) &&
				compare_points(&point_array[(i*2)],    &pacs_target)) {
					is_ghost_eaten[i] = true;
					update_score(score_eat_ghost);
				}
				break;

			case entity_type_inky:
				if (get_inky_mode() == fright &&
				compare_points(&point_array[(i*2) + 1],&pacs_current) &&
				compare_points(&point_array[(i*2)],	   &pacs_target)) {
					is_ghost_eaten[i] = true;
					update_score(score_eat_ghost);
				}
				break;

			case entity_type_pinky:
				if (get_pinky_mode() == fright &&
				compare_points(&point_array[(i*2) + 1],&pacs_current) &&
				compare_points(&point_array[(i*2)],    &pacs_target)) {
					is_ghost_eaten[i] = true;
					update_score(score_eat_ghost);
				}
				break;

			case entity_type_clyde:
				if (get_clyde_mode() == fright &&
				compare_points(&point_array[(i*2) + 1],&pacs_current) &&
				compare_points(&point_array[(i*2)],    &pacs_target)) {
					is_ghost_eaten[i] = true;
					update_score(score_eat_ghost);
				}
				break;

			case entity_type_pacman: is_ghost_eaten[i] = false;
				break;

			default:
				//Do nothing
				break;
		}
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

void set_ghosts_mode(const GhostMode mode){
	set_blinky_mode(mode);
	set_inky_mode(mode);
	set_pinky_mode(mode);
	set_clyde_mode(mode);
}

void reset_eaten_ghosts(Point move_pair[], bool is_ghost_eaten[], const enum entity_type move_order[], const uint8_t number_of_entities) {

	for (uint8_t i = 0; i < number_of_entities; ++i) {

		if (is_ghost_eaten[i] == true) {

			switch (move_order[i]) {

			case entity_type_blinky:
				remove_grid_state_point(get_blinky_position(),cell_blinky);
				add_grid_state(10,7,cell_blinky);
				set_blinky_position(10,7);
				set_blinky_mode(chase);
				copy_point_values(&move_pair[2],get_blinky_position());
				break;

			case entity_type_inky:
				remove_grid_state_point(get_inky_position(),cell_inky);
				add_grid_state(10,6,cell_inky);
				set_inky_position(10,6);
				set_inky_mode(chase);
				copy_point_values(&move_pair[4],get_inky_position());
				break;

			case entity_type_pinky:
				remove_grid_state_point(get_pinky_position(),cell_pinky);
				add_grid_state(10,8,cell_pinky);
				set_pinky_position(10,8);
				set_pinky_mode(chase);
				copy_point_values(&move_pair[6],get_pinky_position());
				break;

			case entity_type_clyde:
				remove_grid_state_point(get_clyde_position(),cell_clyde);
				add_grid_state(10,9,cell_clyde);
				set_clyde_position(10,9);
				set_clyde_mode(chase);
				copy_point_values(&move_pair[8],get_clyde_position());
				break;

			case entity_type_pacman: 
				continue;

			default:
				//Do nothing
				break;
			}
		}
		is_ghost_eaten[i] = false;
	}
}

bool is_pacman_dead(const Point points[], enum entity_type entities[]) {

	for (uint8_t i = 0; i < 5; ++i) {
		if ((entities[i] != entity_type_pacman) &&
			compare_points(&points[(i*2) + 1],&points[0]) &&
			compare_points(&points[(i*2)],    &points[1])) 
		{
			//Call death draw function
			switch (entities[i]) {
				case entity_type_blinky:
					if (get_blinky_mode() != fright) 
					{
						draw_pacman_dying(points[0],points[(i*2)],entities[i]);
						return true;
					}
					break;

				case entity_type_inky:
					if (get_inky_mode() != fright)
					{
						draw_pacman_dying(points[0],points[(i*2)],entities[i]);
						return true;
					}
					break;

				case entity_type_pinky:
					if (get_pinky_mode() != fright)
					
					{
						draw_pacman_dying(points[0],points[(i*2)],entities[i]);
						return true;
					}
					break;
					
				case entity_type_clyde:
					if (get_clyde_mode() != fright)
					{
						draw_pacman_dying(points[0],points[(i*2)],entities[i]);
						return true;
					}
					break;

				default:
				return false;
			}	
		}
	}
	
	return false;
}

void reset_round(Point move_pair[], uint8_t* god_mode_timer, bool* button_pressed, bool is_ghost_eaten[], bool is_cell_eaten[]) {

	remove_grid_state_point(&move_pair[1], cell_pacman);
	remove_grid_state_point(&move_pair[3], cell_blinky);
	remove_grid_state_point(&move_pair[5], cell_inky);
	remove_grid_state_point(&move_pair[7], cell_pinky);
	remove_grid_state_point(&move_pair[9], cell_clyde);

	add_grid_state(15,7,cell_pacman);
	add_grid_state(10,6,cell_inky);
	add_grid_state(10,7,cell_blinky);
	add_grid_state(10,8,cell_pinky);
	add_grid_state(10,9,cell_clyde);

	set_point_coord(15,7,&move_pair[0]);
	set_point_coord(10,7,&move_pair[2]);
	set_point_coord(10,6,&move_pair[4]);
	set_point_coord(10,8,&move_pair[6]);
	set_point_coord(10,9,&move_pair[8]);

	for (uint8_t i = 1; i < 10; i += 2) {

		move_pair[i].x = INVALID_POINT;
		move_pair[i].y = INVALID_POINT;
	}

	set_pacman_position(15,7);
	set_pacman_state(Mortal);
	*god_mode_timer = 0;

	set_blinky_position(10,7);
	_blinky_feed_next(false,true);

	set_inky_position(10,6);
	_inky_feed_next(false,true);

	set_pinky_position(10,8);
	_pinky_feed_next(false,true);

	set_clyde_position(10,9);
	_clyde_feed_next(false,true);

	set_ghosts_mode(scatter);

	for (uint8_t i = 0; i < 5; ++i) {
		is_ghost_eaten[i] = false;
	}

	is_cell_eaten[0] = false;
	is_cell_eaten[1] = false;
	is_cell_eaten[2] = false;

	*button_pressed = false;
	set_pacman_direction(PAC_NONE);

	uint8_t pacmans_life = get_pacman_life();
	set_pacman_life(--pacmans_life);
	display_life_LED(pacmans_life);

	if (get_music_setting()) {
		death_sound();
	}
	playNote(0);
	draw_current_page();
	delay(2000);
}

void restart_game(Point move_pair[], uint8_t* const pellet_count, bool* const button_pressed, Point* const target_point, 
				 uint8_t* const god_mode_timer, bool is_ghost_eaten[], bool is_cell_eaten[]) {

	create_reset_grid();

	set_pacman_position(15,7);
	set_pacman_state(Mortal);
    set_pacman_direction(PAC_NONE);

	set_blinky_position(10,7);
	_blinky_feed_next(false,true);

	set_inky_position(10,6);
	_inky_feed_next(false,true);

	set_pinky_position(10,8);
	_pinky_feed_next(false,true);

	set_clyde_position(10,9);
	_clyde_feed_next(false,true);

	set_ghosts_mode(scatter);

	set_point_coord(15,7,&move_pair[0]);
	set_point_coord(10,7,&move_pair[2]);
	set_point_coord(10,6,&move_pair[4]);
	set_point_coord(10,8,&move_pair[6]);
	set_point_coord(10,9,&move_pair[8]);

	for (uint8_t i = 1; i < 10; i += 2) {

		move_pair[i].x = INVALID_POINT;
		move_pair[i].y = INVALID_POINT;
	}

	*pellet_count = 111;
	*button_pressed = false;
	target_point->x = INVALID_POINT;
	target_point->y = INVALID_POINT;
	*god_mode_timer = 0;

	for (uint8_t i = 0; i < 5; ++i) {
		is_ghost_eaten[i] = false;
	}

	is_cell_eaten[0] = false;
	is_cell_eaten[1] = false;
	is_cell_eaten[2] = false;

	reset_score();
	set_pacman_life(4);
	turn_on_LEDS();
}

//Cleanup function
void exit_game(Point entity_store[], bool* play_game) {
	//free feed
	_inky_feed_next(false, true);
	_blinky_feed_next(false, true);
	_pinky_feed_next(false, true);
	_clyde_feed_next(false, true);
	
	//destroy characters
	destroy_blinky();
	destroy_inky();
	destroy_clyde();
	destroy_pinky();
	destroy_pacman();
	destroy_grid();

	for (uint8_t i = 1; i < 10; i+=2)
	{
		entity_store[i].x = INVALID_POINT;
		entity_store[i].y = INVALID_POINT;
	}

	//go back to the main page
	set_menu_page(menu_page_home);
	*play_game = false;
	reset_score();
	reset_user_name();
}

void play_game() {

	//New game - Ask the user to enter their name
	draw_current_page();
	input_user_name();

	//Set to game page so we can draw the grid
	set_menu_page(menu_page_game);

    //set up ghosts and pacman
	Pacman* pacman_ref = _pacman(false);
	Blinky* blinky_ref = _blinky(false);
	Clyde* clyde_ref = _clyde(false);
	Pinky* pinky_ref = _pinky(false);
	Inky* inky_ref = _inky(false);

	/*
		--pacman--
	Pos = 0 / Target = 1
		--blinky--
	Pos = 2 / Target = 3
		--inky--
	Pos = 4 / Target = 5
		--pinky--
	Pos = 6 / Target = 7
		--clyde--
	Pos = 8 / Target = 9
	*/
	Point move_pair[10];
	move_pair[0] = create_deep_copy_stack(get_pacman_position());
	move_pair[2] = create_deep_copy_stack(get_blinky_position());
	move_pair[4] = create_deep_copy_stack(get_inky_position());
	move_pair[6] = create_deep_copy_stack(get_pinky_position());
	move_pair[8] = create_deep_copy_stack(get_clyde_position());

	for (uint8_t i = 0; i < 10; i +=2) {
		move_pair[i+1].x = INVALID_POINT;
		move_pair[i+1].y = INVALID_POINT;
	}

	const enum entity_type entity_move_order[] = {
		entity_type_pacman, entity_type_blinky, entity_type_inky, entity_type_pinky, entity_type_clyde
	};

	bool play_game = true;
	bool button_pressed = false;
	uint8_t pellet_count = 111;
	Point target_point = {INVALID_POINT,INVALID_POINT};
	uint8_t god_mode_timer = 0;
	bool is_ghost_eaten[] = {false, false, false, false, false};
	bool is_cell_eaten[] = {false, false, false};
	turn_on_LEDS();
	create_reset_grid();
	draw_current_page();

	if (get_music_setting()) {
		
		pacman_intro_tune();
	}
	else {
		delay(2000);
	}
	
	//main game loop here
	while (play_game && get_pacman_life() != 0)
	{	
		//Pause menu is here
		while (get_active_menu_page() == menu_page_pause) {	
			//stop any sounds from the speakers
			playNote(0);
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
			
			if (get_active_menu_page() == menu_page_restart) {
				restart_game(move_pair,&pellet_count,&button_pressed,&target_point, &god_mode_timer, is_ghost_eaten, is_cell_eaten);
				set_menu_page(menu_page_game);
			}
			
			if (get_active_menu_page() == menu_page_game) {
				draw_current_page();
				delay(2000);
			}
			
			if (get_active_menu_page() == menu_page_home) {
				play_game = false;
			}
		}
		//Break to exit the game
		if (!play_game) break;
		
		if(button_pressed = is_button_down_pressed()) set_pacman_direction(PAC_BOTTOM);
		else if(button_pressed = is_button_right_pressed()) set_pacman_direction(PAC_RIGHT);
		else if(button_pressed = is_button_left_pressed()) set_pacman_direction(PAC_LEFT);
		else if(button_pressed = is_button_up_pressed()) set_pacman_direction(PAC_TOP);
		
		uint8_t pacman_new_x = get_pacman_position()->x + get_pac_dx();
		uint8_t pacman_new_y = get_pacman_position()->y + get_pac_dy();
		//wrapping pacman when he goes offscreen...........
		pacman_new_y = pacman_new_y == 16 ? 0 : pacman_new_y;
		pacman_new_y = pacman_new_y == 255 ? 15 : pacman_new_y;
		if (!has_grid_state(pacman_new_x, pacman_new_y, cell_wall | cell_gate))
		{
			set_point_coord(pacman_new_x, pacman_new_y,&move_pair[1]);
			remove_grid_state_point(&move_pair[0], cell_pacman);

			if(has_grid_state_point(&move_pair[1],cell_pellet)) {
				is_cell_eaten[0] = true;
			}
			if(has_grid_state_point(&move_pair[1],cell_cherry)) {
				is_cell_eaten[1] = true;
			}
			if(has_grid_state_point(&move_pair[1],cell_power_up)) {
				is_cell_eaten[2] = true;
			}
			add_grid_state(pacman_new_x, pacman_new_y, cell_pacman);
		}
		else
		{
			pacman_new_x = get_pacman_position()->x;
			pacman_new_y = get_pacman_position()->y;
			move_pair[1].x = pacman_new_x;
			move_pair[1].y = pacman_new_y;
		}
		//Run algo on ghosts based on pacman's current position
		//Blinky
		target_point = _blinky_feed_next(get_blinky_behaviour_change(),false);
		copy_point_values(&move_pair[3],&target_point);
		//inky
		target_point = _inky_feed_next(get_inky_behaviour_change(), false);
		copy_point_values(&move_pair[5],&target_point);
		//pinky
		target_point = _pinky_feed_next(get_pinky_behaviour_change(), false);
		copy_point_values(&move_pair[7],&target_point);
		//clyde
		target_point = _clyde_feed_next(get_clyde_behaviour_change(), false);
		copy_point_values(&move_pair[9],&target_point);

		remove_grid_state_point(get_blinky_position(), cell_blinky);
 		add_grid_state_point(&move_pair[3], cell_blinky);
		remove_grid_state_point(get_inky_position(), cell_inky);
 		add_grid_state_point(&move_pair[5], cell_inky);
		remove_grid_state_point(get_pinky_position(), cell_pinky);
 		add_grid_state_point(&move_pair[7], cell_pinky);
		remove_grid_state_point(get_clyde_position() ,cell_clyde);
		add_grid_state_point(&move_pair[9], cell_clyde);
		/*
			Pacman will check if the direction he is moving too will collide with a ghost
			therefore he will simply eat the ghost if it is ellgibale to be eaten.
			This checks for moving ghosts, dynamic moving eat function
		*/
		if (get_pacman_state() == God) {check_if_eat_ghost_real_time(
			move_pair,
			0,
			entity_move_order,
			is_ghost_eaten, 
			5);
		}
		//Checking if pacman is dying -- dynamic
		if (is_pacman_dead(move_pair,entity_move_order)) {
			reset_round(move_pair, &god_mode_timer,&button_pressed,is_ghost_eaten,is_cell_eaten);
			target_point.x = INVALID_POINT;
			target_point.y = INVALID_POINT;
			continue;
		}

		//If pacman does not die this turn because he didnt collided with a ghost, then we can update grid states and scores
		pac_eats_target_cell(move_pair,pacman_new_x, pacman_new_y,is_cell_eaten,&pellet_count,&god_mode_timer);

		//Visual drawing for this turn of the game
		move_entities(move_pair,entity_move_order,5, is_ghost_eaten);

		//set the internal positions of each entity to their new positions
		set_pacman_position(pacman_new_x, pacman_new_y);
		copy_point_values(get_blinky_position(), &move_pair[3]);
		copy_point_values(get_inky_position(), &move_pair[5]);
		copy_point_values(get_pinky_position(), &move_pair[7]);
		copy_point_values(get_clyde_position(), &move_pair[9]);
		copy_point_values(&move_pair[0], &move_pair[1]);
		copy_point_values(&move_pair[2], &move_pair[3]);
		copy_point_values(&move_pair[4], &move_pair[5]);
		copy_point_values(&move_pair[6], &move_pair[7]);
		copy_point_values(&move_pair[8], &move_pair[9]);

		//Reset ghosts we collided with
		reset_eaten_ghosts(move_pair,is_ghost_eaten,entity_move_order,5);

		//Starting the counter for pacmans god mode and setting ghosts to fright mode
		if (god_mode_timer == 15)
		{
			set_ghosts_mode(fright);
			set_pacman_state(God);
		}
		/*
			Static_movement eat function checker, this checks if pacman is sharing a cell with a ghost
		    This eat function occurs after all movement and pacman simply eats all eligible ghosts, 
			they must be in fright mode in order to be eaten.
		*/	
		if (get_pacman_state() == God) {check_if_eat_ghost_static(move_pair);}
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
			update_score(score_life * get_pacman_life());
			target_point.x = INVALID_POINT;
			target_point.y = INVALID_POINT;
			
			if (get_music_setting()) {
				winning_music();
			}

			if (update_highscores()) {
				eputs("You win - new highscore.\r\n");
			}
			else {
				eputs("You win\r\n");
			}
			
			break;
		}
		//Checking if pacman died -- static
		if (has_grid_state_point(get_pacman_position(), cell_blinky | cell_pinky | cell_inky | cell_clyde)) {
			reset_round(move_pair, &god_mode_timer,&button_pressed,is_ghost_eaten,is_cell_eaten);
			target_point.x = INVALID_POINT;
			target_point.y = INVALID_POINT;
			continue;
		}
		//Check if the user wants to pause
		if (is_button_pause_pressed()) {
			set_menu_page(menu_page_pause);
			draw_current_page();
		}
		target_point.x = INVALID_POINT;
		target_point.y = INVALID_POINT;
	}	
	
	if (get_pacman_life() == 0) {
		eputs("You lose, no more lives remaining\r\n");
	}

	exit_game(move_pair, &play_game);
}