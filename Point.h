#pragma once

struct Point {
    int row;
    int col;

    Point(int r = 0, int c = 0);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

int manhattanDistance(const Point& a, const Point& b);
int fCost(int g, int h);