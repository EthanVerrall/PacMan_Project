#include "../include/utils/point.h"

struct Point {

    uint8_t x;
    uint8_t y;
};

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


bool copy_point_x(Point* const dest_point, const Point* const source_point) {

    if (dest_point && source_point) {

        dest_point->x = source_point->x;

        return true;
    } 
    else {

        return false;
    }
}

bool copy_point_y(Point* const dest_point, const Point* const source_point) {

    if(dest_point && source_point) {

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

bool set_x_point_coord(const uint8_t x, Point* const struct_point) {

    if (!struct_point) {

        return false;
    } 
    else {
        struct_point->x = x;
        return true;
    }
}

bool set_y_point_coord(const uint8_t y, Point* const struct_point) {

    if (!struct_point) {

        return false;
    } 
    else {
        struct_point->y = y;
        return true;
    }
}

uint8_t get_x_point_coord(const Point* const struct_point) {

    if (!struct_point) {

        return INVALID_POINT;
    }

    return struct_point->x;
}

uint8_t get_y_point_coord(const Point* const struct_point) {

    if (!struct_point) {

        return INVALID_POINT;
    }
    return struct_point->y;
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

Point* destroy_point(Point* struct_point) {

    free(struct_point);
    return NULL;
}