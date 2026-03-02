#include "../../include/behaviours/algo.h"

Point* trace_path_a_star(const Point* current, const Point* target, const Grid* board){

    //check for nullness
    if(!current || !target) return NULL;

    if(compare_points(current, target)){
        //this means that we are already at our target
        return current;
    }

    //track our open and closed points
    //this is just in the case that max path is changed maybe or removed
    //so that we do not scratch our heads over errors later
    #ifdef MAX_PATH_STORE
        const Point* open_points[MAX_PATH_STORE];
        const Point* closed_points[MAX_PATH_STORE];
    #else
        const Point* open_points[10];
        const Point* closed_points[10];
    #endif

    //Because we are working with arrays and cannot pop or push
    //I will create a sort of placeholder to remove and resize and check the size
    //two numbers storing current size of the array
    uint8_t open_arr_capacity = 0;
    uint8_t closed_arr_capacity = 0;

    //determine our heuristic
    uint8_t heuristic = calculate_heuristics_h(current, target);


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