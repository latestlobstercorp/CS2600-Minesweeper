# include "Board.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct Board {
    int **board;
    int size;
};

struct Board *createBoard(int size) {
    struct Board *b = malloc(sizeof(struct Board));
    b->size = size;
    b->board = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        b->board[i] = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            b->board[i][j] = 0; // Initialize all cells to 0 (empty)
        }
    }
    return b;
}

void printBoard(struct Board *b) {
    for (int i = 0; i < b->size; i++) {
        for (int j = 0; j < b->size; j++) {
            if (b->board[i][j] == 0) { // 0 represents an empty cell
                printf("[]");
            } else if (b->board[i][j] == 1) { // 1 represents a revealed cell
                printf("-");
            } else if (b->board[i][j] == 2) { // 2 represents a mine
                printf("X"); 
            }
        }
        printf("\n");
    }
}

void initializeMines(struct Board *b, int numMines) {
    int placedMines = 0;
    while (placedMines < numMines) {
        int x = rand() % b->size;
        int y = rand() % b->size;
        if (b->board[x][y] == 0) { // If the cell is empty
            b->board[x][y] = 2; // Place a mine (2)
            placedMines++;
        }
    }
}

int countMines(struct Board *b, int row, int col) {
    int count = 0;
    int xVal[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int yVal[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for(int i = 0; i < 8; i++) {
        int checkRow = row + xVal[i];
        int checkCol = col + yVal[i];

        if((checkRow >= 0 && checkRow < b->size) 
        && (checkCol >= 0 && checkCol < b->size)) {
            if(b->board[checkRow][checkCol] == 2) {
                count++;
            }
        }
    }
    
    return count;
}