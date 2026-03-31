#include "../include/utils/point.h"

Point* create_point(const uint8_t x, const uint8_t y) {

    Point* const new_point = calloc(1, sizeof(Point));

    if (new_point) {
        new_point->x = x;
        new_point->y = y;

        return new_point;
    }
    else {

        return NULL;
    }
}

Point* create_deep_copy(const Point* const struct_point) {

    if(!struct_point) {

        return NULL;
    }

    Point* const new_point = calloc(1, sizeof(Point));

    if (new_point) {
        new_point->x = struct_point->x;
        new_point->y = struct_point->y;

        return new_point;
    }
    else {

        return NULL;
    }
}

Point create_deep_copy_stack(const Point* const struct_point) {

    if (!struct_point) {

        Point invalid_point = {INVALID_POINT, INVALID_POINT};

        return invalid_point;
    }

    Point new_point;
    new_point.x = struct_point->x;
    new_point.y = struct_point->y;

    return new_point;
}

bool copy_point_values(Point* const dest_point, const Point* const source_point) {

    if (dest_point && source_point) {

        dest_point->x = source_point->x;
        dest_point->y = source_point->y;

        return true;
    } 
    else {

        return false;
    }
}

bool set_point_coord(const uint8_t x, const uint8_t y, Point* const struct_point) {

    if (!struct_point) {

        return false;
    } 
    else {
        struct_point->x = x;
        struct_point->y = y;
        return true;
    }
}

bool move_point(const int8_t x, const int8_t y, Point* const struct_point) {

    if (!struct_point) {

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
        return false;
    }
}

bool is_point_valid(const Point* const struct_point){
    if (struct_point)
    {
        if (struct_point->x == INVALID_POINT || struct_point->y == INVALID_POINT) return false;

        return true;
    }

    return false;
    
}

Point* destroy_point(Point* struct_point) {

    free(struct_point);
    return NULL;
}