# include "Board.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main() {
    int size = 5; // Size of the board
    int numMines = 3; // Number of mines to place

    // Create the board
    struct Board *b = createBoard(size);

    // // Initialize mines
    // initializeMines(b, numMines);

    // Print the board
    printBoard(b);

    // Free memory (not shown here for brevity)

    return 0;
}