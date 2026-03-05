#ifndef ALGO_H
#define ALGO_H

#define MAX_PATH_STORE 10

#include "../point.h"
#include "../grid.h"
#include <stdint.h> 
#include <math.h>
#include "util/arr.c"

/** 
 * This path tracing uses the A* algorithm to check the 
 * 
 * 
 *  NOTE: Important Information
 * REMEMBER TO FREE THE ARRAY RETURNED BY THE A STAR ALGORITHM
*/
Point* trace_path_a_star(const Point* current,const Point* target,const Grid* board);

Point* trace_path_dfs(const Point* current,const Point* target,const Grid* board);

/** 
 * Calculates the grid using Manhattan distance
*/
uint8_t calculate_heuristics_h(const Point* current, const Point* target);


Point* find_smallest_heuristic_node(Point* list[], const Point* target);
#endif //!ALGO_H