#ifndef POINT_H
#define POINT_H
#include <stdint.h>
#include <stdbool.h>

/*  
    Struct for point, will be used for all elements in the program.
    Ghosts and pacman will have a point, board will have many points.

    uint8_t x;
    uint8_t y;
*/
typedef struct Point Point;


//Creating a new point
//Function returns null if Point creation fails, otherwise address returned
Point* create_point(const uint8_t x, const uint8_t y);

//Updates both x and y coordinate for the point
bool set_point_coord(const uint8_t x, const uint8_t y, Point* const struct_point);

//Updates x coordinate for the point
bool set_x_point_coord(const uint8_t x, Point* const struct_point);

//Updates y coordinate for the point
bool set_y_point_coord(const uint8_t y, Point* const struct_point);

//Returns coordinate x of point
uint8_t get_x_point_coord(const Point* const struct_point);

//Returns coordinate y of point
uint8_t get_y_point_coord(const Point* const struct_point);

//Updates point by specified amount
//Use this function to update movement for pacMan and Ghosts and...
bool move_point(const uint8_t x, const uint8_t y, Point* const struct_point);

//Compares both x and y values between two points. 
//Returns false if not Identical 
bool compare_points(const Point* const struct_point_1, const Point* const struct_point_2);

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