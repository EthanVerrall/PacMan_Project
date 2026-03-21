#include "../include/behaviours/entities&sprites/blinky.h"

const Point* get_blinky_target_position(){
    if (get_blinky_mode() == scatter) return get_blinky_scatter_position();
    return get_pacman_position(); //chases pacman directly
}

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _blinky_feed_next(const bool reset, const bool end){
    static Point* feed_cache[MAX_FEED_CAPACITY]; //use 30 as the max capacity of the feed... 60 bytes
    static uint8_t feed_pointer = 1;

    //game is finished, free all memory
    if (end)
    {
        free_arr(feed_cache);
        return NULL;
    }

    if (reset || feed_pointer == MAX_FEED_CAPACITY || !feed_cache[feed_pointer]) //only force a reset if the feed_cache is actually empty 
                                                                                 //or reset is passed
    {
        //get the ghosts target position
        //get the ghosts actual position
        //the algorithm would trace a path based on both positions
        Point* temp_point = create_point(get_x_point_coord(get_blinky_position()),
                                         get_y_point_coord(get_blinky_position()));
        trace_path_a_star(
            temp_point,
            get_blinky_target_position(),
            feed_cache
        );
        temp_point = destroy_point(temp_point);
        feed_pointer = 1; //set back to one to restart
    }
    Point* curr_point_to_return = feed_cache[feed_pointer];
    
    feed_pointer++;
    return curr_point_to_return;
}

const Point* get_blinky_scatter_position(){
    return get_ghost_scatter_position(_blinky());
}

const Point* get_blinky_position(){
    return get_ghost_position(_blinky());
}

const bool set_blinky_position(const uint8_t x, const uint8_t y){
    return set_ghost_position(_blinky(), x, y);
}

const GhostMode get_blinky_mode(){
    return get_ghost_mode(_blinky());
}

const void set_blinky_mode(GhostMode mode){
    return set_ghost_mode(_blinky(), mode);
}

Blinky* _blinky(){
    static Blinky* current_blinky = NULL;
    
    if (!current_blinky)
    {
        //create inky
        current_blinky = create_ghost(
            'B',
            create_point(10,7),//need to get blinky starting position
            scatter, //start in chase mode?
            create_point(2,14)
        );

        return current_blinky;
    }
    
    //else blinky already exists, do not create a new instance
    return current_blinky;
}