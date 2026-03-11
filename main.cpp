#include "AStar.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "=== A* Pathfinding on a Random Binary Matrix ===\n";

    const int ROWS = 6;
    const int COLS = 8;

    BinaryMatrix grid(ROWS, COLS);
    grid.generateRandomMatrix();
    grid.randomizeStartEnd();
    grid.solveAndDisplay();

    return 0;
}