#include "AStar.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed once

    std::cout << "=== Random Binary Matrix with Random Start/End ===\n\n";

    const int ROWS = 6;
    const int COLS = 8;

    BinaryMatrix binMatrix(ROWS, COLS);
    binMatrix.generateRandomMatrix();
    binMatrix.randomizeStartEnd();
    binMatrix.solveAndDisplay();

    return 0;
}