#pragma once
#include "Point.h"
#include <vector>

class Grid {
public:
    Grid(int rows, int cols);

    void randomFill(int obstaclePercent = 30);
    void randomiseEndpoints();

    bool isWalkable(int r, int c) const;
    bool isInside(int r, int c) const;

    int rows() const { return rows_; }
    int cols() const { return cols_; }

    Point start() const { return start_; }
    Point end() const { return end_; }

    int cell(int r, int c) const { return matrix_[r][c]; }

    void setCell(int r, int c, int value);
    void setStart(const Point& p);
    void setEnd(const Point& p);

private:
    int rows_;
    int cols_;
    Point start_;
    Point end_;
    std::vector<std::vector<int>> matrix_;
};