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
    }
    if (pacman_direction == 0) //right
    {
        //check that the position right is not outside the board
        
    }
    
    
}