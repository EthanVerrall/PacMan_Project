#include "../include/frontend&drawing/draw_manager.h"
#include "../include/serial.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

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

    //direction just defines which way we are moving
    //a simple arbitrary value should be fine for this
    //0 = RIGHT, 1 = DOWN, 2 = LEFT, 3 = UP

    switch (entity) {

        case entity_type_blinky: 
            if (direction == RIGHT) return blinky_array[blinky_right_eye];
            if (direction == DOWN) return blinky_array[blinky_bottom_eye];
            if (direction == LEFT) return blinky_array[blinky_left_eye];
            if (direction == UP) return blinky_array[blinky_top_eye];

            eputs("Matching texture for blinky not found. NULL returned.\r\n");
            return NULL;

        case entity_type_clyde: 
            if (direction == RIGHT) return clyde_array[clyde_right_eye];
            if (direction == DOWN) return clyde_array[clyde_bottom_eye];
            if (direction == LEFT) return clyde_array[clyde_left_eye];
            if (direction == UP) return clyde_array[clyde_top_eye];

            eputs("Matching texture for clyde not found. NULL returned.\r\n");
            return NULL;

        case entity_type_inky:
            if (direction == RIGHT) return inky_array[inky_right_eye];
            if (direction == DOWN) return inky_array[inky_bottom_eye];
            if (direction == LEFT) return inky_array[inky_left_eye];
            if (direction == UP) return inky_array[inky_top_eye];

            eputs("Matching texture for inky not found. NULL returned.\r\n");
            return NULL;

        case entity_type_pinky:
            if (direction == RIGHT) return pinky_array[pinky_right_eye];
            if (direction == DOWN) return pinky_array[pinky_bottom_eye];
            if (direction == LEFT) return pinky_array[pinky_left_eye];
            if (direction == UP) return pinky_array[pinky_top_eye];

            eputs("Matching texture for pinky not found. NULL returned.\r\n");
            return NULL;

        case entity_type_pacman: 

            //Why do we have only two frames for this guy lol XD -- surely we add more????

            //Pacmans mouth is open
            if (direction == RIGHT && is_mouth_open) {

                is_mouth_open = false;
                return pacman_array[pacman_right_open];
            }

            if (direction == DOWN && is_mouth_open) {

                is_mouth_open = false;
                return pacman_array[pacman_bottom_open];
            }

            if (direction == LEFT && is_mouth_open) {

                is_mouth_open = false;
                return pacman_array[pacman_left_open];
            }

            if (direction == UP && is_mouth_open) {

                is_mouth_open = false;
                return pacman_array[pacman_top_open];
            }

            //Pacmans mouth is closed
            if (direction == RIGHT && (!is_mouth_open)) {

                is_mouth_open = true;
                return pacman_array[pacman_right_closed];
            }

            if (direction == DOWN && (!is_mouth_open)) {

                is_mouth_open = true;
                return pacman_array[pacman_bottom_closed];
            }

            if (direction == LEFT && (!is_mouth_open)) {

                is_mouth_open = true;
                return pacman_array[pacman_left_closed];
            }

            if (direction == UP && (!is_mouth_open)) {

                is_mouth_open = true;
                return pacman_array[pacman_top_closed];
            }

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
        
        cell_bitmask = 0;
    }
    
    switch  (cell_bitmask) {

        case cell_blank: return blank_array;

        case cell_pellet: return pickups_array[pickups_pellet];

        case cell_power_up: return pickups_array[pickups_powerup];

        case cell_cherry: return pickups_array[pickups_cherry];
        
        case cell_gate: return wall_array[wall_gate];

        default:
        eputs("point_at_static_texture() was not passed a valid enum entity_type, function aborted, NULL returned.\r\n");
        return NULL;
    }
}

//--------------------------------------------------------------
//Helper functionS -- must be declared before void move_entity() -- end
//--------------------------------------------------------------

void move_entity(const Point* const point_array[10], const enum entity_type entity_array[5] ) {

    //Enusring we don't derference a NULL POINTER
    for (uint8_t i = 0; i < 10; ++i) {

        if (!point_array[i]) {

            eputs("Points passed to move_entity function are invalid or NULL. Function aborted!\r\n");
            return;
        }
    }

    //Enusring we don't have an invalid entity
    for (uint8_t i = 0; i < 5; ++i) {

        if (!entity_array[i]) {

            eputs("Points passed to move_entity function are invalid or NULL. Function aborted!\r\n");
            return;
        } 
    }

    //Each entities starting x pixel
    uint8_t x_original_pixel_array[5];

    //Each entities starting y pixel
    uint8_t y_original_pixel_array[5];

    //Each targets starting x pixel
    uint8_t x_target_pixel_array[5];

    //Each targets starting y pixel
    uint8_t y_target_pixel_array[5];

    //Textures for our entities that we are moving
    uint16_t* entity_textures_array[5];

    //Textures for our static tiles we will restore
    uint16_t* static_tiles_array[5];

    //Velocity for x_pixels
    int8_t dx[5];

    //Velocity for x_pixels
    int8_t dy[5];
    
    
    //Pixel conversion is done here
    //Direction calculated here
    //Textures are assigned here 
    for (uint8_t i = 0; i < 5; ++i) {

        x_original_pixel_array[i] = get_y_point_coord(point_array[i * 2]) * 8;
        y_original_pixel_array[i] = get_x_point_coord(point_array[i * 2]) * 8;

        x_target_pixel_array[i]   = get_y_point_coord(point_array[(i * 2) + 1]) * 8;
        y_target_pixel_array[i]   = get_x_point_coord(point_array[(i * 2) + 1]) * 8;

        //Target - Original
        dx[i] = x_target_pixel_array[i] - x_original_pixel_array[i];
        dy[i] = y_target_pixel_array[i] - y_original_pixel_array[i];

        //Moves RIGHT
        if (dx[i] == 8 && dy[i] == 0) {

            entity_textures_array[i] = point_at_entity_texture(RIGHT, entity_array[i]);
        }
        //Moves DOWN
        else if (dx[i] == 0 && dy[i] == 8) {

            entity_textures_array[i] = point_at_entity_texture(DOWN, entity_array[i]);
        }
        //Moves LEFT
        else if (dx[i] == -8 && dy[i] == 0) {

            entity_textures_array[i] = point_at_entity_texture(LEFT, entity_array[i]);
        }
        //Moves UP
        else if (dx[i] == 0 && dy[i] == -8) {

            entity_textures_array[i] = point_at_entity_texture(UP, entity_array[i]);
        }
        else 
        {
            eputs("Unexpected dx and dy value function move_entity() aborted.\r\n");
            return;
        }
        static_tiles_array[i] = point_at_static_texture(x_original_pixel_array[i], y_original_pixel_array[i], entity_array[i]);
    }


    for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
         current_frame <= 8; 
         ++current_frame, ++forward_offset, --backward_offset)  
    {

        for (uint8_t i = 0; i < 5; ++i) {

            //Moves RIGHT
            if (dx[i] == 8 && dy[i] == 0) {

                //Redrawing the tile we are leaving
                putColumn(x_original_pixel_array[i] + forward_offset, y_original_pixel_array[i], static_tiles_array[i], forward_offset);
                //Drawing over the tiles in the direction we are moving
                putImage(x_original_pixel_array[i] + current_frame, y_original_pixel_array[i], 8,8, entity_textures_array[i], 0,0);
            }

            //Moves DOWN
            else if (dx[i] == 0 && dy[i] == 8) {

                //Redrawing the tile we are leaving
                putRow(x_original_pixel_array[i], y_original_pixel_array[i] + forward_offset, static_tiles_array[i], forward_offset);
                //Drawing over the tiles in the direction we are moving
                putImage(x_original_pixel_array[i], y_original_pixel_array[i] + current_frame, 8,8, entity_textures_array[i], 0,0);
            }

            //Moves LEFT
            else if (dx[i] == -8 && dy[i] == 0) {

                //Redrawing the tile we are leaving
                putColumn(x_original_pixel_array[i] + backward_offset, y_original_pixel_array[i], static_tiles_array[i], backward_offset);
                //Drawing over the tiles in the direction we are moving
                putImage(x_original_pixel_array[i] - current_frame, y_original_pixel_array[i], 8,8, entity_textures_array[i], 0,0);
            }

            //Moves UP
            else if (dx[i] == 0 && dy[i] == -8) {

                //putImage(x_original_pixel, y_original_pixel + j, 8,i, static_tile, 0,1);
                putRow(x_original_pixel_array[i], y_original_pixel_array[i] + backward_offset, static_tiles_array[i], backward_offset);
                //Drawing over the tiles in the direction we are moving
                putImage(x_original_pixel_array[i], y_original_pixel_array[i] - current_frame, 8,8, entity_textures_array[i], 0,0);
            }   
            //Error case
            else {
                eputs("Error with movement, function move_entity() did not work.\r\n");
            }   
        }
        //End of frame, needs to delay now
        delay(100);
    }
}