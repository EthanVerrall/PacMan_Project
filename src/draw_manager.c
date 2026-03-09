#include "../include/draw_manager.h"
#include <stdint.h>

void draw_starting_grid () {

    for (uint8_t y_pixel = 0 + HEIGHT_OFFSET; y_pixel < SCREEN_HEIGHT; y_pixel += 8) {

        for (uint8_t x_pixel = 0; x_pixel < SCREEN_WIDTH; x_pixel += 8) {

            uint8_t cell_bitmask = get_grid_state(x_pixel, y_pixel);

            switch (cell_bitmask) {

                case cell_blank:
                case cell
                case
                case
                case
                case
                case
                case
            }
        }
    }
}