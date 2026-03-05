#include "include/behaviours/algo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define COL 30
#define ROW 30
void create_board(){}

void generate_random_walls(uint8_t board[][COL]){
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            if (rand() % 10 == 0) board[i][j] = 1;
            else board[i][j] = 0;
        }
    }
}

void printBoard(uint8_t board[][COL]){
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            if (board[i][j] == 1)
            {
                printf("&", board[i][j]);
            }
            else
            {
                printf(" ", board[i][j]);
            }
            
        }
        printf("\n");
    }
}

//for testing the algorithm
void test_algo_path(){}

int main(){

    uint8_t board[ROW][COL];
    generate_random_walls(board);
    printBoard(board);
    return 0;
}