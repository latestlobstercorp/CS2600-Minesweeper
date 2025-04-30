#ifdef BOARD_H
#define BOARD_H

struct Board {
    int **board; // 2D array representing the board
    int size;    // Size of the board (number of rows/columns)
};

struct Board *createBoard(int size); // Function to create a new board
void printBoard(struct Board *b); // Function to print the board
void initializeMines(struct Board *b, int numMines); // Function to initialize mines on the board

#endif // BOARD_H