#include "Grid.h"
#include <cstdlib>
#include <stdexcept>
#include <vector>

Grid::Grid(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(rows, std::vector<int>(cols, 0)) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("Grid dimensions must be at least 1x1");
    }
}

void Grid::randomFill(int obstaclePercent) {
    if (obstaclePercent < 0 || obstaclePercent > 100) {
        throw std::invalid_argument("Obstacle percentage must be between 0 and 100");
    }

    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            matrix_[r][c] = (std::rand() % 100 < obstaclePercent) ? 1 : 0;
        }
    }
}

void Grid::randomiseEndpoints() {
    std::vector<Point> freeCells;

    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            if (matrix_[r][c] == 0) {
                freeCells.push_back(Point(r, c));
            }
        }
    }

    if (freeCells.size() < 2) {
        matrix_[0][0] = 0;
        matrix_[rows_ - 1][cols_ - 1] = 0;
        freeCells.clear();
        freeCells.push_back(Point(0, 0));
        freeCells.push_back(Point(rows_ - 1, cols_ - 1));
    }

    int startIndex = std::rand() % static_cast<int>(freeCells.size());
    int endIndex = startIndex;

    while (endIndex == startIndex) {
        endIndex = std::rand() % static_cast<int>(freeCells.size());
    }

    start_ = freeCells[startIndex];
    end_ = freeCells[endIndex];
}

bool Grid::isInside(int r, int c) const {
    return r >= 0 && r < rows_ && c >= 0 && c < cols_;
}

bool Grid::isWalkable(int r, int c) const {
    return isInside(r, c) && matrix_[r][c] == 0;
}

void Grid::setCell(int r, int c, int value) {
    if (!isInside(r, c)) {
        throw std::out_of_range("Cell position is outside the grid");
    }

    if (value != 0 && value != 1) {
        throw std::invalid_argument("Cell value must be 0 or 1");
    }

    matrix_[r][c] = value;
}

void Grid::setStart(const Point& p) {
    if (!isWalkable(p.row, p.col)) {
        throw std::invalid_argument("Start point must be on a free cell");
    }
    start_ = p;
}

void Grid::setEnd(const Point& p) {
    if (!isWalkable(p.row, p.col)) {
        throw std::invalid_argument("End point must be on a free cell");
    }
    end_ = p;
}