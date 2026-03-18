#include "../include/frontend&drawing/draw_manager.h"
#include "../include/serial.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define right 0
#define down 1
#define left 2
#define up 3

static bool is_mouth_open = false;

bool draw_starting_grid () {
    /*
        The below two arrays are used in parallel to define the wall types 
        and how many times they must print.
    */

    //Ensuring pacmans mouth is closed at game start
    is_mouth_open = false;

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
            uint8_t cell_bitmask = get_grid_state(y_pixel / 8, x_pixel / 8);

            switch (cell_bitmask) {

                case cell_blank|cell_pacman:
                    next_draw = pacman_array[pacman_right_closed];
                    break;

                case cell_blank|cell_ghost:

                    if (ghost_counter == 1) next_draw = inky_array[inky_right_eye];
                    if (ghost_counter == 2) next_draw = blinky_array[blinky_right_eye];
                    if (ghost_counter == 3) next_draw = pinky_array[pinky_right_eye];
                    if (ghost_counter == 4) next_draw = clyde_array[clyde_right_eye];

                    if (ghost_counter < 1 || ghost_counter > 4) {
                        
                        eputs("Trying to draw another ghost when all ghosts have been drawn.\r\n");
                        eputs("Grid deleted from memory, draw has been aborted.\r\n");
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
                    eputs("Trying to draw unknown cell type.\r\n");
                    eputs("Grid deleted from memory, draw has been aborted.\r\n");
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

//--------------------------------------------------------------
//Helper functionS -- must be declared before void move_entity() -- start
//--------------------------------------------------------------

//Function updates our uint_16 pointer to point at the texture we are drawing
const uint16_t* point_at_entity_texture(uint8_t direction,enum entity_type entity) {

    //direction just defines whic way we are moving
    //a simple arbitrary value should be fine for this
    //0 = right, 1 = down, 2 = left, 3 = up

    switch (entity) {

        case entity_type_blinky: 
            if (right) return blinky_array[blinky_right_eye];
            if (down) return blinky_array[blinky_bottom_eye];
            if (left) return blinky_array[blinky_left_eye];
            if (up) return blinky_array[blinky_top_eye];

            eputs("Matching texture for blinky not found. NULL returned.\r\n");
            return NULL;

        case entity_type_clyde: 
            if (right) return clyde_array[clyde_right_eye];
            if (down) return clyde_array[clyde_bottom_eye];
            if (left) return clyde_array[clyde_left_eye];
            if (up) return clyde_array[clyde_top_eye];

            eputs("Matching texture for clyde not found. NULL returned.\r\n");
            return NULL;

        case entity_type_inky:
            if (right) return inky_array[inky_right_eye];
            if (down) return inky_array[inky_bottom_eye];
            if (left) return inky_array[inky_left_eye];
            if (up) return inky_array[inky_top_eye];

            eputs("Matching texture for inky not found. NULL returned.\r\n");
            return NULL;

        case entity_type_pinky:
            if (right) return pinky_array[pinky_right_eye];
            if (down) return pinky_array[pinky_bottom_eye];
            if (left) return pinky_array[pinky_left_eye];
            if (up) return pinky_array[pinky_top_eye];

            eputs("Matching texture for pinky not found. NULL returned.\r\n");
            return NULL;

        case entity_type_pacman: 

            //Why do we have only two frames for this guy lol XD -- surely we add more????

            //Pacmans mouth is open
            if (right && is_mouth_open) return pacman_array[pacman_right_open];
            if (down && is_mouth_open) return pacman_array[pacman_bottom_open];
            if (left && is_mouth_open) return pacman_array[pacman_left_open];
            if (up && is_mouth_open) return pacman_array[pacman_top_open];
            
            //Pacmans mouth is closed
            if (right && is_mouth_open) return pacman_array[pacman_right_closed];
            if (down && is_mouth_open) return pacman_array[pacman_bottom_closed];
            if (left && is_mouth_open) return pacman_array[pacman_left_closed];
            if (up && is_mouth_open) return pacman_array[pacman_top_closed];

            eputs("Matching texture for pacman not found. NULL returned.\r\n");
            return NULL;

        default: eputs("point_at_texture() was not passed a valid enum entity_type, function aborted, NULL returned.\r\n");
        return NULL;
    }
}

const uint16_t* point_at_static_texture(uint8_t x_pixel, uint8_t y_pixel, const enum entity_type entity) {

    //Changing pixels to correctly reflect grid indexing
    //Function assumes we are working with perfect eights, should be called before any moving to a new tile has happened
    x_pixel /= 8;
    y_pixel /= 8;

    //Getting bitmask from grid cell and extracting the dynamic entity from it
    //I only need the static_tile types for this function. Must remove pacman and ghosts from my bitmask
    uint8_t cell_bitmask = 0;
    
    if (has_grid_state(y_pixel,x_pixel,cell_pacman)) {

        cell_bitmask = ~cell_pacman & get_grid_state(y_pixel,x_pixel);
    } 
    else if (has_grid_state(y_pixel,x_pixel,cell_ghost)) {

        cell_bitmask = ~cell_ghost & get_grid_state(y_pixel,x_pixel);
    }
    else {
        
        uint8_t cell_bitmask = 0;
    }
    
    switch  (cell_bitmask) {

        case cell_blank: return blank_array;

        case cell_pellet: return pickups_array[pickups_pellet];

        case cell_power_up: return pickups_array[pickups_powerup];

        case cell_cherry: return pickups_array[pickups_cherry];
        
        default:
        eputs("point_at_static_texture() was not passed a valid enum entity_type, function aborted, NULL returned.\r\n");
        return NULL;
    }
}

//--------------------------------------------------------------
//Helper functionS -- must be declared before void move_entity() -- end
//--------------------------------------------------------------


void move_entity(Point* const current_point, Point* const target_point, const enum entity_type entity) {

    if (!current_point || !target_point) {

        eputs("Points passed to move_entity function are invalid or NULL. Function aborted!\r\n");
        return;
    } 
    
    uint8_t x_current_pixel = get_y_point_coord(current_point) * 8;
    uint8_t y_current_pixel = get_x_point_coord(current_point) * 8;
    uint8_t x_target_pixel = get_y_point_coord(target_point) * 8;
    uint8_t y_target_pixel = get_x_point_coord(target_point) * 8;
    //const uint8_t origin_x_pixel = x_current_pixel;
    //const uint8_t origin_y_pixel = y_current_pixel;

    //Calculate direction for animation purposes
    int8_t dx = (int8_t) x_target_pixel - (int8_t) x_current_pixel;
    int8_t dy = (int8_t) y_target_pixel - (int8_t) y_current_pixel;

    //Moves right
    if (dx == 1 && dy == 0) {
        const uint16_t* moving_entity = point_at_entity_texture(right,entity);
        const uint16_t* static_tile = point_at_static_texture(x_current_pixel, y_current_pixel, entity);
        for (uint8_t i = 1; i <= 8; ++i) {

            
        }
    }
    //Moves down
    else if (dx == 0 && dy == 1)
    {
        const uint16_t* moving_entity = point_at_entity_texture(down,entity);
        const uint16_t* static_tile = point_at_static_texture(x_current_pixel, y_current_pixel, entity);
        for (uint8_t i = 1; i <= 8; ++i) {

            
        }

    }
    //Moves left
    else if (dx == -1 && dy == 0) 
    {
        const uint16_t* moving_entity = point_at_entity_texture(left,entity);
        const uint16_t* static_tile = point_at_static_texture(x_current_pixel, y_current_pixel, entity);
        for (uint8_t i = 1; i <= 8; ++i) {

            
        }

    }
    //Moves up
    else if (dx == 0 && dy == -1) 
    {
        const uint16_t* moving_entity = point_at_entity_texture(up,entity);
        const uint16_t* static_tile = point_at_static_texture(x_current_pixel, y_current_pixel, entity);
        for (uint8_t i = 1; i <= 8; ++i) {

            
        }

    }
    else {
        //It's cooked if I get here tbh
    }
}