#ifndef ALGO_H
#define ALGO_H

#define MAX_PATH_STORE 30

#include "../point.h"
#include "../grid.h"
#include <stdint.h> 
#include <math.h>
#include "../../src/util/arr.c"

/** 
 * This path tracing uses the A* algorithm to check the 
 * 
 * 
 *  NOTE: Important Information
 * REMEMBER TO FREE THE ARRAY RETURNED BY THE A STAR ALGORITHM
*/
Point* trace_path_a_star(const Point* current,const Point* target);

//since a* works, we decided to not need this function.... 
//The definition remains in the case where we would want to use later
//Point* trace_path_dfs(const Point* current,const Point* target);

/** 
 * Calculates the grid using Manhattan distance
*/
uint8_t calculate_heuristics_h(const Point* current, const Point* target);


Point* find_smallest_heuristic_node(Point* list[], const Point* target, const uint8_t g_cost[][GRID_COL_COUNT]);
#endif //!ALGO_H