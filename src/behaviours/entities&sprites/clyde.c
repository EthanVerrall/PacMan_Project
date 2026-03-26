#include "../include/behaviours/entities&sprites/clyde.h"

const Point* get_clyde_target_position(){

    if (get_clyde_mode() == scatter)
    {
        return create_point(get_x_point_coord(get_clyde_scatter_position()),
                            get_y_point_coord(get_clyde_scatter_position()));
    }
    
    const Point* pacman_position = get_pacman_position();

    const Point* clyde_pos = get_clyde_position();

    int16_t pacman_clyde_distance_x = get_x_point_coord(pacman_position) - get_x_point_coord(clyde_pos);
    int16_t pacman_clyde_distance_y = get_y_point_coord(pacman_position) - get_y_point_coord(clyde_pos);

    //check if the distance in x and y is less than 8.. I am using 4 here because 
    if ((pacman_clyde_distance_x * pacman_clyde_distance_x) +  (pacman_clyde_distance_y * pacman_clyde_distance_y) < 16)
    {
        //runs to scatter position
        //check if clyde is already at his scatter position
        if (compare_points(clyde_pos, get_clyde_scatter_position()))
        {
            //just chase pacman then, for now, we can take it as a feature since there are no other places to move to
            return create_point(get_x_point_coord(pacman_position),
                            get_y_point_coord(pacman_position));
        }
        
        return create_point(get_x_point_coord(get_clyde_scatter_position()),
                            get_y_point_coord(get_clyde_scatter_position())); // work on this function
    }

    //chases pacman when he is far away, if he is close, he runs to his scatter positions
    return create_point(get_x_point_coord(pacman_position),
                            get_y_point_coord(pacman_position));
}

const Point* _clyde_feed_next(const bool reset, const bool end){
    static Point* feed_cache[MAX_FEED_CAPACITY]; //use 50 as the max capacity of the feed... 60 bytes
    static uint8_t feed_pointer = 1;

    //game is finished, free all memory
    if (end)
    {
        free_arr(feed_cache);
        return NULL;
    }

    if (reset || feed_pointer == MAX_FEED_CAPACITY || !feed_cache[feed_pointer]) //only force a reset if the feed_cache is actually empty or reset is passed
    {
        //get the ghosts target position
        //get the ghosts actual position
        //the algorithm would trace a path based on both positions
        Point* temp_point = create_point(get_x_point_coord(get_clyde_position()),
                                         get_y_point_coord(get_clyde_position()));
        Point* target = get_clyde_target_position();
        trace_path_a_star(
            temp_point,
            target,
            feed_cache
        );
        free(temp_point);
        free(target);
        //reset the behaviour change incase a behaviour change cause the reset
        set_clyde_behaviour_change(false);
        feed_pointer = 1; //set back to one to restart

        //if the value pointed to be the feed_pointer is NULL, i.e meaning the ghost is on the target or somewhat close,
        //or in a case where the algorithm was not able to properly get the ghost path, return the current position of the ghost
        if (!feed_cache[feed_pointer])
        {
            Point* position_deep_cpy = create_deep_copy(get_clyde_position()); //meaning clyde just doesn't move
            feed_cache[feed_pointer] = position_deep_cpy; //add to feed cache so that it would be freed on the next call to a*
            return feed_cache[feed_pointer];
        }
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

const bool get_clyde_behaviour_change(){
    return get_ghost_behaviour_change(_clyde());
}

void set_clyde_behaviour_change(const bool change){
    return set_ghost_behaviour(_clyde(), change);
}


Clyde* _clyde(){
    static Clyde* current_clyde = NULL;
    
    if (!current_clyde)
    {
        //create inky
        current_clyde = create_ghost(
            'C',
            create_point(10,9),//need to get clyde starting position
            scatter, //start in chase mode?
            create_point(18,1),
            false
        );

        return current_clyde;
    }
    
    //else clyde already exists, do not create a new instance
    return current_clyde;
}
