#include "../include/behaviours/entities&sprites/inky.h"

//getting inky's target position might introduce a bug
//also check for blinky's target introducing a bug
const Point* get_inky_target_position()
{
    if (get_inky_mode() == scatter)
    {
        return create_point(get_x_point_coord(get_inky_scatter_position()),
                            get_y_point_coord(get_inky_scatter_position()));
    }

    const Point* blinky_position = get_blinky_position();
    const Point* pacman_position = get_pacman_position();
    PacDirection pacman_direction = get_pacman_direction();

    int16_t blinky_x = get_x_point_coord(blinky_position);
    int16_t blinky_y = get_y_point_coord(blinky_position);

    int16_t ref_x = get_x_point_coord(pacman_position);
    int16_t ref_y = get_y_point_coord(pacman_position);

    // 2 tiles ahead of Pac-Man
    if (pacman_direction == PAC_LEFT)
    {
        ref_x -= 2;
    }
    else if (pacman_direction == PAC_RIGHT)
    {
        ref_x += 2;
    }
    else if (pacman_direction == PAC_TOP)
    {
        ref_y -= 2;
    }
    else if (pacman_direction == PAC_BOTTOM)
    {
        ref_y += 2;
    }

    // Inky target = 2 * reference - Blinky
    int16_t target_x = (2 * ref_x) - blinky_x;
    int16_t target_y = (2 * ref_y) - blinky_y;

    // Clamp to inner walkable bounds (assuming border walls)
    #ifdef GRID_ROW_COUNT
        if (target_x < 1) target_x = 1;
        if (target_x >= GRID_ROW_COUNT - 1) target_x = GRID_ROW_COUNT - 2;
    #else
        if (target_x < 1) target_x = 1;
        if (target_x >= 38 - 1) target_x = 38 - 2;
    #endif

    #ifdef GRID_COL_COUNT
        if (target_y < 1) target_y = 1;
        if (target_y >= GRID_COL_COUNT - 1) target_y = GRID_COL_COUNT - 2;
    #else
        if (target_y < 1) target_y = 1;
        if (target_y >= 28 - 1) target_y = 28 - 2;
    #endif

    //if target is a wall, try adjacent non-wall tiles
    if (is_grid_state(target_x, target_y, cell_wall))
    {
        bool is_target_set = false;

        const int offsets[4][2] = {
            { 0, -1 }, // up
            { 1,  0 }, // right
            { 0,  1 }, // down
            {-1,  0 }  // left
        };

        for (int i = 0; i < 4; ++i)
        {
            int16_t next_x = target_x + offsets[i][0];
            int16_t next_y = target_y + offsets[i][1];

            #ifdef GRID_ROW_COUNT
                if (next_x < 1 || next_x >= GRID_ROW_COUNT - 1) continue;
            #else
                if (next_x < 1 || next_x >= 38 - 1) continue;
            #endif

            #ifdef GRID_COL_COUNT
                if (next_y < 1 || next_y >= GRID_COL_COUNT - 1) continue;
            #else
                if (next_y < 1 || next_y >= 28 - 1) continue;
            #endif

            if (is_grid_state(next_x, next_y, cell_wall))
            {
                continue;
            }
            

            target_x = next_x;
            target_y = next_y;
            is_target_set = true;
            break;
        }

        if (!is_target_set)
        {
            return create_point(
                get_x_point_coord(pacman_position),
                get_y_point_coord(pacman_position)
            );
        }
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
const Point* _inky_feed_next(const bool reset, const bool end){
    static Point* feed_cache[MAX_FEED_CAPACITY]; //use 50 as the max capacity of the feed... 60 bytes
    static uint8_t feed_pointer = 1;

    //game is finished, free all memory
    if (end)
    {
        free_arr(feed_cache);
        return NULL;
    }

    //-11 4
    

    if (reset || feed_pointer == MAX_FEED_CAPACITY || !feed_cache[feed_pointer]) //only force a reset if the feed_cache is actually empty or reset is passed
    {
        //get the ghosts target position
        //get the ghosts actual position
        //the algorithm would trace a path based on both positions
        Point* temp_point = create_point(get_x_point_coord(get_inky_position()),
                                         get_y_point_coord(get_inky_position()));
        Point* target = get_inky_target_position();
        
        trace_path_a_star(
            temp_point,
            target,
            feed_cache
        );
        free(temp_point);
        free(target);
        feed_pointer = 1; //set back to one to restart

        //if the value pointed to be the feed_pointer is NULL, i.e meaning the ghost is on the target or somewhat close,
        //or in a case where the algorithm was not able to properly get the ghost path, return the current position of the ghost
        if (!feed_cache[feed_pointer])
        {
            Point* position_deep_cpy = create_deep_copy(get_inky_position()); //meaning inky just doesn't move
            feed_cache[feed_pointer] = position_deep_cpy; //add to feed cache so that it would be freed on the next call to a*
            return feed_cache[feed_pointer];
        }
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

const bool set_inky_position(const uint8_t x, const uint8_t y){
    return set_ghost_position(_inky(), x, y);
}

const GhostMode get_inky_mode(){
    return get_ghost_mode(_inky());
}

const void set_inky_mode(GhostMode mode){
    return set_ghost_mode(_inky(), mode);
}

Inky* _inky(){
    static Inky* current_inky = NULL;
    
    if (!current_inky)
    {
        //create inky
        current_inky = create_ghost(
            'I',
            create_point(10,6),//need to get inky starting position
            scatter, //start in chase mode?
            create_point(18,14)
        );

        return current_inky;
    }
    
    //else inky already exists, do not create a new instance
    return current_inky;
}