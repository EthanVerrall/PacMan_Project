#ifndef ARR_H

#define ARR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "point.h"
#define ARRHELPERS
#define MAXARRSIZE 50

//This function assumes the list is arranged and there are no NULL spaces between items
bool is_not_empty(Point* list[]);

Point* pop(Point* list[]);

uint8_t get_list_size(Point* list[]);

bool push(const Point* item, Point* list[]);

bool search_item(const Point* item, Point* list[]);

bool remove_item(const Point* item, Point* list[]);

void free_arr(Point* list[]);

void reverse_points(Point* list[]);

#endif //!ARR_H