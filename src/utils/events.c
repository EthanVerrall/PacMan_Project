#include "../include/utils/events.h"

volatile uint32_t milliseconds;  //DO NOT TOUCH THIS VARIABLE, CLOCK USES THIS FOR INTERRUPTS AND TIMERS AND TICKS

void SET_UP_STM() {

    //Initial STM startup
    initClock();
	initSysTick();
	setupIO();
    initSerial();
	initSound();
}

//---------------
//Setup functions - Start
//---------------

//DONT USE THIS OUTSIDE OF FUNCTION SET_UP_STM
void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}

//DONT USE THIS OUTSIDE OF FUNCTION SET_UP_STM
void SysTick_Handler(void)
{
	milliseconds++;
}

//DONT USE THIS OUTSIDE OF FUNCTION SET_UP_STM
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

//Use for interrupts and sleeps - parameter is in milliseconds
void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

//Turn on pullup resistors for buttons
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}

//Set GPIOA PORT bits and their mode 
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

//Turns on Port A and Port B - GPIOA
//Also turns on our 4 buttons to control pacman and menu navigation
//Sets GPIOB 4, GPIOB 5, GPIOA 8, GPIOA 11 as inputs.
//Turns those 4 ports pull-up resistors on
void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	
	//Setting ports as input mode
	pinMode(GPIOB,4,0);  // Down
	pinMode(GPIOB,5,0);  // Right
	pinMode(GPIOA,8,0);  // Up
	pinMode(GPIOA,11,0); // Left
	pinMode(GPIOA,1,0); //Pause button
	
	//Turning on pull-up resistors
	enablePullUp(GPIOB,4);  // Down
	enablePullUp(GPIOB,5);  // Right
	enablePullUp(GPIOA,8);  // Up 
	enablePullUp(GPIOA,11); // Left
	enablePullUp(GPIOA,1); //Pause button

	//Turning on LEDS;
	pinMode(GPIOA,9,1); //HIGH GREEN LED
	pinMode(GPIOA,10,1); //LOW GREEN LED
	pinMode(GPIOB,0,1); //YELLOW LED
	pinMode(GPIOA,12,1); //RED LED
}
//---------------
//Setup functions - End
//---------------


//---------------
//Pacman Related functions - Start
//---------------
bool is_button_up_pressed() {

	if ((GPIOA->IDR & (1<<8)) == 0 ) return true;
	
	return false;
}

bool is_button_right_pressed() {

	if ((GPIOB->IDR & (1<<4)) == 0 ) return true;
	
	return false;
}

bool is_button_down_pressed() {

	if ((GPIOA->IDR & (1<<11)) == 0 ) return true;
	
	return false;
}

bool is_button_left_pressed() {

	if ((GPIOB->IDR & (1<<5)) == 0) return true;
	
	return false;
}

bool is_button_pause_pressed() {

	if ((GPIOA->IDR & (1<<1)) == 0) return true;
	
	return false;
}

void display_life_LED(const uint8_t pacman_lives) {
	
	switch (pacman_lives) {
		case 4: 
			turn_on_LEDS();
			break;

		case 3:
			turn_off_high_green_LED();
			turn_on_low_green_LED();
			turn_on_yellow_LED();
			turn_on_red_LED();
			break;

		case 2:
			turn_off_high_green_LED();
			turn_off_low_green_LED();
			turn_on_yellow_LED();
			turn_on_red_LED();
			break;

		case 1:
			turn_off_high_green_LED();
			turn_off_low_green_LED();
			turn_off_yellow_LED();
			turn_on_red_LED();
			break;

		case 0: 
			turn_off_LEDS();
			break;

		default:
		break;
	}
}

void turn_off_LEDS() {

	GPIOA->ODR &= ~(1<<9);
	GPIOA->ODR &= ~(1<<10);
	GPIOB->ODR &= ~(1<<0); 
	GPIOA->ODR &= ~(1<<12);  
}

void turn_on_LEDS() {

	GPIOA->ODR |= (1<<9);
	GPIOA->ODR |= (1<<10);
	GPIOB->ODR |= (1<<0); 
	GPIOA->ODR |= (1<<12);  
}

void turn_on_high_green_LED() {

	GPIOA->ODR |= (1<<9); 
}

void turn_on_low_green_LED() {

	GPIOA->ODR |= (1<<10); 
}

void turn_on_yellow_LED() {

	GPIOB->ODR |= (1<<0); 
}

void turn_on_red_LED() {

	GPIOA->ODR |= (1<<12); 
}

void turn_off_high_green_LED() {

	GPIOA->ODR &= ~(1<<9); 
}

void turn_off_low_green_LED() {

	GPIOA->ODR &= ~(1<<10); 
}

void turn_off_yellow_LED() {

	GPIOB->ODR &= ~(1<<0); 
}

void turn_off_red_LED() {

	GPIOA->ODR &= ~(1<<12); 
}
//---------------
//Pacman Related functions - End
//---------------