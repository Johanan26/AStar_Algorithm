#include "Point.h"
#include <cstdlib>

Point::Point(int r, int c) : row(r), col(c) {}

bool Point::operator==(const Point& other) const {
    return row == other.row && col == other.col;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

int manhattanDistance(const Point& a, const Point& b) {
    return std::abs(a.row - b.row) + std::abs(a.col - b.col);
}

int fCost(int g, int h) {
    return g + h;
}