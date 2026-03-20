#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/serial.h"
#include "../include/utils/events.h"

int main()
{
	SET_UP_STM();
	
	while (1) {
		
		if(is_button_up_pressed()) eputs("Button up pressed\r\n");
		if(is_button_right_pressed()) eputs("Button right pressed\r\n");
		if(is_button_left_pressed()) eputs("Button left pressed\r\n");
		if(is_button_down_pressed()) eputs("Button down pressed\r\n");
	}

	return 0;
}