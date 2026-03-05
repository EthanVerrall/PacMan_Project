/** 
 * This is just a helper function, especially for dfs and a* algorithms,
 * to work with arrays as if they were lists
*/

#include <stdbool.h>
#include <stdint.h> 
#include "../include/point.h"

#define ARRHELPERS
#define MAXARRSIZE 30

//This function assumes the list is arranged and there are no NULL spaces between items
bool is_not_empty(Point* list[]){
    if (list[0])
        return true;
    else
        return false;
}

Point* pop(Point* list[]){
    //remove the last item in the list
    uint8_t i = 0;
    while (list[i])
        i++;
    Point* temp_point = list[i];
    list[i] = NULL; //We cannot free at this point, since we are still returning the pointer to the memory address.
    //the user of this function, would, in their code, free this item after using it
    return temp_point;
}

uint8_t get_list_size(Point* list[]){
    uint8_t i = 0;
    while (list[i])
        i++;
    return i;
}

bool push(Point* item, Point* list[]){
    if (get_list_size(list) >= MAXARRSIZE){
        printf("Array is full");
        return false;
    }
    if (item == NULL)
    {
        printf("item being passed is a null item, it would be a waste to add");
        return false;
    }

    uint8_t i = 0;
    while (list[i])
        i++;
    
    list[i + 1] = item;
    return true;
}

bool search_item(Point* item, Point* list[]){
    uint8_t i = 0;
    while (list[i])
    {
        if (compare_points(item, list[i])) return true;   
    }

    return false;
}

bool remove_item(Point* item, Point* list[]){
    uint8_t i = 0;
}

bool free_arr(Point* list[]){
    uint8_t i = 0;
    while (list[i])
    {
        free(list[i]);
        list[i] = NULL;
    }
}