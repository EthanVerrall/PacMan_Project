#include "../../include/behaviours/algo.h"

Point* trace_path_a_star(const Point* current, const Point* target, const Grid* board){

    //check for nullness
    if(!current || !target) return NULL;

    //track our open and closed points
    //this is just in the case that max path is changed maybe or removed
    //so that we do not scratch our heads over errors later
    #ifdef MAX_PATH_STORE
        const Point* open_points[MAX_PATH_STORE];
        const Point* closed_points[MAX_PATH_STORE];
    #else
        const Point* open_points[30];
        const Point* closed_points[30];
    #endif

    if(compare_points(current, target)){
        //this means that we are already at our target
        push(current, closed_points);
        return closed_points;
    }

    //add the current to open_points
    push(current, open_points);
    
    while (is_not_empty(open_points))
    {
        //We are starting from 1 as the cost from block to block is 1
        uint8_t current_cost = 1;

        //find the node with the lowest
        Point* current_smallest = find_smallest_heuristic_node(open_points, target);

        //remove from the open points
        remove_item(current_smallest, open_points);

        //If the current_smallest is the target node, we have reached our target... Yay
        if(compare_points(current_smallest, target)) {
            push(current_smallest, closed_points);
            break;
        }

        /** 
         * MENTAL NOTE:
         * each successor is a section just one layer above the current smallest
         * so N,E,W,S, N-E, S-E, S-W, N-W
        */

        for (uint8_t i = -1; i <= 1 ; i++)
        {
            for (uint8_t j = -1; j <= 1; j++)
            {
                //ignore [0][0], that is our current spot
                if (i == 0 && j == 0) continue;
                //NOTE: ask ethan for a function that checks if a place on the grid is a wall
                if(is_wall(board, (get_x_point_coord(current_smallest) + i), (get_y_point_coord(current_smallest) + j))) continue;

                Point* temp_neighbour = create_point(
                    get_x_point_coord(current_smallest) + i,
                    get_y_point_coord(current_smallest) + j
                );
                //if the item successor is in the open list, we ignore
                //TODO: check that the element has a lower f(n) than the successor as well (and it with this)
                if(search_item(temp_neighbour,open_points)) continue;

                //if the item successor is in the closed list, and it has a lower f(n) than the successor, we ignore
                //TODO: check that the element has a lower f(n) than the successor as well (and it with this)
                if(search_item(temp_neighbour,open_points)) continue;

                //just add the neighbour to the open list to be checked in the next iteration
                push(temp_neighbour, open_points);
            }
        }

        //push the current_smallest into the closed list
        push(current_smallest, closed_points);
    }
    //free the open points, closed points might be freed by the user of this function
    free_arr(open_points);

    //are we returning the closed list or the open one
    return closed_points;
}

Point* trace_path_dfs(const Point* current, const Point* target,const Grid* board){
    return create_point(7,8);
}

//Kindly note that this function does not check the values of the points
//It is the responsibility of the programmer to check that the values are valid
//and are within the range of the board
uint8_t calculate_heuristics_h(const Point* current, const Point* target){
    //makes sure that the function does not work on null pointers

    if (!current && target) {
        //use the manhattan formula to work out the heuristic value
        //since we heuristic val can be negative, we use an int here to just prevent overflow
        //we would cast to an unsigned int afterwards
        int _heuristic_val = (
            get_x_point_coord(current) - get_x_point_coord(target)
        ) 
        + (
            get_y_point_coord(current) - get_y_point_coord(target)
        );

        //the heuristic must not be a negative value since it is calculating the nearness of a path to a target
        if (_heuristic_val < 0) _heuristic_val *= -1;
        
        return (uint8_t) _heuristic_val;
    }

    //in the case that any of the points passed in are not valid
    return 0;
}

//TODO: Work on this later
Point* find_smallest_heuristic_node(Point* list[], const Point* target){
    uint8_t max_heuristic = 0;
    for (size_t i = 0; i < get_list_size(list); i++)
    {
        if (list){
            uint8_t heuristic = calculate_heuristics_h(list, target);
        } 
        
    }
    
}