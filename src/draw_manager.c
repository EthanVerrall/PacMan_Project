#include "../include/draw_manager.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

bool draw_starting_grid () {

    /*
        The below two arrays are used in parallel to define the wall types 
        and how many times they must print.
    */

    const uint16_t* wall_type_pair[] = 
    {
        //Row 2
        wall_array[wall_curve_top_left], wall_array[wall_horizontal], wall_array[wall_curve_top_right],

        //Row 3
        wall_array[wall_vertical], wall_array[wall_vertical],

        //Row 4
        wall_array[wall_vertical], wall_array[wall_curve_top_left], wall_array[wall_curve_top_right], wall_array[wall_vertical], 
        wall_array[wall_horizontal], wall_array[wall_vertical], wall_array[wall_curve_top_left], wall_array[wall_curve_top_right],
        wall_array[wall_vertical],
        
        //Row 5
        wall_array[wall_vertical], wall_array[wall_curve_bottom_left], wall_array[wall_curve_bottom_right], wall_array[wall_vertical],
        wall_array[wall_vertical], wall_array[wall_curve_bottom_left], wall_array[wall_curve_bottom_right], wall_array[wall_vertical],

        //Row 6
        wall_array[wall_vertical], wall_array[wall_vertical], wall_array[wall_curve_top_left], 
        wall_array[wall_curve_top_right], wall_array[wall_vertical], wall_array[wall_vertical],

        //Row 7
        wall_array[wall_vertical], wall_array[wall_horizontal], wall_array[wall_vertical], 
        wall_array[wall_horizontal], wall_array[wall_vertical],
        
        //Row 8
        wall_array[wall_vertical], wall_array[wall_horizontal], wall_array[wall_curve_bottom_right], 
        wall_array[wall_curve_bottom_left], wall_array[wall_horizontal], wall_array[wall_vertical],
   
        //Row 9
        wall_array[wall_tri_right], wall_array[wall_horizontal], wall_array[wall_curve_top_right],
        wall_array[wall_curve_top_left], wall_array[wall_horizontal], wall_array[wall_tri_left],

        //Row 10
        wall_array[wall_tri_top], wall_array[wall_horizontal], wall_array[wall_curve_bottom_right],
        wall_array[wall_curve_top_left], wall_array[wall_horizontal], wall_array[wall_horizontal], wall_array[wall_curve_top_right],
        wall_array[wall_curve_bottom_left], wall_array[wall_horizontal], wall_array[wall_tri_top],

        //Row 11
        wall_array[wall_vertical], wall_array[wall_vertical],
        
        //Row 12
        wall_array[wall_tri_bottom], wall_array[wall_horizontal], wall_array[wall_curve_top_right],
        wall_array[wall_curve_bottom_left], wall_array[wall_horizontal], wall_array[wall_curve_bottom_right],
        wall_array[wall_curve_top_left], wall_array[wall_horizontal], wall_array[wall_tri_bottom],
        
        //Row 13
        wall_array[wall_tri_right], wall_array[wall_horizontal], wall_array[wall_curve_bottom_right],
        wall_array[wall_curve_bottom_left], wall_array[wall_horizontal], wall_array[wall_tri_left],

        //Row 14
        wall_array[wall_vertical], wall_array[wall_curve_top_left], wall_array[wall_curve_top_left],
        wall_array[wall_curve_top_right], wall_array[wall_curve_top_right], wall_array[wall_vertical],

        //Row 15
        wall_array[wall_vertical], wall_array[wall_horizontal], wall_array[wall_tri_bottom],wall_array[wall_curve_bottom_right], 
        wall_array[wall_curve_bottom_left], wall_array[wall_curve_bottom_right],
        wall_array[wall_curve_bottom_left], wall_array[wall_tri_bottom], wall_array[wall_horizontal], wall_array[wall_vertical],

        //Row 16
        wall_array[wall_vertical], wall_array[wall_vertical], wall_array[wall_vertical], wall_array[wall_vertical],

        //Row 17
        wall_array[wall_vertical], wall_array[wall_vertical],
        wall_array[wall_curve_top_left], wall_array[wall_horizontal], wall_array[wall_curve_top_right],
        wall_array[wall_vertical], wall_array[wall_vertical],

        //Row 18
        wall_array[wall_vertical], wall_array[wall_curve_bottom_left], wall_array[wall_horizontal],
        wall_array[wall_horizontal], wall_array[wall_curve_bottom_right], wall_array[wall_vertical],

        //Row 19
        wall_array[wall_vertical], wall_array[wall_curve_top_left], 
        wall_array[wall_horizontal], wall_array[wall_curve_top_right], wall_array[wall_vertical],

        //Row 20
        wall_array[wall_curve_bottom_left], wall_array[wall_horizontal], wall_array[wall_curve_bottom_right],
        wall_array[wall_curve_bottom_left], wall_array[wall_horizontal], wall_array[wall_curve_bottom_right]
    };

    const uint8_t wall_count_pair[] =
    {   
        //Row 2
        1, 14, 1,

        //Row 3
        1, 1,

        //Row 4
        1, 1, 1, 1, 2, 1, 1, 1, 1,

        //Row 5
        1, 1, 1, 1, 1, 1, 1, 1,

        //Row 6
        1, 1, 1, 1, 1, 1, 

        //Row 7
        1, 2, 2, 2, 1,

        //Row 8
        1, 2, 1, 1, 2, 1,

        //Row 9
        1, 2, 1, 1, 2, 1,

        //Row 10
        1, 2, 1, 1, 1, 1, 1, 1, 2, 1,

        //Row 11
        1, 1,

        //Row 12
        1, 2, 1, 1, 4, 1, 1, 2, 1,

        //Row 13
        1, 2, 1, 1, 2, 1,

        //Row 14
        1, 1, 1, 1, 1, 1,

        //Row 15
        1, 2, 1, 1, 1, 1, 1, 1, 2, 1,

        //Row 16
        1, 1, 1, 1,

        //Row 17
        1, 1, 1, 2, 1, 1, 1,

        //Row 18
        1, 1, 2, 2, 1, 1,

        //Row 19
        1, 1, 2, 1, 1,

        //Row 20
        1, 5, 1, 1, 5, 1
    };   

    //These variables are used to ensure all pairs of walls are printed and all 4 different ghosts are printed

    uint8_t ghost_counter = 1;
    uint8_t current_wall_pair = 0;
    uint8_t walls_left_to_print = wall_count_pair[current_wall_pair];

    //Loops through the entire grid and prints all tiles and upscaled 8*8 pixels across the screen
    //accounting for the intial offset in height from pixel 0,0

    for (uint8_t y_pixel = 0 + HEIGHT_OFFSET; y_pixel < SCREEN_HEIGHT; y_pixel += 8) {

        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; x_pixel += 8) {

            /*
                HOW THIS WORKS by Ethan Verrall :)

                We get the bitmask for the current grid cell/index that relates to the screens pixel (x,y),
                We then use the switch to check which state it is at this grid cell/index,
                We then set our pointer to the appropriate texture array,
                Finally was pass our pointer to the putImage function to draw on the screen at pixel (x,y)
            */

            const uint16_t* next_draw = NULL;
            uint8_t cell_bitmask = get_grid_state(x_pixel, y_pixel);

            switch (cell_bitmask) {

                case cell_pacman:
                    next_draw = pacman_array[pacman_right_closed];
                    break;

                case cell_ghost:

                    if (ghost_counter == 1) next_draw = inky_array[inky_right_eye];
                    if (ghost_counter == 2) next_draw = blinky_array[blinky_right_eye];
                    if (ghost_counter == 3) next_draw = pinky_array[pinky_right_eye];
                    if (ghost_counter == 4) next_draw = clyde_array[clyde_right_eye];

                    if (ghost_counter < 1 || ghost_counter > 4) {
                        
                        printf("Trying to draw another ghost when all ghosts have been drawn.\n");
                        printf("Grid deleted from memory, draw has been aborted.\n");
                        destroy_grid();

                        //Grid failed to draw
                        return false;
                    }

                    ++ghost_counter;
                    break;
                
                case cell_blank:

                    next_draw = blank_array;
                    break;

                case cell_pellet:
                    next_draw = pickups_array[pickups_pellet];
                    break;

                case cell_cherry:
                    next_draw = pickups_array[pickups_cherry];
                    break;

                case cell_power_up:
                    next_draw = pickups_array[pickups_powerup];
                    break;

                case cell_wall:
                    next_draw = wall_type_pair[current_wall_pair];
                    --walls_left_to_print;

                    if (walls_left_to_print == 0) {

                        ++current_wall_pair;
                        walls_left_to_print = wall_count_pair[current_wall_pair];
                    }                    
                    
                    break;

                case cell_gate:
                    next_draw = wall_array[wall_gate];
                    break;

                default:
                    printf("Trying to draw unknown cell type.\n");
                    printf("Grid deleted from memory, draw has been aborted.\n");
                    destroy_grid();

                    //Grid failed to draw
                    return false;
            }
            //Drawing to the screen
            putImage(x_pixel, y_pixel, 8,8, next_draw, 0,0);
        }

    }

    //Grid drawn properly
    return true;
}