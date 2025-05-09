/* Members:
- Zoey Yung
- Josephine Villar
- Thy Hoang
- Shane Sawyer
- Kristopher Walsh
*/
# include "Board.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <stdbool.h>

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
    printf("\nCurrent Board:\n\n");
    for (int i = 0; i < b->size; i++) {
        for (int j = 0; j < b->size; j++) {
            int val = b->board[i][j];
            if (val == 0 || val == 2) { // 0 represents an empty cell 2 represents a mine
                printf("[ ] "); // unrevealed cell or hidden mine
            } else if (val >= 10 && val <= 18) {
                printf(" %d  ", val - 10); // revealed safe cell with mine count
            } else if (val == 3) {
                printf(" X  "); // revealed mine (only after player hits it)
            }
        }
        printf("\n");
    }
    printf("\n");
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

//Make So It Recursively Digs For Empty Cells
bool revealCell(struct Board *b, int row, int col) {
    if (b->board[row][col] == 2) { // 2 = mine
        b->board[row][col] = 3; // 3 = revealed mine
        return true; // Mine hit
    } else if (b->board[row][col] == 0) { // 0 = empty cell
        int count = countMines(b, row, col);
        b->board[row][col] = 10 + count; // Use 10+count to represent revealed safe cell with count
    }
    return false;
}

bool isGameOver(struct Board *b) {
    for (int i = 0; i < b->size; i++) {
        for (int j = 0; j < b->size; j++) {
            if (b->board[i][j] == 0) {
                return false; // still unrevealed safe cells
            }
        }
    }
    return true;
}

int main() {
    int boardSize;
    int numMines;
    int row, col;

    printf("%s\n", "Welcome to MINESWEEPER");

    printf("%s\n", "Please Enter Width of Board, i.e. 5 :");
    scanf("%d", &boardSize);
    printf("\n");

    struct Board *b = createBoard(boardSize);
    numMines = (int)(boardSize*boardSize * 0.15);

    initializeMines(b, numMines);
    
    bool hitMine = false;

    while(!hitMine && !isGameOver(b)) {
        printBoard(b);

        printf("Choose a cell to reveal (Format x y i.e. 1 5): ");
       
       int ch;
        if (scanf("%d %d", &row, &col) != 2) {
        printf("Invalid input format please enter two integers.\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        continue;
    }

        //Convert to 0-based index
        row -= 1;
        col -= 1;
        
        if(row<0 || row>=boardSize || col<0 || col>=boardSize) {
            printf("Invalid Input. Try Again.\n");
            continue;
        }
        hitMine = revealCell(b, row, col);
    }

    if (hitMine) {
        printBoard(b);
        printf("Game Over! You hit a mine.\n");
    } else {
        printf("Congratulations! You cleared the board.\n");
    }
    
    // Free allocated memory 
    for (int i = 0; i < boardSize; i++) {
        free(b->board[i]);
    }
    free(b->board);
    free(b);

    return 0;
}
