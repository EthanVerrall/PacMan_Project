#include <stm32f031x6.h>
#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/music&sound/sound.h"
#include "../include/music&sound/musical_notes.h"
#include "../include/serial.h"
#include <stdlib.h>
#include <time.h>

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
	initSerial();

	create_reset_grid();
	draw_starting_grid();

	const enum entity_type move_order[] = {entity_type_pacman, entity_type_pinky};

	Point* point_array[] = {

	create_point(10,4), //0 pacman current
	create_point(0,0), //1 pacman target
	create_point(10,11), //2 pinky current
	create_point(0,0) //3 pinky target
	};

	//Testing off screen wrapping
	for (int i = 0; i < 5; ++i) {
		
		//Setting targets based on current position
		set_point_coord(get_x_point_coord(point_array[0]), get_y_point_coord(point_array[0]) - 1, point_array[1]);
		set_point_coord(get_x_point_coord(point_array[2]), get_y_point_coord(point_array[2]) + 1, point_array[3]);
		
		//Check if target is in bounds
		if (get_y_point_coord(point_array[1]) == 255) {
			set_y_point_coord(15, point_array[1]);
		}

		if (get_y_point_coord(point_array[3]) == 16) {
			set_y_point_coord(0,point_array[3]);
		}

		//Logging purposes
			eputs("Iteration: ");
			printDecimal(i + 1);
			eputs("\r\nPacman\r\n");
			printDecimal(get_x_point_coord(point_array[0]));
			printDecimal(get_y_point_coord(point_array[0]));
			eputs("\r\n");
			printDecimal(get_x_point_coord(point_array[1]));
			printDecimal(get_y_point_coord(point_array[1]));

			eputs("\r\nPinky\r\n");
			printDecimal(get_x_point_coord(point_array[2]));
			printDecimal(get_y_point_coord(point_array[2]));
			eputs("\r\n");
			printDecimal(get_x_point_coord(point_array[3]));
			printDecimal(get_y_point_coord(point_array[3]));
			eputs("\r\n\r\n");

		//Physical move
		move_entities(point_array, move_order, 2);

		//Updating current point to what target was
		set_y_point_coord(get_y_point_coord(point_array[1]), point_array[0]);
		set_y_point_coord(get_y_point_coord(point_array[3]), point_array[2]);
		
	}
	//Testing off screen wrapping

	//Freein grid
	destroy_grid();
	
	//Cleaning up points
	for (int i = 0; i < 2; ++i) {

		point_array[i] = destroy_point(point_array[i]);
	}

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