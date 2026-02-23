#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AStar.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "=== Random Binary Matrix with Random Start/End ===\n\n";

    const int ROWS = 6;
    const int COLS = 8;

    BinaryMatrix binMatrix(ROWS, COLS);
    binMatrix.generateRandomMatrix();
    binMatrix.randomizeStartEnd();
    binMatrix.displayMatrix();

    return 0;
}