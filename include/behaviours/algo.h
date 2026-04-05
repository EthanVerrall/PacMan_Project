#ifndef ALGO_H
#define ALGO_H

#define MAX_PATH_STORE 50

#include "../include/utils/point.h"
#include "../include/grid.h"
#include "../include/utils/arr.h"
#include <stdint.h> 
#include <math.h>

/** 
 * This path tracing uses the A* algorithm to check the path from the current point to the target point, 
 * and returns an array of points that represents the path from the current point to the target point,
 * 
 * @param current the current point that we are trying to find a path from, which is a Point struct containing the x and y coordinates of the current point on the grid
 * @param target the target point that we are trying to find a path to
 * @param result an array of points that will be filled with the path from the current point to the target point
 * The result array is assumed to have a size of at least MAX_PATH_STORE, to prevent overflow and it works without undefined behaviours
 * @return an array of points that represents the path from the current point to the target point, which is filled in the result parameter
*/
void trace_path_a_star(const Point* current,const Point* target, Point result[]);

//since a* works, we decided to not need this function.... 
//The definition remains in the case where we would want to use later
//Point* trace_path_dfs(const Point* current,const Point* target);

/** 
 * Calculates the heuristics using Manhattan distance formula
 * The Manhattan distance is the sum of the absolute differences of the x and y coordinates of the two points
 * It is used in the A* algorithm to estimate the cost of reaching the target from the current point,
 * and since it never overestimates the cost of reaching the target, 
 * it guarantees that the A* algorithm will find the optimal path to the target if one exists
 */
uint8_t calculate_heuristics_h(const Point* current, const Point* target);

/** 
 * Finds the smallest heuristic node in a list of points, which is usually the open list in the a* algorithm
 * 
 * The heuristic value is calculated using the calculate_heuristics_h function, and the g_cost is added to it to get the f_cost, #
 * which is used to determine the smallest heuristic node
 * A smaller heuristic value means that the node is closer to the target, and therefore is more likely to be the next node in the path to the target
 *
 * @param list a list of points, which is usually the open list in the a* algorithm, which contains the nodes that are yet to be explored
 * @param target the target point that we are trying to reach, which is used to calculate the heuristic value of the nodes in the list
 * @param g_cost a 2D array that contains the g_cost of each node on the grid, which is used to calculate the f_cost of the nodes in the list
 * 
 * @returns the point in the list that has the smallest heuristic value, most likely to be the next node in the path to the target
 *
*/
Point find_smallest_heuristic_node(Point list[], const Point* target, const uint8_t g_cost[][GRID_COL_COUNT]);
#endif //!ALGO_H