#ifndef POINT_H
#define POINT_H
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define INVALID_POINT 255

/*  
    Struct for point, will be used for all elements in the program.
    Ghosts and pacman will have a point, board will have many points.

    A point correlates directly to grid indexing.
    For example: grid[x_point][y_point] 

    Therefore a valid point is (0,0) to (20,16). Consider outside this range as invalid and undefined behaviour!

    uint8_t x;
    uint8_t y;
*/

typedef struct {

    uint8_t x;
    uint8_t y;

} Point;

//Creating a heap allocated point
//Function returns null if Point creation fails, otherwise address returned
Point* create_point(const uint8_t x, const uint8_t y);

//Creates a deep copy of one point and returns the new deep copy
Point* create_deep_copy(const Point* const struct_point);

//Copys a points values and returns the copy
Point create_deep_copy_stack(const Point* const struct_point);

//Updates both x and y coordinate for the point
bool set_point_coord(const uint8_t x, const uint8_t y, Point* const struct_point);

//Deep copys another points values into yours
bool copy_point_values(Point* const dest_point, const Point* const source_point);

//Updates point by specified amount
//Use this function to update movement for pacMan and Ghosts and...
bool move_point(const int8_t x, const int8_t y, Point* const struct_point);

//Compares both x and y values between two points. 
//Returns false if not Identical 
bool compare_points(const Point* const struct_point_1, const Point* const struct_point_2);

bool is_point_valid(const Point* const struct_point);

/*
Warning!!!
-
The following function frees the point that was passed as the parameter.
Afterwards the function returns NULL.

Ensure you assign this NULL value to the same pointer that was pointing to the point you 
were freeing in the passed parameter.

Failure to follow will result in having your point that you did not free become dangling.
*/
Point* destroy_point(Point* struct_point);

#endif //POINT_H