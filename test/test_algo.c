#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "../include/grid.h"
#include "../include/behaviours/algo.h"
#include "../include/utils/point.h"
#include "../include/utils/arr.h"       

#ifdef MAX_PATH_STORE
    #define TEST_PATH_CAPACITY MAX_PATH_STORE
#else
    #define TEST_PATH_CAPACITY 30
#endif

/* Visual symbols for terminal output */
#define SYMBOL_WALL      '#'
#define SYMBOL_BLANK     ' '
#define SYMBOL_PELLET    '.'
#define SYMBOL_POWERUP   'O'
#define SYMBOL_GATE      '='
#define SYMBOL_CHERRY    'C'
#define SYMBOL_PATH      '*'
#define SYMBOL_START     'S'
#define SYMBOL_TARGET    'T'

/* 
    Decide whether a cell is traversable for pathfinding.
    IMPORTANT:
    The algo currently skips only walls explicitly.
    It also uses get_grid_state(...) == 0 as "invalid/out of bounds",
    which is slightly dangerous because cell_blank might be 0 in some designs.
    
    So this helper tries to be sane:
    - reject walls
    - allow everything else except out-of-bounds (handled by caller)
*/
static bool is_walkable_cell(uint8_t row, uint8_t col)
{
    if (row >= GRID_ROW_COUNT || col >= GRID_COL_COUNT) return false;

    if (is_grid_state(row, col, cell_wall)) return false;

    return true;
}

/* Get a random walkable point */
static Point* get_random_walkable_point(void)
{
    while (true)
    {
        uint8_t row = (uint8_t)(rand() % GRID_ROW_COUNT);
        uint8_t col = (uint8_t)(rand() % GRID_COL_COUNT);

        if (is_walkable_cell(row, col))
        {
            return create_point(row, col);
        }
    }
}

/* Convert grid cell to a printable char */
static char cell_to_char(uint8_t row, uint8_t col)
{
    uint8_t state = get_grid_state(row, col);

    /*
        If the grid uses bitmasks for actors layered on top of base tiles,
        has_grid_state(...) is safer than is_grid_state(...) for those.
    */

    if (is_grid_state(row, col, cell_wall))      return SYMBOL_WALL;
    if (is_grid_state(row, col, cell_gate))      return SYMBOL_GATE;
    if (is_grid_state(row, col, cell_power_up))  return SYMBOL_POWERUP;
    if (is_grid_state(row, col, cell_cherry))    return SYMBOL_CHERRY;
    if (is_grid_state(row, col, cell_pellet))    return SYMBOL_PELLET;

    /* fallback */
    (void)state;
    return SYMBOL_BLANK;
}

/* Print grid with path overlay */
static void print_grid_with_path(const Point* start, const Point* target, Point* path[])
{
    for (uint8_t row = 0; row < GRID_ROW_COUNT; ++row)
    {
        for (uint8_t col = 0; col < GRID_COL_COUNT; ++col)
        {
            Point* temp = create_point(row, col);
            char out = cell_to_char(row, col);

            if (compare_points(temp, start))
            {
                out = SYMBOL_START;
            }
            else if (compare_points(temp, target))
            {
                out = SYMBOL_TARGET;
            }
            else if (search_item(temp, path))
            {
                out = SYMBOL_PATH;
            }

            putchar(out);
            free(temp);
        }
        putchar('\n');
    }
}

/* Optional: print path coordinates for debugging */
static void print_path_coords(Point* path[])
{
    printf("\nPath coordinates:\n");

    for (size_t i = 0; i < TEST_PATH_CAPACITY; ++i)
    {
        if (!path[i]) break;

        printf("  [%zu] (%u, %u)\n",
               i,
               get_x_point_coord(path[i]),
               get_y_point_coord(path[i]));
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));

    if (!create_reset_grid())
    {
        fprintf(stderr, "Failed to create/reset grid.\n");
        return 1;
    }

    Point* start = get_random_walkable_point();
    Point* target = NULL;

    do
    {
        if (target) free(target);
        target = get_random_walkable_point();
    }
    while (compare_points(start, target));

    /* Prepare result path array */
    Point* path[TEST_PATH_CAPACITY];
    for (size_t i = 0; i < TEST_PATH_CAPACITY; ++i)
    {
        path[i] = NULL;
    }

    printf("Start : (%u, %u)\n", get_x_point_coord(start), get_y_point_coord(start));
    printf("Target: (%u, %u)\n\n", get_x_point_coord(target), get_y_point_coord(target));

    /* Run A* */
    trace_path_a_star(start, target, path);

    /* Print */
    print_grid_with_path(start, target, path);
    print_path_coords(path);

    /* Cleanup */
    free(start);
    free(target);

    /*
        We could use free_arr here, but might just be a bit safer
    */
    for (size_t i = 0; i < TEST_PATH_CAPACITY; ++i)
    {
        if (path[i])
        {
            free(path[i]);
            path[i] = NULL;
        }
    }

    destroy_grid();
    return 0;
}
