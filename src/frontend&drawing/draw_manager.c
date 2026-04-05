#include "../include/frontend&drawing/draw_manager.h"

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
#define WHITE_TEXT 0xFFFF

static bool is_mouth_open = false;

//---------------------------------MENUS------------------------------------------

//This draws the entire grid on the screen based on the states at each grid index
//assure all masks are updated before using this function to draw an up to date grid
void redraw_entire_grid () {
    /*
        The below two arrays are used in parallel to define the wall types 
        and how many times they must print.
    */
    
    //Ensuring pacmans mouth is closed at game start / forcing his mouth closed when we resume game as well
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
    //Score goes here with player name
    const char* user_name = get_user_name();
    printText(user_name,3,0,WHITE_TEXT,0);
    printNumber(get_score(),90,0,WHITE_TEXT,0);
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
                const PacDirection pac_direction = get_pacman_direction();
               
                switch (pac_direction) {
                    case PAC_RIGHT: next_draw = pacman_array[pacman_right_closed];
                    break;

                    case PAC_LEFT: next_draw = pacman_array[pacman_left_closed];
                    break;

                    case PAC_TOP: next_draw = pacman_array[pacman_top_closed];
                    break;

                    case PAC_BOTTOM: next_draw = pacman_array[pacman_bottom_closed];
                    break;

                    case PAC_NONE: next_draw = pacman_array[pacman_right_closed];
                    break;
                }
            } 
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_blinky)) {
                if (get_blinky_mode() == fright) next_draw = fright_ghost_array;
                else next_draw = blinky_array[blinky_right_eye];
            }
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_inky)) {
                if (get_inky_mode() == fright) next_draw = fright_ghost_array;
                else next_draw = inky_array[inky_right_eye];
            }
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_pinky)) {
                if (get_pinky_mode() == fright) next_draw = fright_ghost_array;
                else next_draw = pinky_array[pinky_right_eye];
            }
            else if (has_grid_state(y_pixel / 8, x_pixel / 8, cell_clyde)) {
                if (get_clyde_mode() == fright) next_draw = fright_ghost_array;
                else next_draw = clyde_array[clyde_right_eye];
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

//Resets text we have moved away from when in cursor menu mode as white,
//we reset the text as white since it would be yellow or blue if we moved off the text after it finished
//flickering, it makes things look fun and like you are operating a real arcade machine
void reset_text(int8_t cursor_position, const enum menu_page active_menu) {

    if (active_menu == menu_page_home) {

        switch (cursor_position) {

            case 0:
            printTextX2("Play Game",6,70,WHITE_TEXT,0);
            break;

            case 1:
            printTextX2("Scoreboard",6,100,WHITE_TEXT,0);
            break;

            case 2:
            printTextX2("Options",6,130,WHITE_TEXT,0);
            break;
        }
    }
   
    if (active_menu == menu_page_pause) {

        switch (cursor_position) {

            case 0:
                printText("Resume Game",20,60,WHITE_TEXT,0);
            break;

            case 1:
                printText("Restart Game",20,90,WHITE_TEXT,0);
            break;

            case 2:
                printText("Exit Game",20,120,WHITE_TEXT,0);
            break;
        }
    }

    if (active_menu == menu_page_options) {

        for (uint8_t i = 0; i < SCREEN_WIDTH; ++i) {
            for (uint8_t j = 40; j < 48; ++j) {
                putPixel(i,j,0);
            }
        }
    }
}

//Describes how the home page is and should be drawn
void draw_home_page() {
    
    //Clear the screen to black
    for (uint8_t y_pixel = 0; y_pixel < SCREEN_HEIGHT; ++ y_pixel) {
        
        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; ++x_pixel) {

            putPixel(x_pixel,y_pixel,0);
        }
    }

    //Uncompress the main_menu_logo using my switch case map function and pass the the uint16_t colour to draw
    //Based off the huffman compression algorithm
    #define MAIN_MENU_ROWS 32
    #define MAIN_MENU_COLS 114

    for (uint8_t i = 0; i < MAIN_MENU_ROWS; ++i) {
        
        for (uint8_t j = 0; j < MAIN_MENU_COLS; ++j) {

            const uint16_t nex_colour = find_main_menu_colour(main_menu_array[(i * MAIN_MENU_COLS) + j]);
            putPixel(7+j, 5+i, nex_colour);
        }
    }

    printTextX2("Play Game",6,70,WHITE_TEXT,0);

    printTextX2("Scoreboard",6,100,WHITE_TEXT,0);

    printTextX2("Options",6,130,WHITE_TEXT,0);
}

//Describes how the pause page is and should be drawn
void draw_pause_menu() {

    //Clear the screen to black
    for (uint8_t y_pixel = 0; y_pixel < SCREEN_HEIGHT; ++ y_pixel) {
        
        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; ++x_pixel) {

            putPixel(x_pixel,y_pixel,0);
        }
    }

    printTextX2("Paused", 30,20,WHITE_TEXT,0);

    printText("Resume Game",20,60,WHITE_TEXT,0);

    printText("Restart Game",20,90,WHITE_TEXT,0);

    printText("Exit Game",20,120,WHITE_TEXT,0);

}

//Describes how the options page is and should be drawn
void draw_options_menu() {

    //Clear the screen to black
    for (uint8_t y_pixel = 0; y_pixel < SCREEN_HEIGHT; ++ y_pixel) {
        
        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; ++x_pixel) {

            putPixel(x_pixel,y_pixel,0);
        }
    }

    printTextX2("Options",7,5,WHITE_TEXT,0);

    if (get_active_menu_page()) {

        printText("Music on",7,40,WHITE_TEXT,0);
    }
    else {
        printText("Music off",7,40,WHITE_TEXT,0);
    }

    printText("Right = change",7,80,WHITE_TEXT,0);
    printText("Left = home page",7,100,WHITE_TEXT,0);
    
}

//Describes how the name_request page is and should be drawn
void draw_name_request_menu() {

    //Clear the screen to black
    for (uint8_t y_pixel = 0; y_pixel < SCREEN_HEIGHT; ++ y_pixel) {
        
        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; ++x_pixel) {

            putPixel(x_pixel,y_pixel,0);
        }
    }

    printText("Use the serial",7,60,WHITE_TEXT,0);
    printText("monitor to enter",7,68,WHITE_TEXT,0);
    printText("your name?",7,76,WHITE_TEXT,0);
}

//Describes how the scoreboard page is and should be drawn
void draw_scoreboard_menu() {
    
    //Clear the screen to black
    for (uint8_t y_pixel = 0; y_pixel < SCREEN_HEIGHT; ++ y_pixel) {
        
        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; ++x_pixel) {

            putPixel(x_pixel,y_pixel,0);
        }
    }
    
    printTextX2("Scoreboard:",7,5,WHITE_TEXT,0);

    //Fetch the top three scores and draw them, if no score is found we mention "No score yet"
    //otherwise we draw the persons name and their score
    for (uint8_t i = 0; i < 3; ++i) {

        const char* next_name = get_scoreboard_names(i);
        const uint16_t next_score = get_scoreboard_scores(i);

        if (*next_name == '\0' || next_score == 0) {
            printText("No score yet",7,40 + (30*i),WHITE_TEXT,0);
        }
        else 
        {
            printText(next_name,7,40 + (30*i),WHITE_TEXT,0);
            printNumber(next_score,90,40 + (30*i),WHITE_TEXT,0);
        }
    }

    printText("Left = home page",7,144,WHITE_TEXT,0);
}

//This function looks at which menu page we are on, where the cursor is currently positioned
//and flickers that text as yellow and white, gives a classic arcade style feeling
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
            //Flicker text failed, simply abort the function
            break;
        }  
    }

    else if (get_active_menu_page() == menu_page_pause) {

        switch (get_cursor_position()) {
        
        case 0:
            //Flicker is off
            if (!flicker_switch) {

                flicker_switch = 1;
                printText("Resume Game",20,60,YELLOW,0);
            } 
            //Flicker on
            else {

                flicker_switch = 0;
                printText("Resume Game",20,60,BLUE,0);
            }
            break;
        
        case 1:
            //Flicker is off
            if (!flicker_switch) {

                flicker_switch = 1;
                printText("Restart Game",20,90,YELLOW,0);
            } 
            //Flicker on
            else {

                flicker_switch = 0;
                printText("Restart Game",20,90,BLUE,0);
            }
            break;

        case 2:
            //Flicker is off
            if (!flicker_switch) {

                flicker_switch = 1;
                printText("Exit Game",20,120,YELLOW,0);
            } 
            //Flicker on
            else {

                flicker_switch = 0;
                printText("Exit Game",20,120,BLUE,0);
            }
            break;
        
        default:
            //Flicker text failed, simply abort the function
            break;
        }  
    }

    else if (get_active_menu_page() == menu_page_options) {

        if (get_music_setting()) {

            if (!flicker_switch) {

                flicker_switch = 1;
                printText("Music on",7,40,YELLOW,0);
            }
            else 
            {   
                flicker_switch = 0;
                printText("Music on",7,40,BLUE,0);
            }
        }
        else 
        {

            if (!flicker_switch) {

                flicker_switch = 1;
                printText("Music off",7,40,YELLOW,0);
            }
            else 
            {      
                flicker_switch = 0;
                printText("Music off",7,40,BLUE,0);
            }
        }
    }

    else if (get_active_menu_page() == menu_page_scoreboard) {

        if (!flicker_switch) {

                flicker_switch = 1;
                printTextX2("Scoreboard:",7,5,YELLOW,0);
            }
            else 
            {      
                flicker_switch = 0;
                printTextX2("Scoreboard:",7,5,BLUE,0);
            }
    }

    else  {  

        //Error - Trying to flicker text for a menu_page that can't flicker any text.
        return;
    }
    delay(100);
} 

//This function looks at which menu is currently active and draws from the matching above type menu description function
void draw_current_page() {

    const enum menu_page menu_to_draw = get_active_menu_page();

    switch (menu_to_draw) {

        case menu_page_home:
        draw_home_page();
        break;

        case menu_page_game:
        redraw_entire_grid();
        break;

        case menu_page_pause:
        draw_pause_menu();
        break;

        case menu_page_options:
        draw_options_menu();
        break;

        case menu_page_name_request:
        draw_name_request_menu();
        break;

        case menu_page_scoreboard:
        draw_scoreboard_menu();
        break;

        default:
        //Failed to draw the current page
        break;
    }
}

//---------------------------------MENUS------------------------------------------



//--------------------------------------------------------------
//Helper functions -- must be declared before void move_entity() -- start
//--------------------------------------------------------------

//Helps find the correct entity texture based on direction
const uint16_t* point_at_entity_texture(uint8_t direction, const enum entity_type entity) {

    //direction just defines which way we are moving
    //a simple arbitrary value should be fine for this
    //0 = RIGHT, 1 = DOWN, 2 = LEFT, 3 = UP

    switch (entity) {

        case entity_type_blinky: 
            if (get_blinky_mode() == fright) return fright_ghost_array;
            if (direction == RIGHT) return blinky_array[blinky_right_eye];
            if (direction == DOWN) return blinky_array[blinky_bottom_eye];
            if (direction == LEFT) return blinky_array[blinky_left_eye];
            if (direction == UP) return blinky_array[blinky_top_eye];

            return NULL;

        case entity_type_clyde: 
            if (get_clyde_mode() == fright) return fright_ghost_array;
            if (direction == RIGHT) return clyde_array[clyde_right_eye];
            if (direction == DOWN) return clyde_array[clyde_bottom_eye];
            if (direction == LEFT) return clyde_array[clyde_left_eye];
            if (direction == UP) return clyde_array[clyde_top_eye];

            return NULL;

        case entity_type_inky:
            if (get_inky_mode() == fright) return fright_ghost_array;
            if (direction == RIGHT) return inky_array[inky_right_eye];
            if (direction == DOWN) return inky_array[inky_bottom_eye];
            if (direction == LEFT) return inky_array[inky_left_eye];
            if (direction == UP) return inky_array[inky_top_eye];

            return NULL;

        case entity_type_pinky:
            if (get_pinky_mode() == fright) return fright_ghost_array;
            if (direction == RIGHT) return pinky_array[pinky_right_eye];
            if (direction == DOWN) return pinky_array[pinky_bottom_eye];
            if (direction == LEFT) return pinky_array[pinky_left_eye];
            if (direction == UP) return pinky_array[pinky_top_eye];

            return NULL;

        case entity_type_pacman: 

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

            return NULL;

        default: 
        return NULL;
    }
}

//Helps find which texture to restore as we leave a tile, 
//uses the grid to figure out the type from the current saved mask
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
        return NULL;
    }
}

//--------------------------------------------------------------
//Helper functions -- must be declared before void move_entity() -- end
//--------------------------------------------------------------



//-------------------------------------------------------------- 
//Dynamic movement / gameplay functions                          -- Start
//--------------------------------------------------------------

void move_entities(const Point point_array[], const enum entity_type entity_array[],
    const uint8_t num_entites_to_animate, bool is_ghost_eaten[]) {

    //Checking that our point contains valid points and is not set to INVALID_POINT
    for (uint8_t i = 0; i < (num_entites_to_animate * 2); ++i) {

        if (!is_point_valid(&point_array[i])) {

            //Abort the function if the check fails
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
                //All is as expected
                break;

            default:
                //Abort the function since this enetity is not accounted for and no texture will be found for it
                //later on in the function
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
    const uint16_t* entity_textures_array[num_entites_to_animate];

    //Textures for our static tiles we will restore
    const uint16_t* static_tiles_array[num_entites_to_animate];

    //Velocity for x_pixels
    int8_t dx[num_entites_to_animate];

    //Velocity for x_pixels
    int8_t dy[num_entites_to_animate];
  
//////////////////////////////////////////////////////////////////////////////////////////////////////    
////Pixel conversion is done here
////Direction calculated here
////Textures are assigned here
////Looking at which ghosts need to be eaten and tracking their state
////////////////////////////////////////////////////////////////////////////////////////////////////// 
  
    for (uint8_t i = 0; i < num_entites_to_animate; ++i) {


        x_old_pixel_array[i] = (point_array[i * 2].y) * 8;
        y_old_pixel_array[i] = (point_array[i * 2].x) * 8;

        x_new_pixel_array[i] = (point_array[(i * 2) + 1]).y * 8;
        y_new_pixel_array[i] = (point_array[(i * 2) + 1]).x * 8;

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

        //Not moving, need to redraw ourselves in the same spot, in the case that something moves away next turn but
        //we are still standing still (OTHERWISE it would seem we just disappeared)
        else if (dx[i] == 0 && dy[i] == 0) 
        {

            if (entity_array[i] != entity_type_pacman) {

                entity_textures_array[i] = point_at_entity_texture(RIGHT, entity_array[i]);
            }
            else {

                const PacDirection pac_direction = get_pacman_direction();

                switch (pac_direction) {

                    case PAC_BOTTOM:
                    entity_textures_array[i] = point_at_entity_texture(DOWN, entity_array[i]);
                    break;

                    case PAC_TOP:
                    entity_textures_array[i] = point_at_entity_texture(UP, entity_array[i]);
                    break;

                    case PAC_LEFT:
                    entity_textures_array[i] = point_at_entity_texture(LEFT, entity_array[i]);
                    break;

                    case PAC_RIGHT:
                    entity_textures_array[i] = point_at_entity_texture(RIGHT, entity_array[i]);
                    break;

                    case PAC_NONE:
                    entity_textures_array[i] = point_at_entity_texture(RIGHT, entity_array[i]);
                    break;

                    default:
                    //Could not find a texture for the entity
                    return;
                }
            }
        }
        else 
        {
            //Unexpected movement / distance between current and target point
            //Abort the function
            return;
        }
        static_tiles_array[i] = point_at_static_texture(x_old_pixel_array[i], y_old_pixel_array[i]);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////    
////Drawing each moving entity frame by frame
////Looping 8 times since we have 8 frames of animation from one cell to another
////Accounts for all movements, grid wrapping and dynamic live eating
//////////////////////////////////////////////////////////////////////////////////////////////////////
    for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
         current_frame <= 8; 
         ++current_frame, ++forward_offset, --backward_offset)  
    {
        //Restoring tiles
        for (uint8_t i = 0; i < num_entites_to_animate; ++i) {

            if (is_ghost_eaten[i] == true){
                //Do nothing
            }

            //Moves RIGHT
            else if (dx[i] == 8 && dy[i] == 0) {

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


            //We did not move, so we don't need to restore any grid states from beforehand since we still occupy the same cell
            else if (dx[i] == 0 && dy[i] == 0) {   
                //do nothing
            }

            //Error case
            else {
                //Error with movement, just do nothing
            }   
        }

        //Drawing ghosts and pacman
        for (uint8_t i = 0; i < num_entites_to_animate; ++i) {
            
            //The ghost is being eaten by pacman
            if (is_ghost_eaten[i] == true) {

                if (current_frame == 8) {
                    
                    switch (entity_array[i]) {

                    case entity_type_inky:  
                        putImage(48,80, 8,8 ,inky_array[inky_right_eye], 0,0);
                        break;
                    
                    case entity_type_blinky: 
                        putImage(56,80, 8,8 ,blinky_array[blinky_right_eye], 0,0);
                        break;
                    
                    case entity_type_pinky: 
                        putImage(64,80, 8,8 ,pinky_array[pinky_right_eye], 0,0);
                        break;
                    
                    case entity_type_clyde: 
                        putImage(72,80, 8,8 ,clyde_array[clyde_right_eye], 0,0);
                        break;
                    }
                }  
            }

            //Moves RIGHT
            else if (dx[i] == 8 && dy[i] == 0) {

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

            //We did not move, this is for the case that something moves over us next turn and we still haven't moved
            //So we redraw ourselves so it doesn't look like we disappeared
            else if (dx[i] == 0 && dy[i] == 0)
            {   
                putImage(x_old_pixel_array[i], y_old_pixel_array[i], 8,8, entity_textures_array[i], 0,0);
            }

            //Error case
            else {
                //Error with movement, just do nothing
            }  
        } 
        //End of frame, needs to delay now
        //insert sound here
        //Only play sound if the sound setting is on, otherwise we just use a normal delay
        //All sounds and delays add up to 60 ms for each frame

        if(get_pacman_state() == God && get_music_setting()){
            playNote(fright_mode_sound());
            delay(20);
            playNote(fright_mode_sound());
            delay(20);
            playNote(fright_mode_sound());
            delay(20);
        }
        else if (get_pacman_state() == Mortal && get_music_setting())
        {
            playNote(waka_waka());
            delay(15);
            playNote(waka_waka());
            delay(15);
            playNote(waka_waka());
            delay(15);
            playNote(waka_waka());
            delay(15);
        }
        else
        {   
            playNote(0);
            delay(60);
        }
        
    }
    //Draw users score once all movement is over
    printNumber(get_score(),90,0,WHITE_TEXT,0);
}

//Redrawing eaten ghosts in the middle of the screen, based off their starting positions
void eat_ghost(const enum entity_type ghost) {

    const uint16_t* enitity_texture = NULL;
    const PacDirection pac_direction = get_pacman_direction();

    switch (pac_direction) {
        case PAC_BOTTOM:
            if(is_mouth_open) enitity_texture = pacman_array[pacman_bottom_open];
            if(!is_mouth_open) enitity_texture = pacman_array[pacman_bottom_closed];
        break;

        case PAC_TOP:
            if(is_mouth_open) enitity_texture = pacman_array[pacman_top_open];
            if(!is_mouth_open) enitity_texture = pacman_array[pacman_top_closed];
        break;

        case PAC_LEFT:
            if(is_mouth_open) enitity_texture = pacman_array[pacman_left_open];
            if(!is_mouth_open) enitity_texture = pacman_array[pacman_left_closed];
        break;

        case PAC_RIGHT:
            if(is_mouth_open) enitity_texture = pacman_array[pacman_right_open];
            if(!is_mouth_open) enitity_texture = pacman_array[pacman_right_closed];
        break;

        case PAC_NONE:
            if(is_mouth_open) enitity_texture = pacman_array[pacman_right_open];
            if(!is_mouth_open) enitity_texture = pacman_array[pacman_right_closed];
        break;    

        default:
        //Couldnt find the texture for pacman, simply abort the function
        return;
    }

    const uint8_t pac_x_pixel = get_pacman_position()->y * 8;
    const uint8_t pac_y_pixel = get_pacman_position()->x * 8;

    putImage(pac_x_pixel, pac_y_pixel, 8,8, enitity_texture, 0,0);

    switch (ghost) {
        case entity_type_inky:  
            enitity_texture = inky_array[inky_right_eye];
            putImage(48,80, 8,8 ,enitity_texture, 0,0);
            break;

        case entity_type_blinky: 
            enitity_texture = blinky_array[blinky_right_eye];
            putImage(56,80, 8,8 ,enitity_texture, 0,0);
            break;

        case entity_type_pinky: 
            enitity_texture = pinky_array[pinky_right_eye];
            putImage(64,80, 8,8 ,enitity_texture, 0,0);
            break;

        case entity_type_clyde: 
            enitity_texture = clyde_array[clyde_right_eye];
            putImage(72,80, 8,8 ,enitity_texture, 0,0);
            break;

        default:
            //Could not find the texture of the ghost that was eaten, abort the function
            return;  
    }
    //Draw users score
    printNumber(get_score(),90,0,WHITE_TEXT,0);
}

//Cool animation of pacman dying
void draw_pacman_dying(const Point pac_current, const Point ghost_current, enum entity_type ghost) {

    uint8_t ghost_x_pixel = ghost_current.y * 8;
    uint8_t ghost_y_pixel = ghost_current.x * 8;

    int8_t dx_pixels = (pac_current.y * 8) - (ghost_current.y * 8);
    int8_t dy_pixels = (pac_current.x * 8) - (ghost_current.x * 8);

    const uint16_t* ghost_texture = NULL;
    const uint16_t* const static_texture = point_at_static_texture(ghost_x_pixel,ghost_y_pixel);

    //Moves RIGHT
    if (dx_pixels == 8 && dy_pixels == 0) {
        //Drawing over the tiles in the direction we are moving
        ghost_texture = point_at_entity_texture(RIGHT,ghost);

        for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
        current_frame <= 8; 
        ++current_frame, ++forward_offset, --backward_offset)  {
            //Redrawing the tile we are leaving
            putColumn(ghost_x_pixel + forward_offset, ghost_y_pixel, static_texture, forward_offset);
            //Drawing moving ghost
            putImage(ghost_x_pixel + current_frame, ghost_y_pixel, 8,8, ghost_texture, 0,0);
            delay(75);
        }
    }
    
    //Moves DOWN
    else if (dx_pixels == 0 && dy_pixels == 8) {
        //Drawing over the tiles in the direction we are moving
        ghost_texture = point_at_entity_texture(DOWN,ghost);

        for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
        current_frame <= 8; 
        ++current_frame, ++forward_offset, --backward_offset)  {
            
            //Redrawing the tile we are leaving
            putRow(ghost_x_pixel, ghost_y_pixel + forward_offset, static_texture, forward_offset);
            //Drawing moving ghost
            putImage(ghost_x_pixel, ghost_y_pixel + current_frame, 8,8, ghost_texture, 0,0);
            delay(75);
        }
    }

    //Moves LEFT
    else if (dx_pixels == -8 && dy_pixels == 0) {
        //Drawing over the tiles in the direction we are moving
        ghost_texture = point_at_entity_texture(LEFT,ghost);

        for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
        current_frame <= 8; 
        ++current_frame, ++forward_offset, --backward_offset)  {
            
            //Redrawing the tile we are leaving
            putColumn(ghost_x_pixel + backward_offset, ghost_y_pixel, static_texture, backward_offset);
            //Drawing moving ghost
            putImage(ghost_x_pixel - current_frame, ghost_y_pixel, 8,8, ghost_texture, 0,0);
            delay(75);
        }
    }
    //Moves UP
    else if (dx_pixels == 0 && dy_pixels == -8) {
        //Drawing over the tiles in the direction we are moving
        ghost_texture = point_at_entity_texture(UP,ghost);

        for (uint8_t current_frame = 1, forward_offset = 0, backward_offset = 7; 
        current_frame <= 8; 
        ++current_frame, ++forward_offset, --backward_offset)  {
            
            //Redrawing the tile we are leaving
            putRow(ghost_x_pixel, ghost_y_pixel + backward_offset, static_texture, backward_offset);
            //Drawing moving ghost
            putImage(ghost_x_pixel, ghost_y_pixel - current_frame, 8,8, ghost_texture, 0,0);
            delay(75);
        }
    }
}	

//-------------------------------------------------------------- 
//Dynamic movement / gameplay functions                          -- end
//--------------------------------------------------------------