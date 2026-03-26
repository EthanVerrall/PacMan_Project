#include "../include/behaviours/entities&sprites/blinky.h"

const Point* get_blinky_target_position(){
    if (get_blinky_mode() == scatter) return create_point(get_x_point_coord(get_blinky_scatter_position()),
                            get_y_point_coord(get_blinky_scatter_position()));
    return create_point(get_x_point_coord(get_pacman_position()),
                        get_y_point_coord(get_pacman_position())); //chases pacman directly
}

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _blinky_feed_next(const bool reset, const bool end){
    static Point* feed_cache[MAX_FEED_CAPACITY]; //use 50 as the max capacity of the feed... 60 bytes
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
        Point* target = get_blinky_target_position();
        trace_path_a_star(
            temp_point,
            target,
            feed_cache
        );
        free(temp_point);
        free(target);
        //reset the behaviour change incase a behaviour change cause the reset
        set_blinky_behaviour_change(false);
        feed_pointer = 1; //set back to one to restart
        //if the value pointed to be the feed_pointer is NULL, i.e meaning the ghost is on the target or somewhat close,
        //or in a case where the algorithm was not able to properly get the ghost path, return the current position of the ghost
        if (!feed_cache[feed_pointer])
        {
            Point* position_deep_cpy = create_deep_copy(get_blinky_position()); //meaning blinky just doesn't move
            feed_cache[feed_pointer] = position_deep_cpy; //add to feed cache so that it would be freed on the next call to a*
            return feed_cache[feed_pointer];
        }
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

const bool get_blinky_behaviour_change(){
    return get_ghost_behaviour_change(_blinky());
}

void set_blinky_behaviour_change(const bool change){
    return set_ghost_behaviour(_blinky(), change);
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
            create_point(2,14),
            false
        );

        return current_blinky;
    }
    
    //else blinky already exists, do not create a new instance
    return current_blinky;
}