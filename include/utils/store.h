/* 
#ifndef STORE_H
#define STORE_H

#include "stm32f0xx_hal.h"
#include <stdbool.h>

    Our microcontroller has 32KB Flash. 
    from the docs I found out that it works with pages 
    each page are 1KB (1024 bytes) each.
    page 31 (would be the last page) should start at 0x08007C00. far away from code and consts

    Please also verify that this is correct... i.e where we should start our address 'FLASH_USER_START_ADDR'
    I checked as well 31000 is around 0x08007C00 in hex... (also verify)
    By the way, saving it this way means that after the area where we save our data is wasted (about 1kb)... we can try offsetting maybe?

    Lets discuss this



#define FLASH_USER_START_ADDR   0x08007C00 // page 31
#define NAME_ADDR_START         (FLASH_USER_START_ADDR + 0) // offsetting from start like arrays 
#define SCORE_ADDR_START        (FLASH_USER_START_ADDR + 8)  // offset for 7 chars + null
#define SOUND_ADDR_START        (FLASH_USER_START_ADDR + 10) // offset for uint16_t score
//I could also use a struct here since they are stored sequentially as well. We can discuss this when we talk this evening

// On the flash for our microcontroller, we need erase the entire 1KB page before writing new data.
// really problematic
// so I just wrote it into a function so it can just be pieced together after
//
void Erase_User_Page();


//all of the reading
//read from uint8_t
uint8_t Read_Flash_Byte(uint32_t address);

//a word is 4 bytes and half word is 2 bytes. double word is 64 bits - 8 bytes :)
uint16_t Read_Flash_HalfWord(uint32_t address);

// main interfaces that we would use in main loop to get data
void get_name(char read_into[]);

uint16_t get_score();

uint8_t get_sound_preferences();


 * IMPORTANT: because we can only erase by Page, we have to save all variables 
 * at once. Otherwise, setting the score would delete the name and vice versa fore each part stored.
 *
 * apparently the flash has to be locked and unlocked before and after access like a mutex
 * maybe it anticipated a multithreading environment... who knows

void save_all_settings(const char name[], uint16_t score, uint8_t sound_pref);

#endif // STORE_H
*/