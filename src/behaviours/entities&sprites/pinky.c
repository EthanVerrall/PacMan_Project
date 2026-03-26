#include "../include/behaviours/entities&sprites/pinky.h"

const Point* get_pinky_target_position()
{
    if (get_pinky_mode() == scatter)
    {
        return create_point(get_x_point_coord(get_pinky_scatter_position()),
                            get_y_point_coord(get_pinky_scatter_position()));
    }

    PacDirection pacman_direction = get_pacman_direction();
    const Point* pacman_position = get_pacman_position();

    int16_t pacman_x_pos = get_x_point_coord(pacman_position);
    int16_t pacman_y_pos = get_y_point_coord(pacman_position);

    int16_t target_x = pacman_x_pos;
    int16_t target_y = pacman_y_pos;

    int16_t dx = 0;
    int16_t dy = 0;

    if (pacman_direction == PAC_RIGHT)
    {
        dx = 1;
    }
    else if (pacman_direction == PAC_LEFT)
    {
        dx = -1;
    }
    else if (pacman_direction == PAC_BOTTOM)
    {
        dy = 1;
    }
    else if (pacman_direction == PAC_TOP)
    {
        dy = -1;
    }

    for (int i = 1; i <= 4; i++)
    {
        int16_t next_x = pacman_x_pos + (dx * i);
        int16_t next_y = pacman_y_pos + (dy * i);

        // Bounds check
        #ifdef GRID_COL_COUNT
            if (next_x < 0 || next_x >= GRID_COL_COUNT) break;
        #else
            if (next_x < 0 || next_x >= 38) break;
        #endif

        #ifdef GRID_ROW_COUNT
            if (next_y < 0 || next_y >= GRID_ROW_COUNT) break;
        #else
            if (next_y < 0 || next_y >= 28) break;
        #endif

        // Stop if blocked
        if (has_grid_state(next_x, next_y, cell_wall))
        {
            break;
        }

        // Furthest valid tile so far
        target_x = next_x;
        target_y = next_y;
    }

    return create_point(target_x, target_y);
}

/** 
 * Get the next position that Inky is to move to based on pacmans position and its AI behaviours
 * Internally, it uses a cache to prevent multiple pathfinding check calls on every cycle/ call to the function
 * 
 * 
 * The feed next takes a reset boolean that determines if it should force a call to the pathfinding algorithm or it should use the cache
*/
const Point* _pinky_feed_next(const bool reset, const bool end){
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
        //run a for loop for a deep copy
        Point* temp_point = create_point(get_x_point_coord(get_pinky_position()),
                                         get_y_point_coord(get_pinky_position()));
        Point* target = get_pinky_target_position();
        trace_path_a_star(
            temp_point,
            target,
            feed_cache
        );
        free(temp_point);
        free(target);
        //reset the behaviour change incase a behaviour change cause the reset
        set_pinky_behaviour_change(false);
        feed_pointer = 1; //set back to one to restart

        //if the value pointed to be the feed_pointer is NULL, i.e meaning the ghost is on the target or somewhat close,
        //or in a case where the algorithm was not able to properly get the ghost path, return the current position of the ghost
        if (!feed_cache[feed_pointer])
        {
            Point* position_deep_cpy = create_deep_copy(get_pinky_position()); //meaning pinky just doesn't move
            feed_cache[feed_pointer] = position_deep_cpy; //add to feed cache so that it would be freed on the next call to a*
            return feed_cache[feed_pointer];
        }
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

const bool get_pinky_behaviour_change(){
    return get_ghost_behaviour_change(_pinky());
}

void set_pinky_behaviour_change(const bool change){
    return set_ghost_behaviour(_pinky(), change);
}

Pinky* _pinky(){
    static Pinky* current_pinky = NULL;
    
    if (!current_pinky)
    {
        //create pinky
        current_pinky = create_ghost(
            'P',
            create_point(10,8),//need to get pinky starting position
            scatter, //start in chase mode?
            create_point(2,1),
            false
        );

        return current_pinky;
    }
    
    //else pinky already exists, do not create a new instance
    return current_pinky;
}