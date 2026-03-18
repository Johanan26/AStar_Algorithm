#include "AStar.h"
#include "Display.h"
#include "Grid.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

void runRandomTest(int rows, int cols, int obstaclePercent) {
    Grid grid(rows, cols);
    grid.randomFill(obstaclePercent);
    grid.randomiseEndpoints();

    std::vector<Point> path = AStar::findPath(grid);

    std::cout << "\n========================================\n";
    std::cout << "Test case: " << rows << "x" << cols
        << ", obstacle density = " << obstaclePercent << "%\n";
    Display::render(grid, path);
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "=== A* Pathfinding Project ===\n";

    // General test
    runRandomTest(6, 8, 30);

    // Edge case: denser obstacle map
    runRandomTest(6, 8, 45);

    return 0;
}