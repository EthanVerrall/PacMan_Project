#ifndef EVENTS_H
#define EVENTS_H

#include "stm32f031x6.h"
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



//---------------
//Pacman Related functions - End
//---------------


#endif //EVENTS_H