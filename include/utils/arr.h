#ifndef ARR_H

#define ARR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "point.h"
#define ARRHELPERS
#define MAXARRSIZE 50

//This function assumes the list is arranged and there are no NULL spaces between items
/** 
 * Checks that the list is not empty and has at least one valid item in it
 * The list is assumed to not be fragmented, meaning that there are no NULL spaces between items, 
 * and that all items are valid until the first invalid item is reached
*/
bool is_not_empty(Point list[]);

/**
 * Like a stack or a vector, `pop()` removes the last item (Point) in the list and returns it,
 * and sets the index of the removed item to be invalid (INVALID_POINT)
 * The list is assumed to not be fragmented, meaning that there are no NULL spaces between items
 */
Point pop(Point list[]);

/**
 * Returns the number of valid items in the list, which is essentially the size of the list
 * As above, the list is assumed to not be fragmented, so if there is any invalid item in the list, 
 * it is assumed that all items after it are also invalid and therefore not counted in the size
 */
uint8_t get_list_size(Point list[]);

/**
 * Adds an item to the end of the list, and returns true if the item was successfully added,
 * and false if the item was not added because the list is full (has reached MAXARRSIZE) or if the item is invalid (INVALID_POINT)
 * If the item was successfully added, it is added to the first index in the list that is invalid (INVALID_POINT)
 */
bool push(const Point* item, Point list[]);

/**
 * Checks for an item in the list, and returns true if the item is found, 
 * and false if the item is not found or if the list is empty.
 */
bool search_item(const Point* item, Point list[]);

/**
 * Removes and item from the list, and returns true if the item was successfully removed,
 * and false if the item was not removed because the item was not found in the list or because the list is empty.
 * Also rearranges the list so that there are no invalid points between valid points, so the array works like a list or vector
 */
bool remove_item(const Point* item, Point list[]);

/** 
 * Sets all items in the list to invalid points (INVALID_POINT), essentially clearing the list and making it empty
*/
void clear_arr(Point list[]);

/** 
 * Reverses the order of the items in the list, so the first item becomes the last item, 
 * and the last item becomes the first item, and so on.
 * 
 * The list is reversed in place, and is checked until the last valid item on the list, 
 * so if the list is fragmented, meaning that there are invalid items between valid items, 
 * the function will only reverse the order of the valid items until the first invalid item is reached, 
 * and will not reverse any items after the first invalid item
*/
void reverse_points(Point list[]);

#endif //!ARR_H