/** 
 * This is just a helper function, especially for dfs and a* algorithms,
 * to work with arrays as if they were lists
*/
#include "../include/utils/arr.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#define MAXARRSIZE 50

//This function assumes the list is arranged and there are no NULL spaces between items
bool is_not_empty(Point list[]){
    if (is_point_valid(&list[0]))
        return true;
    else
        return false;
}

Point pop(Point list[]){
    //remove the last item in the list
    uint8_t i = 0;
    while (i < MAXARRSIZE && is_point_valid(&list[0]))
        i++;
    Point temp_point = list[i - 1];
    list[i - 1].x = INVALID_POINT; //We cannot free at this point, since we are still returning the pointer to the memory address.
    list[i - 1].y = INVALID_POINT; //We cannot free at this point, since we are still returning the pointer to the memory address.
    //the user of this function, would, in their code, free this item after using it
    return temp_point;
}

uint8_t get_list_size(Point list[]){
    uint8_t i = 0;
    while (i < MAXARRSIZE && is_point_valid(&list[i]))
        i++;
    return i;
}

bool push(const Point* const item, Point list[]){
    if (get_list_size(list) >= MAXARRSIZE){
       // printf("Array is full");
        return false;
    }
    if (item == NULL)
    {
        //printf("item being passed is a null item, it would be a waste to add");
        return false;
    }

    uint8_t i = 0;
    while (i < MAXARRSIZE && is_point_valid(&list[i]))
        i++;
    
    list[i] = create_deep_copy_stack(item);
    return true;
}

bool search_item(const Point* item, Point list[]){
    uint8_t i = 0;
    while (i < MAXARRSIZE && is_point_valid(&list[i]))
    {
        if (compare_points(item, &list[i])) return true;
        i++; 
    }

    return false;
}

bool remove_item(const Point* item, Point list[]){
    uint8_t i = 0;
    bool found = false;
    while (i < MAXARRSIZE && is_point_valid(&list[i])){
        if (compare_points(&list[i], item))
        {
            found = true;
            break;
        }
        i++;
    }
    if (found)
    {
        //remove the item from the point .... we will use the index later
        list[i].x = INVALID_POINT;
        list[i].y = INVALID_POINT;
        i++; //latent increase as we would be checking for NULLNESS
        //reorder the list
        while (i < MAXARRSIZE && is_point_valid(&list[i])){
            list[i - 1] = list[i];
            i++;
        }
        list[i - 1].x = INVALID_POINT;
        list[i - 1].y = INVALID_POINT;
    }

    //free(item);

    return found; //found_and_removed
    
}

void clear_arr(Point list[]){
    
    for (uint8_t i = 0; i < MAXARRSIZE; ++i)
    {
        list[i].x = INVALID_POINT;
        list[i].y = INVALID_POINT;
    }
}

void reverse_points(Point list[]) {
    uint8_t n = get_list_size(list);

    for(uint8_t i = 0; i < n/2; i++) {
        //perform a swap
        Point temp = list[i];
        list[i] = list[n-i-1];
        list[n-i-1] = temp;
    }
}