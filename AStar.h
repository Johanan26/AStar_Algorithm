#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

// ---------------------------------------------------------------------------
// Grid coordinate type
// ---------------------------------------------------------------------------
struct Point {
    int row;
    int col;

    bool operator==(const Point& other) const noexcept {
        return row == other.row && col == other.col;
    }
};

// ---------------------------------------------------------------------------
// A* heuristic and cost helpers
// h(n) – Manhattan distance (no diagonal movement allowed)
// f(n) = g(n) + h(n)
// ---------------------------------------------------------------------------
constexpr int manhattanDistance(const Point& a, const Point& b) noexcept {
    return (a.row > b.row ? a.row - b.row : b.row - a.row)
        + (a.col > b.col ? a.col - b.col : b.col - a.col);
}

constexpr int f_cost(int g, int h) noexcept { return g + h; }

// ---------------------------------------------------------------------------
// BinaryMatrix
//   0 = free cell   1 = obstacle
// ---------------------------------------------------------------------------
class BinaryMatrix {
public:
    BinaryMatrix(int rows, int cols);

    // Fill every cell randomly with 0 or 1
    void generateRandomMatrix();

    // Pick two distinct free cells as start (S) and end (E)
    void randomizeStartEnd();

    // Run A*, then print the grid + per-step cost table
    void solveAndDisplay() const;

    // Plain display (no colour, no path)
    void displayMatrix() const;

    // Getters
    int getRows() const;
    int getCols() const;
    std::vector<std::vector<int>> getMatrix() const;

private:
    std::vector<std::vector<int>> matrix;
    int rows;
    int cols;
    Point start;
    Point end;

    // Returns the optimal path [start … end], or empty if no path exists.
    // Each cell costs 1 to enter (uniform-cost grid).
    std::vector<Point> runAStar() const;
};

#endif // ASTAR_H