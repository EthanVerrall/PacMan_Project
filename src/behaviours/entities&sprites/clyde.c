#include "../include/behaviours/entities&sprites/clyde.h"

const Point* get_clyde_target_position(){

    if (get_clyde_mode() == scatter) return create_deep_copy(get_clyde_scatter_position());

    if (get_clyde_mode() == fright) 
        return get_random_point_on_grid(67); 
    
    const Point* pacman_position = get_pacman_position();

    const Point* clyde_pos = get_clyde_position();

    int16_t pacman_clyde_distance_x = pacman_position->x - clyde_pos->x;
    int16_t pacman_clyde_distance_y = pacman_position->y - clyde_pos->y;

    //check if the distance in x and y is less than 8.. I am using 4 here because 
    if ((pacman_clyde_distance_x * pacman_clyde_distance_x) +  (pacman_clyde_distance_y * pacman_clyde_distance_y) < 16)
    {
        //runs to scatter position
        //check if clyde is already at his scatter position
        if (compare_points(clyde_pos, get_clyde_scatter_position()))
        {
            //just chase pacman then, for now, we can take it as a feature since there are no other places to move to
            return create_point(pacman_position->x,pacman_position->y);
        }
        
        return create_point(get_clyde_scatter_position()->x,get_clyde_scatter_position()->y); // work on this function
    }

    //chases pacman when he is far away, if he is close, he runs to his scatter positions
    return create_point(pacman_position->x, pacman_position->y);
}

const Point _clyde_feed_next(const bool reset, const bool end){
    static Point feed_cache[MAX_FEED_CAPACITY]; //use 50 as the max capacity of the feed... 60 bytes
    static uint8_t feed_pointer = 1;
    for (uint8_t i = 0; i < MAX_FEED_CAPACITY; i++)
    {
        if(feed_cache[i].x == 0 || feed_cache[i].y == 0) {
            feed_cache[i].x = INVALID_POINT;
            feed_cache[i].y = INVALID_POINT;
        } 
    }

    //game is finished, free all memory
    if (end)
    {
        clear_arr(feed_cache);
        Point invalid_point = {INVALID_POINT, INVALID_POINT};
        return invalid_point;
    }

    if (reset || feed_pointer == MAX_FEED_CAPACITY || !is_point_valid(&feed_cache[feed_pointer])) //only force a reset if the feed_cache is actually empty 
                                                                                 //or reset is passed
    {
        //get the ghosts target position
        //get the ghosts actual position
        //the algorithm would trace a path based on both positions
        Point* temp_point = create_point(get_clyde_position()->x,get_clyde_position()->y);
        const Point* target = get_clyde_target_position();
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
        if (!is_point_valid(&feed_cache[feed_pointer]))
        {
            feed_cache[feed_pointer] = create_deep_copy_stack(get_clyde_position());
            return feed_cache[feed_pointer];
        }
    }
    Point curr_point_to_return = feed_cache[feed_pointer];
    
    feed_pointer++;
    return curr_point_to_return;
}

const Point* get_clyde_scatter_position(){
    return get_ghost_scatter_position(_clyde(false));
}

const Point* get_clyde_position(){
    return get_ghost_position(_clyde(false));
}


const bool set_clyde_position(const uint8_t x, const uint8_t y){
    return set_ghost_position(_clyde(false),x, y);
}

const GhostMode get_clyde_mode(){
    return get_ghost_mode(_clyde(false));
}

const void set_clyde_mode(GhostMode mode){
    set_ghost_mode(_clyde(false), mode);
}

const bool get_clyde_behaviour_change(){
    return get_ghost_behaviour_change(_clyde(false));
}

void set_clyde_behaviour_change(const bool change){
    return set_ghost_behaviour(_clyde(false), change);
}


Clyde* _clyde(bool destroy){
    static Clyde* current_clyde = NULL;

    if (destroy)
    {
        //destroy clyde's inner structs
        destroy_point(get_clyde_position());
        destroy_point(get_clyde_scatter_position());
        free(current_clyde);
        current_clyde = NULL;
        return current_clyde;
    }
    
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

Clyde* destroy_clyde(){
    //get clyde
    Clyde* clyde = _clyde(true);
    return NULL;
}