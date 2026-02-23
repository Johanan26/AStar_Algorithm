#include "AStar.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

// Constructor
BinaryMatrix::BinaryMatrix(int r, int c)
    : rows(r), cols(c), startRow(-1), startCol(-1), endRow(-1), endCol(-1) {
    matrix.resize(rows, std::vector<int>(cols, 0));
}

void BinaryMatrix::generateRandomMatrix() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            matrix[i][j] = std::rand() % 2;
}

void BinaryMatrix::randomizeStartEnd() {
    std::vector<std::pair<int, int>> freeCells;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (matrix[i][j] == 0) freeCells.emplace_back(i, j);

    if (freeCells.empty()) {
        matrix[0][0] = 0;
        freeCells.emplace_back(0, 0);
    }

    int s = std::rand() % static_cast<int>(freeCells.size());
    startRow = freeCells[s].first;
    startCol = freeCells[s].second;

    int e = s;
    if (freeCells.size() > 1) {
        while (e == s) e = std::rand() % static_cast<int>(freeCells.size());
    }
    endRow = freeCells[e].first;
    endCol = freeCells[e].second;
}

void BinaryMatrix::carveManhattanCorridorIfNeeded() {
    int r = startRow;
    int c = startCol;

    while (r != endRow) {
        matrix[r][c] = 0;
        r += (endRow > r) ? 1 : -1;
    }
    while (c != endCol) {
        matrix[r][c] = 0;
        c += (endCol > c) ? 1 : -1;
    }
    matrix[endRow][endCol] = 0;
}

void BinaryMatrix::solveAndDisplay() {
    carveManhattanCorridorIfNeeded();

    // Build L-shaped path (rows first, then cols)
    std::vector<std::pair<int, int>> path;
    int r = startRow, c = startCol;
    path.emplace_back(r, c);

    while (r != endRow) {
        r += (endRow > r) ? 1 : -1;
        path.emplace_back(r, c);
    }
    while (c != endCol) {
        c += (endCol > c) ? 1 : -1;
        path.emplace_back(r, c);
    }

    // Count free cells crossed
    int zerosCrossed = 0;
    for (auto& p : path)
        if (matrix[p.first][p.second] == 0) ++zerosCrossed;

    std::cout << "\nBinary Matrix (" << rows << "x" << cols << "):\n";
    std::cout << "--------------------\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << '\n';
    }
    std::cout << "--------------------\n";
    std::cout << "Path steps: " << (path.size() ? static_cast<int>(path.size()) - 1 : 0) << '\n';
    std::cout << "Free cells crossed: " << zerosCrossed << '\n';
}

void BinaryMatrix::displayMatrix() const {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r == startRow && c == startCol)
                std::cout << "S ";
            else if (r == endRow && c == endCol)
                std::cout << "E ";
            else
                std::cout << matrix[r][c] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

int BinaryMatrix::getRows() const { return rows; }
int BinaryMatrix::getCols() const { return cols; }
std::vector<std::vector<int>> BinaryMatrix::getMatrix() const { return matrix; }