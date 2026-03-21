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



//--------------------------------------------------------------
//Helper functions -- must be declared before void move_entity() -- start
//--------------------------------------------------------------

const uint16_t* point_at_entity_texture(uint8_t direction, const enum entity_type entity) {

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

const uint16_t* point_at_static_texture(uint8_t x_pixel, uint8_t y_pixel) {

    //Changing pixels to correctly reflect grid indexing
    //Function assumes we are working with perfect eights, should be called before any moving to a new tile has happened
    x_pixel /= 8;
    y_pixel /= 8;

    if (has_grid_state(y_pixel,x_pixel,cell_blank))  { return blank_array; } 

    else if (has_grid_state(y_pixel,x_pixel,cell_pellet)) { return pickups_array[pickups_pellet]; }

    else if (has_grid_state(y_pixel,x_pixel,cell_power_up)) { return pickups_array[pickups_powerup]; }

    else if (has_grid_state(y_pixel,x_pixel,cell_cherry)) { return pickups_array[pickups_cherry]; }

    else if (has_grid_state(y_pixel,x_pixel,cell_gate)) { return wall_array[wall_gate]; }

    else 
    { 
        eputs("point_at_static_texture() was unable to find the correct matching static bitmap array.\r\n");
        return NULL;
    }
}

//---------------------------------MENUS------------------------------------------

void redraw_entire_grid () {
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
    uint8_t current_wall_pair = 0;
    uint8_t walls_left_to_print = wall_count_pair[current_wall_pair];

    //Clearing the first row of 8 pixels heigh, needs to be redrawn as black to clear the pacman logo after image
    //from the home page
    for (uint8_t y_pixel = 0; y_pixel < 8; ++y_pixel) {

        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; ++x_pixel) {
            putPixel(x_pixel,y_pixel,0);
        }

    }

    //Loops through the entire grid and prints all tiles and upscaled 8*8 pixels across the screen
    //accounting for the intial offset in height from pixel 0,0
    for (uint8_t y_pixel = 0 + HEIGHT_OFFSET; y_pixel < SCREEN_HEIGHT; y_pixel += 8) {

        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; x_pixel += 8) {

            /*
                HOW THIS WORKS by Ethan Verrall :)

                First we test if the current pixel contains a moving entity, if true we set our next_draw pointer
                to the matching texture array and then draw the tile on the screen.

                OTHERWISE:

                We get the bitmask for the current grid cell/index that relates to the screens pixel (x,y),
                We then use the switch to check which state it is at this grid cell/index,
                We then set our pointer to the appropriate texture array,
                Finally was pass our pointer to the putImage function to draw on the screen at pixel (x,y)
            */

            const uint16_t* next_draw = NULL;
            
            if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_pacman)) {
                next_draw = pacman_array[pacman_right_closed];
            } 
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_blinky)) {
                next_draw = blinky_array[blinky_right_eye];
            }
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_inky)) {
                next_draw = inky_array[inky_right_eye];
            }
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_pinky)) {
                next_draw = pinky_array[pinky_right_eye];
            }
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_clyde)) {
                next_draw = clyde_array[clyde_right_eye];
            }
           else {
                const uint16_t cell_bitmask = get_grid_state(y_pixel / 8, x_pixel / 8);

                switch (cell_bitmask) {

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
                        //Grid failed to draw
                        eputs("Trying to draw unknown cell type.\r\n");
                        eputs("Grid deleted from memory, draw has been aborted.\r\n");
                        destroy_grid();
                    return;
                }
            }
            //Drawing to the screen
            putImage(x_pixel, y_pixel, 8,8, next_draw, 0,0);
        }
    }
    //Grid drawn properly
}

void redraw_white_text(int8_t cursor_position, enum menu_page active_menu) {

    if (active_menu == menu_page_home) {

        switch (cursor_position) {

            case 0:
            printTextX2("Play Game",6,70,0xFFFF,0);
            break;

            case 1:
            printTextX2("Scoreboard",6,100,0xFFFF,0);
            break;

            case 2:
            printTextX2("Options",6,130,0xFFFF,0);
            break;
        }
    }
}

void draw_home_page() {

    putImage(7,5,114,32,main_menu_array,0,0);

    printTextX2("Play Game",6,70,0xFFFF,0);

    printTextX2("Scoreboard",6,100,0xFFFF,0);

    printTextX2("Options",6,130,0xFFFF,0);
}

void flicker_text() {

    const uint16_t YELLOW = 57095 ;
	const uint16_t BLUE = 35315;

    static uint8_t flicker_switch = 0;

    if (get_active_menu_page() == menu_page_home) {

        switch (get_cursor_position()) {
        
        case 0:
            //Flicker is off
            if (!flicker_switch) {

                flicker_switch = 1;
                printTextX2("Play Game",6,70,YELLOW,0);
            } 
            //Flicker on
            else {

                flicker_switch = 0;
                printTextX2("Play Game",6,70,BLUE,0);
            }
        break;
        
        case 1:
            //Flicker is off
            if (!flicker_switch) {

                flicker_switch = 1;
                printTextX2("Scoreboard",6,100,YELLOW,0);
            } 
            //Flicker on
            else {

                flicker_switch = 0;
                printTextX2("Scoreboard",6,100,BLUE,0);
            }
        break;

        case 2:
            //Flicker is off
            if (!flicker_switch) {

                flicker_switch = 1;
                printTextX2("Options",6,130,YELLOW,0);
            } 
            //Flicker on
            else {

                flicker_switch = 0;
                printTextX2("Options",6,130,BLUE,0);
            }
        break;
        
        default:
            eputs("Unexpected cursor postion when attempting to flicker text on the home page.\r\n");
            printDecimal(get_cursor_position());
            eputs("\r\n");
            break;
        }  
    }
    else  {  

        eputs("Trying to flicker text for a menu_page that can't flicker any text.\r\n");
        return;
    }
    delay(100);
} 

//---------------------------------MENUS------------------------------------------

//--------------------------------------------------------------
//Helper functions -- must be declared before void move_entity() -- end
//--------------------------------------------------------------

void move_entities(const Point* const point_array[], const enum entity_type entity_array[], const uint8_t num_entites_to_animate) {

    //Enusring we don't derference a NULL POINTER
    for (uint8_t i = 0; i < (num_entites_to_animate * 2); ++i) {

        if (!point_array[i]) {

            eputs("Points passed to move_entities function are invalid or NULL. Function aborted!\r\n");
            return;
        }
    }

    //Ensuring all enums are valid entity types
    for (uint8_t i = 0; i < num_entites_to_animate; ++i) {

        switch (entity_array[i]) {
            
            case entity_type_blinky:
            case entity_type_clyde:
            case entity_type_inky:
            case entity_type_pinky:
            case entity_type_pacman:
                //Intentional fallthrough
                //Do nothing all is as expected
                break;

            default:
                eputs("Entities in entity array are an invalid type, function move_entities aborted!\r\n");
                return;
        }
    }

    //Each entities starting x pixel
    uint8_t x_old_pixel_array[num_entites_to_animate];

    //Each entities starting y pixel
    uint8_t y_old_pixel_array[num_entites_to_animate];

    //Each targets starting x pixel
    uint8_t x_new_pixel_array[num_entites_to_animate];

    //Each targets starting y pixel
    uint8_t y_new_pixel_array[num_entites_to_animate];

    //Textures for our entities that we are moving
    uint16_t* entity_textures_array[num_entites_to_animate];

    //Textures for our static tiles we will restore
    uint16_t* static_tiles_array[num_entites_to_animate];

    //Velocity for x_pixels
    int8_t dx[num_entites_to_animate];

    //Velocity for x_pixels
    int8_t dy[num_entites_to_animate];
    
    //Pixel conversion is done here
    //Direction calculated here
    //Textures are assigned here 
    for (uint8_t i = 0; i < num_entites_to_animate; ++i) {

        x_old_pixel_array[i] = get_y_point_coord(point_array[i * 2]) * 8;
        y_old_pixel_array[i] = get_x_point_coord(point_array[i * 2]) * 8;

        x_new_pixel_array[i] = get_y_point_coord(point_array[(i * 2) + 1]) * 8;
        y_new_pixel_array[i] = get_x_point_coord(point_array[(i * 2) + 1]) * 8;

        //Target - Original
        dx[i] = x_new_pixel_array[i] - x_old_pixel_array[i];
        dy[i] = y_new_pixel_array[i] - y_old_pixel_array[i];

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
        //Wrapping from left to right side of the screen
        else if (dx[i] == 120 && dy[i] == 0) {

            entity_textures_array[i] = point_at_entity_texture(LEFT, entity_array[i]);
        }
        //Wrapping from right to left side of the screen    
        else if (dx[i] == -120 && dy[i] == 0) {

            entity_textures_array[i] = point_at_entity_texture(RIGHT, entity_array[i]);
        }
        else 
        {
            eputs("Unexpected dx and dy value function move_entity() aborted.\r\n");
            return;
        }
        static_tiles_array[i] = point_at_static_texture(x_old_pixel_array[i], y_old_pixel_array[i]);
    }


    for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
         current_frame <= 8; 
         ++current_frame, ++forward_offset, --backward_offset)  
    {

        //Restoring tiles
        for (uint8_t i = 0; i < num_entites_to_animate; ++i) {

            //Moves RIGHT
            if (dx[i] == 8 && dy[i] == 0) {

                //Redrawing the tile we are leaving
                putColumn(x_old_pixel_array[i] + forward_offset, y_old_pixel_array[i], static_tiles_array[i], forward_offset);
            }
            
            //Moves DOWN
            else if (dx[i] == 0 && dy[i] == 8) {

                //Redrawing the tile we are leaving
                putRow(x_old_pixel_array[i], y_old_pixel_array[i] + forward_offset, static_tiles_array[i], forward_offset);
            }

            //Moves LEFT
            else if (dx[i] == -8 && dy[i] == 0) {

                //Redrawing the tile we are leaving
                putColumn(x_old_pixel_array[i] + backward_offset, y_old_pixel_array[i], static_tiles_array[i], backward_offset);
            }

            //Moves UP
            else if (dx[i] == 0 && dy[i] == -8) {

                //Redrawing the tile we are leaving
                putRow(x_old_pixel_array[i], y_old_pixel_array[i] + backward_offset, static_tiles_array[i], backward_offset);
            }

            //Wrapping from left to right side of the screen
            else if (dx[i] == 120 && dy[i] == 0) {

                //Making entities appear like they are sliding off the screen
                for (uint8_t j = 0; j < (8 - current_frame); ++j) {   
                    putColumn(x_old_pixel_array[i] + j, y_old_pixel_array[i], entity_textures_array[i], (current_frame - 1) + j);
                }
                
                //Redrawing the tile we are leaving
                putColumn(x_old_pixel_array[i] + backward_offset, y_old_pixel_array[i], static_tiles_array[i], backward_offset);
            }

            //Wrapping from right to left side of the screen    
            else if (dx[i] == -120 && dy[i] == 0) {

                //Making entities appear like they are sliding off the screen
                for (uint8_t j = 7; j > (current_frame - 1); --j) {   
                    putColumn(x_old_pixel_array[i] + j, y_old_pixel_array[i], entity_textures_array[i], j - (current_frame - 1 ));
                }
                
                //Redrawing the tile we are leaving
                putColumn(x_old_pixel_array[i] + forward_offset, y_old_pixel_array[i], static_tiles_array[i], forward_offset);
            }

            //Error case
            else {
                eputs("Error with movement, function move_entity() did not work.\r\n");
            }   
        }

        //Drawing ghosts and pacman
        for (uint8_t i = 0; i < num_entites_to_animate; ++i) {
            
            //Moves RIGHT
            if (dx[i] == 8 && dy[i] == 0) {

                //Drawing over the tiles in the direction we are moving
                putImage(x_old_pixel_array[i] + current_frame, y_old_pixel_array[i], 8,8, entity_textures_array[i], 0,0);
            }
            
            //Moves DOWN
            else if (dx[i] == 0 && dy[i] == 8) {

                //Drawing over the tiles in the direction we are moving
                putImage(x_old_pixel_array[i], y_old_pixel_array[i] + current_frame, 8,8, entity_textures_array[i], 0,0);
            }

            //Moves LEFT
            else if (dx[i] == -8 && dy[i] == 0) {

                //Drawing over the tiles in the direction we are moving
                putImage(x_old_pixel_array[i] - current_frame, y_old_pixel_array[i], 8,8, entity_textures_array[i], 0,0);
            }

            //Moves UP
            else if (dx[i] == 0 && dy[i] == -8) {

                //Drawing over the tiles in the direction we are moving
                putImage(x_old_pixel_array[i], y_old_pixel_array[i] - current_frame, 8,8, entity_textures_array[i], 0,0);
            }
            //Wrapping from left to right side of the screen
            else if (dx[i] == 120 && dy[i] == 0) {
                
                //Drawing over the tiles in the direction we are moving
                //Makes our entity appear piece like he is coming onto the screen
                for (uint8_t j = 0; j < current_frame; ++j) {

                    putColumn(x_new_pixel_array[i] + backward_offset + j, y_new_pixel_array[i], entity_textures_array[i], j);
                }
            }

            //Wrapping from right to left side of the screen    
            else if (dx[i] == -120 && dy[i] == 0) {

                //Drawing over the tiles in the direction we are moving
                //Makes our entity appear piece like he is coming onto the screen
                for (uint8_t j = 0; j < current_frame; ++j) {

                    putColumn(x_new_pixel_array[i] + forward_offset - j, y_new_pixel_array[i], entity_textures_array[i], 7 - j);
                }
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

void draw_current_page() {

    const enum menu_page menu_to_draw = get_active_menu_page();

    switch (menu_to_draw) {

        case menu_page_home:
        draw_home_page();
        break;

        case menu_page_game:
        redraw_entire_grid();
        break;

        default:
        eputs("Function draw_current_page failed to find the corresponding menu/page to draw.\r\n");
        break;
    }
}