#include "../../include/behaviours/ghosts/inky.h"

#ifndef LEFT
#define LEFT 0 
#endif

#ifndef RIGHT
#define RIGHT 1
#endif

#ifndef TOP
#define TOP 2
#endif

#ifndef BOTTOM
#define BOTTOM 3
#endif

const Point* get_inky_target_position(){

    Point* blinky_position =  get_blinky_position();
    Point* pacman_position = get_pacman_position();
    //NOTE: when pacman has been created get the direct function and return type for get direction
    uint8_t pacman_direction = get_pacman_direction();

    int8_t blinky_x = get_x_point_coord(blinky_position);
    int8_t blinky_y = get_y_point_coord(blinky_position);
    

    if (pacman_direction == LEFT) blinky_x -= 2;
    if (pacman_direction == RIGHT) blinky_x += 2;
    if (pacman_direction == TOP) blinky_y -= 2;
    if (pacman_direction == BOTTOM) blinky_y += 2;

    blinky_x *= 2;
    blinky_y *= 2;

    int8_t distance_x = blinky_x - get_x_point_coord(pacman_position);
    int8_t distance_y = blinky_y - get_y_point_coord(pacman_position);

    //absolute the points in the case that they end up being less than zero
    if(distance_x < 0) distance_x *= -1;
    if(distance_y < 0) distance_y *= -1;

    return create_point(distance_x, distance_y);
}

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _inky_feed_next(const bool reset, const bool end){
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
        //get the ghosts target position
        //get the ghosts actual position
        //the algorithm would trace a path based on both positions
        feed_cache = trace_path_a_star(
            get_inky_position(),
            get_inky_target_position()
        );
        feed_pointer = 0; //set back to zero to restart
    }
    Point* curr_point_to_return = feed_cache[feed_pointer];
    feed_pointer++;
    return curr_point_to_return;
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