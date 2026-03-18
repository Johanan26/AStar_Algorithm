#include "Grid.h"
#include "Point.h"
#include <vector>

class Display {
public:
    static void render(const Grid& grid, const std::vector<Point>& path);

private:
    static void printGrid(const Grid& grid, const std::vector<Point>& path);
    static void printCostTable(const Grid& grid, const std::vector<Point>& path);
};