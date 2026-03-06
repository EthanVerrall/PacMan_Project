#include "../../include/behaviours/ghosts/blinky.h"

const Point* get_blinky_target_position(){
    return get_pacman_position(); //work on this after
}

const Point* get_blinky_scatter_position(){
    return get_ghost_scatter_position(_blinky());
}

const Point* get_blinky_position(){
    return get_ghost_position(_blinky());
}

const Blinky* _blinky(){
    static Blinky* current_blinky = NULL;
    
    if (!current_blinky)
    {
        //create inky
        current_blinky = create_ghost(
            'B',
            create_point(0,0),//need to get blinky starting position
            chase, //start in chase mode?
            create_point(31,0)
        );

        return current_blinky;
    }
    
    //else blinky already exists, do not create a new instance
    return current_blinky;
}