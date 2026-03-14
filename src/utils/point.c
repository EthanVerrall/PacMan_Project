#include "../include/utils/point.h"
#include "../include/serial.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

struct Point {

    uint8_t x;
    uint8_t y;
};

Point* create_point(const uint8_t x, const uint8_t y) {

    Point* new_point = calloc(1, sizeof(Point));

    if (new_point) {
        new_point->x = x;
        new_point->y = y;

        return new_point;
    }
    else {

        eputs("Error - failed to create Point. Calloc failed, function returned NULL.\r\n") ;
        return NULL;
    }
}

bool set_point_coord(const uint8_t x, const uint8_t y, Point* const struct_point) {

    if (!struct_point) {

        eputs("Error - assigning values to a Point that is NULL, function aborted.\r\n");
        return false;
    } 
    else {
        struct_point->x = x;
        struct_point->y = y;
        return true;
    }
}

bool set_x_point_coord(const uint8_t x, Point* const struct_point) {

    if (!struct_point) {

        eputs("Error - assigning x value to a Point that is NULL, function aborted.\r\n");
        return false;
    } 
    else {
        struct_point->x = x;
        return true;
    }
}

bool set_y_point_coord(const uint8_t y, Point* const struct_point) {

    if (!struct_point) {

        eputs("Error - assigning y value to a Point that is NULL, function aborted.\r\n");
        return false;
    } 
    else {
        struct_point->y = y;
        return true;
    }
}

uint8_t get_x_point_coord(const Point* const struct_point) {

    if (!struct_point) {

        eputs("Error - Trying to return x value for a NULL POINT. 255 was returned.\r\n");
        return INVALID_POINT;
    }

    return struct_point->x;
}

uint8_t get_y_point_coord(const Point* const struct_point) {

    if (!struct_point) {

        eputs("Error - Trying to return y value for a NULL POINT. 255 was returned.\r\n");
        return INVALID_POINT;
    }
    return struct_point->y;
}

bool move_point(const int8_t x, const int8_t y, Point* const struct_point) {

    if (!struct_point) {

        eputs("Error - trying to moving a Point that is NULL, function aborted.\r\n");
        return false; 
    } 
    else {
        
        struct_point->x += x;
        struct_point->y += y;
        return true;
    }
}

bool compare_points(const Point* const struct_point_1, const Point* const struct_point_2) {

    if (struct_point_1 && struct_point_2) {

        if ( (struct_point_1->x == struct_point_2->x) && (struct_point_1->y == struct_point_2->y) ) {

            return true;
        }
        
        return false;
    } 
    else {

        if (!struct_point_1 && !struct_point_2) 
        eputs("Both of your points were invalid, aka NULL or undefined behaviour. Compare returned false.\r\n");
        else if (!struct_point_1)
        eputs("Point A was invalid, aka NULL or undefined behaviour. Compare returned false.\r\n");
        else
        eputs("Point B was invalid, aka NULL or undefined behaviour. Compare returned false.\r\n");
        
        return false;
    }
}

Point* destroy_point(Point* struct_point) {
    
    if (!struct_point) {

        eputs("Your point was already NULL, nothing to free.\r\n");
    }

    free(struct_point);
    return NULL;
}