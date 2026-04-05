#include "../include/behaviours/algo.h"
#include "../include/grid.h"

void trace_path_a_star(const Point* current, const Point* target, Point result[]){

    //check for nullness
    if(!current || !target){ 
        //eputs("invalid current or target");
        return;
    }

    //free array
    clear_arr(result);

    Point current_copy = create_deep_copy_stack(current);

    //g_cost array of the grid, storing the cost of each path on the grid, i.e steps taken to reach a particular point from the start point
    uint8_t g_cost[GRID_ROW_COUNT][GRID_COL_COUNT];

    //initialise the g_cost grid with a default value of 255 (which is the maximum value for an unsigned 8 bit integer, 
    //it is also a value that is not possible to be reached by the g_cost since the maximum path length is 29)
    for (uint8_t i = 0; i < GRID_ROW_COUNT; i++)
    {
        for (uint8_t j = 0; j < GRID_COL_COUNT; j++)
        {
            g_cost[i][j] = 255;
        }
    }

    //the g_cost of the starting point is 0 since we are already there
    g_cost[current_copy.x][current_copy.y] = 0;

    //track our open and closed points
    //this is just in the case that max path is changed maybe or removed
    //so that we do not scratch our heads over errors later
    #ifdef MAX_PATH_STORE
        Point open_points[MAX_PATH_STORE];
         for (uint8_t i = 0; i < MAX_PATH_STORE; i++) {
            open_points[i].x = INVALID_POINT;
            open_points[i].y = INVALID_POINT;
         }
    #else
        Point open_points[30];
        for (uint8_t i = 0; i < 30; i++) {
            open_points[i].x = INVALID_POINT;
            open_points[i].y = INVALID_POINT;
        }
    #endif
    

    if(compare_points(&current_copy, target)){
        //this means that we are already at our target
        push(&current_copy, result);
        return;
    }

    //add the current to open_points
    push(&current_copy, open_points);
    
    while (is_not_empty(open_points))
    {

        //find the node with the lowest f(n) = g(n) + h(n) in the open points,
        //where g(n) is the cost from the start node to the current node, and is based on the g_cost array
        //and h(n) is the heuristic cost from the current node to the target node
        //now we need to also consider the g_cost here as well
        Point current_smallest = find_smallest_heuristic_node(open_points, target, g_cost);
        if (!is_point_valid(&current_smallest)) break;

        uint8_t currents_x = current_smallest.x;
        uint8_t currents_y = current_smallest.y;

        //remove from the open points
        remove_item(&current_smallest, open_points);

        //If the current_smallest is the target node, we have reached our target.
        //so we reconstruct path from g_cost array

        if(compare_points(&current_smallest, target)) {


            // Change these from uint8_t to int16_t
            int16_t x = current_smallest.x;
            int16_t y = current_smallest.y;

            while(g_cost[x][y] != 0)
            {
                Point p;
                p.x = x;
                p.y = y;
                if (!push(&p, result))  //push failed, list is full
                {
                    eputs("push failed, list is full\r\n");
                    break;
                }
                bool found = false;

                for(int8_t i = -1; i <= 1 && !found; i++)
                for(int8_t j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0) continue;
                    if (i != 0 && j != 0) continue;

                    int16_t neighbour_x = x + i;
                    int16_t neighbour_y = y + j;

                    // explicit bounds check before any array access
                    if (neighbour_x < 0 || neighbour_y < 0 ||
                        neighbour_x >= GRID_ROW_COUNT || neighbour_y >= GRID_COL_COUNT)
                        continue;

                    if (g_cost[neighbour_x][neighbour_y] == g_cost[x][y] - 1)
                    {
                        x = neighbour_x; 
                        y = neighbour_y;
                        found = true;
                        break;
                    }
                }
                if (!found) break;
            }
            Point start_node;  // x,y are now at the start (g_cost == 0)
            start_node.x = x;
            start_node.y = y;
            push(&start_node, result);
            //because we work backwards, we would need to reverse the list so feed can properly get the path forwards
            reverse_points(result);
            return;
        }

        /** 
         * MENTAL NOTE:
         * each successor is a section just one layer above the current smallest
         * so N,E,W,S, N-E, S-E, S-W, N-W
        */

        /** 
         * Since we are using the manhattan algorithm
        */
        for (int8_t i = -1; i <= 1 ; i++)
        {
            for (int8_t j = -1; j <= 1; j++)
            {
                //ignore [0][0], that is our current spot
                if (i == 0 && j == 0) continue;

                //ignore diagonals too
                if (i != 0 && j != 0) continue;

                //check if the grid position is out of bounds
                //get grid state returns zero if and only if the grid is out of bound

                int16_t nx = (int16_t)current_smallest.x + i;
                int16_t ny = (int16_t)current_smallest.y + j;

                if (nx < 0 || ny < 0 || nx >= GRID_ROW_COUNT || ny >= GRID_COL_COUNT)
                    continue;
                
                //check if the grid position is a wall
                if(has_grid_state(nx, ny, cell_wall)) continue;

                

                //the g_cost of the current smallest is the g_cost of the current smallest's parent + 1 
                //as we are moving one step from the parent to the current smallest
                uint8_t tentative_g = g_cost[currents_x][currents_y] + 1;

                uint8_t neighbour_x = nx;
                uint8_t neighbour_y = ny;

                //obvivously if the neighbour has a g_cost that is greater than or equal to the g_cost of the current smallest, 
                //then we ignore it as it is not a better path
                if (tentative_g >= g_cost[neighbour_x][neighbour_y]) continue;

                //as all the checks have passed, we will now update the g_cost of the neighbour to be the tentative g_cost
                g_cost[neighbour_x][neighbour_y] = tentative_g;

                Point temp_neighbour;
                temp_neighbour.x = neighbour_x;
                temp_neighbour.y = neighbour_y;

                //just add the neighbour to the open list to be checked in the next iteration
                //but check first if open points is full, 
                //if it is, no worries, we return, we remove less optimal nodes to make space for more optimal nodes, 
                //so we would not miss out on the optimal path, just maybe not find it as fast as we could have if we had more space in the open points
                if (!search_item(&temp_neighbour, open_points)) {
                    if (get_list_size(open_points) >= MAXARRSIZE) {
                        //find and replace the node with the highest f cost
                        uint8_t worst_idx = 0;
                        uint16_t worst_f = 0;
                        for (uint8_t k = 0; k < MAXARRSIZE; k++) {
                            if (!is_point_valid(&open_points[k])) continue;
                            uint16_t f = g_cost[open_points[k].x][open_points[k].y] 
                                    + calculate_heuristics_h(&open_points[k], target);
                            if (f > worst_f) {
                                worst_f = f;
                                worst_idx = k;
                            }
                        }
                        //only replace if our new node is actually better
                        uint16_t new_f = g_cost[temp_neighbour.x][temp_neighbour.y]
                                    + calculate_heuristics_h(&temp_neighbour, target);
                        if (new_f < worst_f) {
                            open_points[worst_idx] = temp_neighbour;
                        }
                    } else {
                        push(&temp_neighbour, open_points);
                    }
                }
            }
        }
    }

    return;
}

//Kindly note that this function does not check the values of the points
//It is the responsibility of the programmer to check that the values are valid
//and are within the range of the board
uint8_t calculate_heuristics_h(const Point* current, const Point* target){
    //makes sure that the function does not work on null pointers

    if (!current|| !target) return 0;

    //use the manhattan formula to work out the heuristic value
    //since we heuristic val can be negative, we use an int here to just prevent overflow
    //we would cast to an unsigned int afterwards

    int8_t _heuristic_val_x = current->x - target->x;

    int8_t _heuristic_val_y = current->y - target->y;

    

    if (_heuristic_val_x < 0) _heuristic_val_x = -_heuristic_val_x;
    if (_heuristic_val_y < 0) _heuristic_val_y = -_heuristic_val_y;
    int8_t _heuristic_val = _heuristic_val_x + _heuristic_val_y;
    
    return (uint8_t) _heuristic_val;
}

//This algorithm calculates the smallest heuristic node in the a list (most likely the open list)
Point find_smallest_heuristic_node(Point list[], const Point* target, const uint8_t g_cost[][GRID_COL_COUNT]){
    if (!list || !is_point_valid(&list[0])) {
        Point temp = {INVALID_POINT, INVALID_POINT};
        return temp;
    }
    uint16_t smallest_heuristic_f = g_cost[list[0].x][list[0].y] + calculate_heuristics_h(&list[0], target);
    Point smallest_heuristic_point = list[0];
    for (uint8_t i = 1; i < get_list_size(list); i++)
    {
        if (is_point_valid(&list[i])){
            uint8_t current_heuristic = calculate_heuristics_h(&list[i], target);
            uint8_t current_g = g_cost[list[i].x][list[i].y];
            uint16_t current_f = current_g + current_heuristic;
            if (current_f < smallest_heuristic_f)
            {
                smallest_heuristic_f = current_f;
                smallest_heuristic_point = list[i];
            }
        }
    }

    return smallest_heuristic_point;
}