#ifndef MAIN_MENU_TITLE_H
#define MAIN_MENU_TITLE_H

#include <stdint.h>

//Forward declaring to save space, in the case this
//needs to be included in mutiple files, array holds our compressed main_menu_title logo
extern const uint8_t main_menu_array[3648];

//Function used to uncompress our main_menu_array
uint16_t find_main_menu_colour(const uint8_t map_code);

#endif //MAIN_MENU_TITLE_H