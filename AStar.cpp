#include "project.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

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

}
void BinaryMatrix::carveManhattanCorridorIfNeeded() {
}

void BinaryMatrix::solveAndDisplay() {
}

void BinaryMatrix::displayMatrix() const {
}

int BinaryMatrix::getRows() const { return rows; }
int BinaryMatrix::getCols() const { return cols; }
std::vector<std::vector<int>> BinaryMatrix::getMatrix() const { return matrix; }
