#include <stm32f031x6.h>
#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/music&sound/sound.h"
#include "../include/music&sound/musical_notes.h"
#include "../include/serial.h"

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

volatile uint32_t milliseconds;

int main()
{
	initClock();
	initSysTick();
	setupIO();
	initSound();

	create_reset_grid();
	draw_starting_grid();

	Point* point_array[10] =
	{
		//Inky
		create_point(10,6),
		create_point(0,0),

		//Blinky
		create_point(10,7),
		create_point(0,0),

		//Pinky
		create_point(10,8),
		create_point(0,0),

		//Clyde
		create_point(10,9),
		create_point(0,0),

		//Pacman
		create_point(15,7),
		create_point(0,0)
	};

	enum entity_type entity_array[5] =
	{
		entity_type_inky,
		entity_type_blinky,
		entity_type_pinky,
		entity_type_clyde,
		entity_type_pacman
	};

	bool run_game = true;
	while (run_game) {

		for (uint8_t i = 0u; i < 10; i += 2) {

			// Get the current pos
			uint8_t const current_x = get_x_point_coord(point_array[i]);
			uint8_t const current_y = get_y_point_coord(point_array[i]);

			// Get the target pos
			uint8_t const target_x = get_x_point_coord(point_array[i + 1u]);
			uint8_t const target_y = get_y_point_coord(point_array[i + 1u]);

			// Create mask for all directions and valid moves
			uint8_t 	  allowed_move_mask = 0u; 	    // 0 0 0 0
			uint8_t const left  			= 1u << 0u; // 0 0 0 1
			uint8_t const right 			= 1u << 1u; // 0 0 1 0
			uint8_t const up    			= 1u << 2u; // 0 1 0 0
			uint8_t const down  			= 1u << 3u; // 1 0 0 0

			// Check neighboring cells for valid moves:
			if (i == 8u) {

				// Pacman
				if (!has_grid_state(current_x	  , current_y - 1u, cell_wall | cell_gate)) { allowed_move_mask |= left;  } // Check left
				if (!has_grid_state(current_x	  , current_y + 1u, cell_wall | cell_gate)) { allowed_move_mask |= right; } // Check right
				if (!has_grid_state(current_x - 1u, current_y     , cell_wall | cell_gate)) { allowed_move_mask |= up;  } // Check up
				if (!has_grid_state(current_x + 1u, current_y     , cell_wall | cell_gate)) { allowed_move_mask |= down;  } // Check down
			} else {

				// Ghost
				if (!has_grid_state(current_x	  , current_y - 1u, cell_wall)) { allowed_move_mask |= left;  } // Check left
				if (!has_grid_state(current_x	  , current_y + 1u, cell_wall)) { allowed_move_mask |= right; } // Check right
				if (!has_grid_state(current_x - 1u, current_y     , cell_wall)) { allowed_move_mask |= up;  } // Check up
				if (!has_grid_state(current_x + 1u, current_y     , cell_wall)) { allowed_move_mask |= down;  } // Check down
			}

			// Generate random number between 0-3 (left, right, up, down)
			uint8_t random_direction_mask = 0u; // Initialize to 0 so loop can run at least once
			while(!(random_direction_mask & allowed_move_mask)) {

				uint8_t const random_num 		    = rand() % 4;
				random_direction_mask = 1u << random_num;
			}

			// Check which direction to move
			if (random_direction_mask & left) { // Check left

				// Update new target in array
				set_point_coord(current_x, current_y - 1u, point_array[i + 1u]);
			} else if (random_direction_mask & right) { // Check right

				// Update new target in array
				set_point_coord(current_x, current_y + 1u, point_array[i + 1u]);
			} else if (random_direction_mask & up) { // Check up

				// Update new target in array
				set_point_coord(current_x - 1u, current_y, point_array[i + 1u]);
			} else if (random_direction_mask & down) { // Check down

				// Update new target in array
				set_point_coord(current_x + 1u, current_y, point_array[i + 1u]);
			}
		}

		// Draw point array
		move_entity(point_array, entity_array);

		for (uint8_t i = 0u; i < 10; i += 2) {

			// Get the current pos
			uint8_t const current_x = get_x_point_coord(point_array[i]);
			uint8_t const current_y = get_y_point_coord(point_array[i]);

			// Get the target pos
			uint8_t const target_x = get_x_point_coord(point_array[i + 1u]);
			uint8_t const target_y = get_y_point_coord(point_array[i + 1u]);

			// Update grid in old position
			if (i == 8u) {
				
				// Pacman
				set_grid_state(current_x, current_y, cell_blank);
			} else {

				// Ghost
				remove_grid_state(current_x, current_y, cell_ghost);
			}

			// Update grid in new position
			uint8_t const new_target_x = get_x_point_coord(point_array[i + 1u]);
			uint8_t const new_target_y = get_y_point_coord(point_array[i + 1u]);
			if (i == 8u) {

				// Pacman
				add_grid_state(new_target_x, new_target_y, cell_pacman);
			} else {

				// Ghost
				if (!has_grid_state(new_target_x,new_target_y, cell_ghost)) {
					add_grid_state(new_target_x, new_target_y, cell_ghost);
				}
				
			}

			// Update current position
			set_x_point_coord(new_target_x, point_array[i]);
			set_y_point_coord(new_target_y, point_array[i]);

			// If its Pacman, check if ghost eats him
			if (i == 8u) {

				// Pacman
				if (has_grid_state(new_target_x, new_target_y, cell_ghost)) {

					run_game = false;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		destroy_point(point_array[i]);
	}

	destroy_grid();
	return 0;
}

void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}

void SysTick_Handler(void)
{
	milliseconds++;
}

void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared

// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface

        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) );

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);
        // set PLL as system clock source
        RCC->CFGR |= (1<<1);
}

void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}

void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}

int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}