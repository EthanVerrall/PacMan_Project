#include "../include/frontend&drawing/draw_manager.h"
#include "../include/grid.h"
#include "../include/serial.h"
#include "../include/utils/events.h"

int main()
{	
	SET_UP_STM();
	//create_reset_grid();
	set_menu_page(menu_page_game);
	draw_current_page();

	destroy_grid();
	return 0;
}