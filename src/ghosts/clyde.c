#include "../../include/behaviours/ghosts/clyde.h"

Point* get_clyde_target_position(Clyde* clyde){
    Point* pacman_position = get_pacman_position();
    if (
        get_x_point_coord(pacman_position) - get_x_point_coord(clyde->position) < 8 ||
        get_y_point_coord(pacman_position) - get_y_point_coord(clyde->position) < 8 
    )
    {
        //runs to scatter position
        return get_clyde_scatter_position(); // work on this function
    }
    //return get_pacman_position();
}