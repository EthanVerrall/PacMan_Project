#include "../include/behaviours/entities&sprites/clyde.h"

//todo... I need to write states that check for their current state
const Point* get_clyde_target_position(){
    
    Point* pacman_position = get_pacman_position();

    const Point* clyde_pos = get_clyde_position();

    uint8_t pacman_clyde_distance_x = get_x_point_coord(pacman_position) - get_x_point_coord(clyde_pos);
    uint8_t pacman_clyde_distance_y = get_y_point_coord(pacman_position) - get_y_point_coord(clyde_pos);

    if (pacman_clyde_distance_x < 0) pacman_clyde_distance_x *= -1;
    if (pacman_clyde_distance_y < 0) pacman_clyde_distance_y *= -1;

    if (pacman_clyde_distance_x < 8 || pacman_clyde_distance_y < 8)
    {
        //runs to scatter position
        return get_clyde_scatter_position(); // work on this function
    }

    //get 
    return pacman_position;
}

const Point* _clyde_feed_next(const bool reset, const bool end){
    static Point* feed_cache[MAX_FEED_CAPACITY]; //use 30 as the max capacity of the feed... 60 bytes
    static uint8_t feed_pointer = 0;

    //game is finished, free all memory
    if (end)
    {
        free_arr(feed_cache);
        return NULL;
    }

    if (reset || feed_pointer == MAX_FEED_CAPACITY || !feed_cache[feed_pointer]) //only force a reset if the feed_cache is actually empty or reset is passed
    {
        //free the cache first
        free_arr(feed_cache);
        //get the ghosts target position
        //get the ghosts actual position
        //the algorithm would trace a path based on both positions
        trace_path_a_star(
            get_clyde_position(),
            get_clyde_target_position()
            ,feed_cache
        );
        feed_pointer = 0; //set back to zero to restart
    }
    Point* curr_point_to_return = feed_cache[feed_pointer];
    feed_pointer++;
    return curr_point_to_return;
}

const Point* get_clyde_scatter_position(){
    return get_ghost_scatter_position(_clyde());
}

const Point* get_clyde_position(){
    return get_ghost_position(_clyde());
}


const bool set_clyde_position(const uint8_t x, const uint8_t y){
    return set_ghost_position(_clyde(),x, y);
}

const GhostMode get_clyde_mode(){
    return get_ghost_mode(_clyde());
}

const void set_clyde_mode(GhostMode mode){
    set_ghost_mode(_clyde(), mode);
}


Clyde* _clyde(){
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
