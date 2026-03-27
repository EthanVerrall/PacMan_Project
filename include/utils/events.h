#ifndef EVENTS_H
#define EVENTS_H

#include "stm32f031x6.h"
#include "../include/music&sound/sound.h"
#include "../include/frontend&drawing/display.h"
#include "../include/serial.h"
#include <stdbool.h>

//Function is so important it deserves to be capitalised
//Turns everything on...
//The clock, the screen, buttons, makes the universe spin round at this point
//-
//ALWAYS CALL THIS FUNCTION FIRST IN MAIN, LINE ONE IF POSSIBLE
void SET_UP_STM();

//---------------
//Setup functions - Start
//---------------

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

//---------------
//Setup functions - End
//---------------



//---------------
//Pacman Related functions - Start
//---------------

//If a button is currently held down return true, otherwise return false

bool is_button_up_pressed();
bool is_button_right_pressed();
bool is_button_down_pressed();
bool is_button_left_pressed();
bool is_button_pause_pressed();

//Displays the correct LEDS based on pacmans current remaining lives

void display_life_LED(const uint8_t pacman_lives);

//Functions to turn LEDS on and off -- Turns all LEDS on and off

void turn_off_LEDS();
void turn_on_LEDS();

//Functions to turn LEDS on and off --Toggling

void toggle_high_green_LED();
void toggle_low_green_LED();
void toggle_yellow_LED();
void toggle_red_LED();

//Turn LEDS on or off manually

void turn_on_high_green_LED();
void turn_on_low_green_LED();
void turn_on_yellow_LED();
void turn_on_red_LED();

void turn_off_high_green_LED();
void turn_off_low_green_LED();
void turn_off_yellow_LED();
void turn_off_red_LED();
//---------------
//Pacman Related functions - End
//---------------


#endif //EVENTS_H