#include "../include/behaviours/entities&sprites/pinky.h"

const Point* get_pinky_target_position(){
    //get pacman direction
    uint8_t pacman_direction = get_pacman_direction();
    Point* pacman_position = get_pacman_position();
    uint8_t pacman_x_pos = get_x_point_coord(pacman_position);
    uint8_t pacman_y_pos = get_y_point_coord(pacman_position);

    uint8_t pinky_x_pos = pacman_x_pos;
    uint8_t pinky_y_pos = pacman_y_pos;
    if (pacman_direction == 1) //left
    {
        //check that the position left is not outside the board
        #ifdef GRID_ROW_COUNT
            if (pacman_x_pos + 4 > GRID_ROW_COUNT)
        #else
            if (pacman_x_pos + 4 > 38)
        #endif
            {pinky_x_pos += 4;}        
    }
    if (pacman_direction == 0) //right
    {
        //check that the position right is not outside the board
        #ifdef MIN_BOARD_X_SIZE
            if (pacman_x_pos - 4 < 0)
        #else
            if (pacman_x_pos - 4 < 0)
        #endif
            {pinky_x_pos -= 4;}    
    }
    if (pacman_direction == 2){
        #ifdef GRID_COL_COUNT
            if (pacman_y_pos + 4 > GRID_COL_COUNT)
        #else
            if (pacman_x_pos + 4 > 28) //????? is this actually 28.... I will just take it as is... 
            // define changes this afterwards
        #endif
            {pinky_y_pos += 4;}    
    }
    if (pacman_direction == 3){
        #ifdef MIN_BOARD_Y_SIZE
            if (pacman_y_pos + 4 < MIN_BOARD_Y_SIZE)
        #else
            if (pacman_y_pos + 4 < 0)
        #endif
            {pinky_y_pos -= 4;}    
    }
    
    return create_point(pinky_x_pos, pinky_y_pos);
}

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _pinky_feed_next(const bool reset, const bool end){
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
        //run a for loop for a deep copy
        trace_path_a_star(
            get_pinky_position(),
            get_pinky_target_position(),
            feed_cache
        );
        
        feed_pointer = 0; //set back to zero to restart
    }
    Point* curr_point_to_return = feed_cache[feed_pointer];
    feed_pointer++;
    return curr_point_to_return;
}

const Point* get_pinky_scatter_position(){
    return get_ghost_scatter_position(_pinky());
}

const Point* get_pinky_position(){
    return get_ghost_position(_pinky());
}

const bool set_pinky_position(const uint8_t x, const uint8_t y){
    return set_ghost_position(_pinky(), x, y);
}

const GhostMode get_pinky_mode(){
    return get_ghost_mode(_pinky());
}

const void set_pinky_mode(GhostMode mode){
    return set_ghost_mode(_pinky(), mode);
}

Pinky* _pinky(){
    static Pinky* current_pinky = NULL;
    
    if (!current_pinky)
    {
        //create pinky
        current_pinky = create_ghost(
            'P',
            create_point(0,0),//need to get pinky starting position
            chase, //start in chase mode?
            create_point(0,0)
        );

        return current_pinky;
    }
    
    //else pinky already exists, do not create a new instance
    return current_pinky;
}