#include "../include/behaviours/algo.h"
#include "../include/grid.h"
#include "../include/serial.h"

void trace_path_a_star(const Point* current, const Point* target, Point* result[]){

    //free array
    free_arr(result); // -- @JOSHUA CHECK THIS ONE PLEASE

    //as per the discussion we had, g_cost grid is now going to be included, 
    //It would be a mutli-dimensional array of the same size as the board, and it would store the g_cost of each point on the board

    //because of the x,y and row, col issue, I would need to ask ethan if the gcost would be correct
    uint8_t g_cost[GRID_ROW_COUNT][GRID_COL_COUNT];

    //initialise the g_cost grid with a default value of 255 (which is the maximum value for an unsigned 8 bit integer, 
    //it is also a value that is not possible to be reached by the g_cost since the maximum path length is 29)
    for (size_t i = 0; i < GRID_ROW_COUNT; i++)
    {
        for (size_t j = 0; j < GRID_COL_COUNT; j++)
        {
            g_cost[i][j] = 255;
        }
    }

    //check for nullness
    if(!current || !target) return;

    //the g_cost of the starting point is 0 since we are already there
    g_cost[get_x_point_coord(current)][get_y_point_coord(current)] = 0;

    //track our open and closed points
    //this is just in the case that max path is changed maybe or removed
    //so that we do not scratch our heads over errors later
    #ifdef MAX_PATH_STORE
        Point* open_points[MAX_PATH_STORE];
         for (size_t i = 0; i < MAX_PATH_STORE; i++) open_points[i] = NULL;
    #else
        Point* open_points[30];
        for (size_t i = 0; i < 30; i++) open_points[i] = NULL;
    #endif
    

    if(compare_points(current, target)){
        //this means that we are already at our target
        push(current, result);
        return;
    }

    //add the current to open_points
    push(current, open_points);
    
    while (is_not_empty(open_points))
    {

        //find the node with the lowest
        //now we need to also consider the g_cost here as well
        //NOTE: f(n) = g(n) + h(n) .... yup
        Point* current_smallest = find_smallest_heuristic_node(open_points, target, g_cost);

        uint8_t currents_x = get_x_point_coord(current_smallest);
        uint8_t currents_y = get_y_point_coord(current_smallest);

        //remove from the open points
        remove_item(current_smallest, open_points);

        //If the current_smallest is the target node, we have reached our target... Yay
        //so we reconstruct path from g_cost array
        if(compare_points(current_smallest, target)) {

            uint8_t x = get_x_point_coord(current_smallest);
            uint8_t y = get_y_point_coord(current_smallest);

            while(g_cost[x][y] != 0)
            {
                Point* p = create_point(x,y);
                push(p, result);

                bool found = false;

                for(int8_t i = -1; i <= 1 && !found; i++)
                for(int8_t j = -1; j <= 1; j++)
                {

                    if(!get_grid_state(x+i, y+j)) continue;

                    //ignore [0][0], that is our current spot
                    if (i == 0 && j == 0) continue;

                    //ignore diagonals too
                    if (i != 0 && j != 0) continue;

                    int16_t neighbour_x = x+i;
                    int16_t neighbour_y = y+j;

                    //if it is a lower cost, we are on the right path backwards
                    if(g_cost[neighbour_x][neighbour_y] == g_cost[x][y]-1)
                    {
                        //so the new x and y would be the path of our previous 'neighbour' we came from
                        x = neighbour_x;
                        y = neighbour_y;
                        found = true;
                        break; //go back out to while
                    }
                }
                if(!found) break;
            }
            //because we work backwards, we would need to reverse the list so feed can properly get the path forwards
            free(current_smallest);
            push(current, result);
            reverse_points(result);
            free_arr(open_points);
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
                //FLAG: NEEDS TO BE FIXED

                int nx = (int)get_x_point_coord(current_smallest) + i;
                int ny = (int)get_y_point_coord(current_smallest) + j;

                if (nx < 0 || ny < 0 || nx >= GRID_ROW_COUNT || ny >= GRID_COL_COUNT)
                    continue;
                
                //check if the grid position is a wall
                if(is_grid_state(nx, ny, cell_wall)) continue;

                //the g_cost of the current smallest is the g_cost of the current smallest's parent + 1 
                //as we are moving one step from the parent to the current smallest
                //hopefully this makes sense
                uint8_t tentative_g = g_cost[currents_x][currents_y] + 1;

                uint8_t neighbour_x = nx;
                uint8_t neighbour_y = ny;


                //obvivously if the neighbour has a g_cost that is greater than or equal to the g_cost of the current smallest, 
                //then we ignore it as it is not a better path
                if (tentative_g >= g_cost[neighbour_x][neighbour_y]) continue;

                //as all the checks have passed, we will now update the g_cost of the neighbour to be the tentative g_cost
                g_cost[neighbour_x][neighbour_y] = tentative_g;

                Point* temp_neighbour = create_point(
                    neighbour_x,
                    neighbour_y
                );

                //just add the neighbour to the open list to be checked in the next iteration
                //but check first if open points is full, 
                //if it is, don't worry, we return, trace path and then come back to trace the rest of the path
                //it does not have to be the full path at all times and we have to save space on the microcontroller 
                if (get_list_size(open_points) >= MAXARRSIZE) {
                    free(temp_neighbour);
                    free_arr(open_points);
                    return;
                };
                if (!search_item(temp_neighbour,open_points))
                {
                    push(temp_neighbour, open_points);
                }
                else
                {
                    free(temp_neighbour);
                }
                
                temp_neighbour = NULL; // open points owns temp_neighbour now
            }
        }

        free(current_smallest);
    }
    //free the open points, closed points might be freed by the user of this function
    free_arr(open_points);

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

    int8_t _heuristic_val_x = get_x_point_coord(current) - get_x_point_coord(target);

    int8_t _heuristic_val_y = get_y_point_coord(current) - get_y_point_coord(target);

    if (_heuristic_val_x < 0) _heuristic_val_x = -_heuristic_val_x;
    if (_heuristic_val_y < 0) _heuristic_val_y = -_heuristic_val_y;
    int8_t _heuristic_val = _heuristic_val_x + _heuristic_val_y;
    
    return (uint8_t) _heuristic_val;
}

//This algorithm calculates the smallest heuristic node in the a list (most likely the open list)
Point* find_smallest_heuristic_node(Point* list[], const Point* target, const uint8_t g_cost[][GRID_COL_COUNT]){
    uint16_t smallest_heuristic_f = g_cost[get_x_point_coord(list[0])][get_y_point_coord(list[0])] + calculate_heuristics_h(list[0], target);
    Point* smallest_heuristic_point = list[0];
    for (uint8_t i = 1; i < get_list_size(list); i++)
    {
        if (list[i]){
            uint8_t current_heuristic = calculate_heuristics_h(list[i], target);
            uint8_t current_g = g_cost[get_x_point_coord(list[i])][get_y_point_coord(list[i])];
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