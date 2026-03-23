#include "../include/behaviours/entities&sprites/inky.h"

const Point* get_inky_target_position(){

    if (get_inky_mode() == scatter) return get_inky_scatter_position();

    const Point* blinky_position =  get_blinky_position();
    Point* pacman_position = get_pacman_position();
    //NOTE: when pacman has been created get the direct function and return type for get direction
    uint8_t pacman_direction = get_pacman_direction();

    int8_t pacman_x = get_x_point_coord(pacman_position);
    int8_t pacman_y = get_y_point_coord(pacman_position);
    
    if (pacman_direction == PAC_LEFT) pacman_x -= 2;
    if (pacman_direction == PAC_RIGHT) pacman_x += 2;
    if (pacman_direction == PAC_TOP) pacman_y -= 2;
    if (pacman_direction == PAC_BOTTOM) pacman_y += 2;

    uint8_t blinky_x = get_x_point_coord(blinky_position);
    uint8_t blinky_y = get_y_point_coord(blinky_position);

    int8_t distance_x = blinky_x - pacman_x;
    int8_t distance_y = blinky_y - pacman_y;

    int16_t inky_target_y = pacman_y + distance_y;
    int16_t inky_target_x = pacman_x + distance_x;

    //check if the target is in bounds
    if (inky_target_x >= GRID_ROW_COUNT) inky_target_x = GRID_ROW_COUNT - 2;
    if (inky_target_x <= 0) inky_target_x = 1;
    if (inky_target_y >= GRID_COL_COUNT) inky_target_y = GRID_COL_COUNT - 2;
    if (inky_target_y <= 0) inky_target_y= 2;

    //check if inky's target is a wall
    if (is_grid_state(inky_target_x, inky_target_y, cell_wall))
    {
        bool is_target_set = false;
        for (int8_t i = -1; i <= 1; ++i)
        {
            for (int8_t j = -1; j <= 1; ++j)
            {
                //ignore current spot 
                if (j == 0 && i == 0) continue;
                
                //ignore diagonals
                if (i != 0 && j != 0) continue;

                if (inky_target_x + i < 0 || inky_target_x + i >= GRID_ROW_COUNT || inky_target_y + j < 0 || inky_target_y + j >= GRID_COL_COUNT) continue;

                if(is_grid_state(inky_target_x + i, inky_target_y + j, cell_wall)) continue;

                inky_target_x += i;
                inky_target_y += j;
                is_target_set = true;
            }
            if (is_target_set) break;   
        }

        if (!is_target_set) return create_point(get_x_point_coord(pacman_position),
                            get_y_point_coord(pacman_position));;   
    }

    return create_point(inky_target_x, inky_target_y);
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
        eputs("inky target position\r\n");
        printDecimal(get_x_point_coord(get_inky_target_position()));
        printDecimal(get_y_point_coord(get_inky_target_position()));
        eputs("\r\n");
        
        trace_path_a_star(
            temp_point,
            get_inky_target_position(),
            feed_cache
        );

        for (int8_t i = 0; i < MAX_FEED_CAPACITY; i++)
        {
            if (feed_cache[i])
            {
                eputs("inky cache point\r\n");
                eputs("index ");
                printDecimal(i);
                eputs("\r\n");
                printDecimal(get_x_point_coord(feed_cache[i]));
                printDecimal(get_y_point_coord(feed_cache[i]));
                eputs("\r\n\r\n");
            }
        } 
        feed_pointer = 1; //set back to one to restart
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