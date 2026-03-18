#pragma once

#include "Grid.h"
#include "Point.h"
#include <vector>

class AStar {
public:
    static std::vector<Point> findPath(const Grid& grid);
};