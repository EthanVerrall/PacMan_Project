#include "../include/behaviours/entities&sprites/blinky.h"
#include "serial.h"

const Point* get_blinky_target_position(){
    if (get_blinky_mode() == scatter) return create_deep_copy(get_blinky_scatter_position());

    if (get_blinky_mode() == fright) 
        return get_random_point_on_grid(67); //67 67 67
    
    return create_deep_copy(get_pacman_position()); //chases pacman directly
}

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
Point _blinky_feed_next(const bool reset, const bool end){
    static Point feed_cache[MAX_FEED_CAPACITY]; //use 50 as the max capacity of the feed... 60 bytes
    for (uint8_t i = 0; i < MAX_FEED_CAPACITY; i++)
    {
        if(feed_cache[i].x == 0 || feed_cache[i].y == 0) {
            feed_cache[i].x = INVALID_POINT;
            feed_cache[i].y = INVALID_POINT;
        } 
    }
    
    static uint8_t feed_pointer = 1;
    /* eputs("Printing blinky feed before \r\n");
    for (size_t i = 0; i < MAX_FEED_CAPACITY; i++)
    {
        printDecimal(feed_cache[i].x);   
        printDecimal(feed_cache[i].y);   
    }
    eputs("\r\n"); */

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
        Point* temp_point = create_point(get_blinky_position()->x,
                                         get_blinky_position()->y);
        const Point* target = get_blinky_target_position();
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
        if (!is_point_valid(&feed_cache[feed_pointer]))
        {
            feed_cache[feed_pointer] = create_deep_copy_stack(get_blinky_position());
            return feed_cache[feed_pointer];
        }
    }

    /* eputs("Printing blinky feed after\r\n");
    for (size_t i = 0; i < MAX_FEED_CAPACITY; i++)
    {
        printDecimal(feed_cache[i].x);   
        printDecimal(feed_cache[i].y);   
    }
    eputs("\r\n"); */

    Point curr_point_to_return = feed_cache[feed_pointer];
    
    feed_pointer++;
    return curr_point_to_return;
}

const Point* get_blinky_scatter_position(){
    return get_ghost_scatter_position(_blinky(false));
}

const Point* get_blinky_position(){
    return get_ghost_position(_blinky(false));
}

const bool set_blinky_position(const uint8_t x, const uint8_t y){
    return set_ghost_position(_blinky(false), x, y);
}

const GhostMode get_blinky_mode(){
    return get_ghost_mode(_blinky(false));
}

const void set_blinky_mode(GhostMode mode){
    return set_ghost_mode(_blinky(false), mode);
}

const bool get_blinky_behaviour_change(){
    return get_ghost_behaviour_change(_blinky(false));
}

void set_blinky_behaviour_change(const bool change){
    return set_ghost_behaviour(_blinky(false), change);
}



Blinky* _blinky(bool destroy){
    static Blinky* current_blinky = NULL;

    if (destroy)
    {
        //destroy blinkys inner structs
        destroy_point(get_blinky_position());
        destroy_point(get_blinky_scatter_position());
        free(current_blinky);
        current_blinky = NULL;
        return current_blinky;
    }
    
    
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

Blinky* destroy_blinky(){
    Blinky* blinky = _blinky(true);
    return NULL;
}