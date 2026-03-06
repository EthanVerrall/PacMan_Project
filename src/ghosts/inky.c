#include "../../include/behaviours/ghosts/inky.h"

const Point* get_inky_target_position(){
    //return get_pacman_position();
}

const Point* get_inky_scatter_position(){
    return get_ghost_scatter_position(_inky());
}

const Point* get_inky_position(){
    return get_ghost_position(_inky());
}

const Inky* _inky(){
    static Inky* current_inky = NULL;
    
    if (!current_inky)
    {
        //create inky
        current_inky = create_ghost(
            'I',
            create_point(0,0),//need to get inky starting position
            chase, //start in chase mode?
            create_point(31,31)
        );

        return current_inky;
    }
    
    //else inky already exists, do not create a new instance
    return current_inky;
}