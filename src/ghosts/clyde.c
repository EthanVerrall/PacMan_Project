#include "../../include/behaviours/ghosts/clyde.h"

const Point* get_clyde_target_position(Clyde* clyde){
    Point* pacman_position = get_pacman_position();
    if (
        get_x_point_coord(pacman_position) - get_x_point_coord(clyde->position) < 8 ||
        get_y_point_coord(pacman_position) - get_y_point_coord(clyde->position) < 8 
    )
    {
        //runs to scatter position
        return get_clyde_scatter_position(); // work on this function
    }

    //get 
    return pacman_position;
}

const Point* get_clyde_scatter_position(){
    return get_ghost_scatter_position(_clyde());
}

const Point* get_clyde_position(){
    return get_ghost_position(_clyde());
}

const Clyde* _clyde(){
    static Clyde* current_clyde = NULL;
    
    if (!current_clyde)
    {
        //create inky
        current_clyde = create_ghost(
            'C',
            create_point(0,0),//need to get clyde starting position
            chase, //start in chase mode?
            create_point(0,31)
        );

        return current_clyde;
    }
    
    //else clyde already exists, do not create a new instance
    return current_clyde;
}
