#include "../../include/behaviours/ghosts/pinky.h"

Point* get_pinky_target_position(Pinky* pinky){
    //get pacman direction
    uint8_t pacman_direction = get_pacman_direction();
    Point* pacman_position = get_pacman_position();
    uint8_t pacman_x_pos = get_x_point_coord(pacman_position);
    uint8_t pacman_y_pos = get_y_point_coord(pacman_position);

    uint8_t pinky_x_pos = pacman_x_pos;
    uint8_t pinky_y_pos = pacman_y_pos;
    if (pacman_direction == 1) //left
    {
        //check that the position left is not outside the board
        #ifdef MAX_BOARD_X_SIZE
            if (pacman_x_pos + 4 > MAX_BOARD_X_SIZE)
        #else
            if (pacman_x_pos + 4 > 38)
        #endif
            {pinky_x_pos += 4;}        
    }
    if (pacman_direction == 0) //right
    {
        //check that the position right is not outside the board
        #ifdef MIN_BOARD_X_SIZE
            if (pacman_x_pos - 4 < 0)
        #else
            if (pacman_x_pos - 4 < 0)
        #endif
            {pinky_x_pos -= 4;}    
    }
    if (pacman_direction == 2){
        #ifdef MAX_BOARD_Y_SIZE
            if (pacman_y_pos + 4 > MAX_BOARD_Y_SIZE)
        #else
            if (pacman_x_pos + 4 > 28) //????? is this actually 28.... I will just take it as is... 
            // define changes this afterwards
        #endif
            {pinky_y_pos += 4;}    
    }
    if (pacman_direction == 3){
        #ifdef MIN_BOARD_Y_SIZE
            if (pacman_y_pos + 4 < MIN_BOARD_Y_SIZE)
        #else
            if (pacman_y_pos + 4 < 0)
        #endif
            {pinky_y_pos -= 4;}    
    }
    
    return create_point(pinky_x_pos, pinky_y_pos);
}