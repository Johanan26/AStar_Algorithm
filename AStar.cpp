#include "AStar.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
BinaryMatrix::BinaryMatrix(int r, int c)
    : rows(r), cols(c), start{ 0, 0 }, end{ 0, 0 } {
    matrix.resize(rows, std::vector<int>(cols, 0));
}

// ---------------------------------------------------------------------------
// Matrix generation
// ---------------------------------------------------------------------------
void BinaryMatrix::generateRandomMatrix() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            // ~60% chance of obstacle – makes "no path" scenarios common
            matrix[i][j] = (std::rand() % 10 < 6) ? 1 : 0;
}

// ---------------------------------------------------------------------------
// Pick random start and end from free cells
// ---------------------------------------------------------------------------
void BinaryMatrix::randomizeStartEnd() {
    std::vector<Point> freeCells;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (matrix[i][j] == 0)
                freeCells.push_back({ i, j });

    // Guarantee at least two free cells so a pair can always be chosen
    if (freeCells.size() < 2) {
        matrix[0][0] = 0;
        matrix[rows - 1][cols - 1] = 0;
        freeCells = { {0, 0}, {rows - 1, cols - 1} };
    }

    int s = std::rand() % static_cast<int>(freeCells.size());
    start = freeCells[s];

    int e = s;
    while (e == s)
        e = std::rand() % static_cast<int>(freeCells.size());
    end = freeCells[e];
}

// ---------------------------------------------------------------------------
// A* search
//
// Algorithm outline
// -----------------
// 1. Initialise: put the start node onto the open list with g=0.
// 2. Loop until the open list is empty:
//    a. Pick the open node with the lowest f = g + h  (current).
//    b. If current == goal  →  reconstruct and return the path.
//    c. Move current to the closed list (already evaluated).
//    d. For every walkable 4-directional neighbour of current:
//       - Skip if it is on the closed list.
//       - Compute tentative_g = current.g + 1  (each step costs 1).
//       - If tentative_g is better than the neighbour's known g:
//           * Update the neighbour's g, h, f and record current as its parent.
//           * Add to the open list if not already there.
// 3. If the open list empties without reaching the goal → no path exists.
// ---------------------------------------------------------------------------
std::vector<Point> BinaryMatrix::runAStar() const {
    const int INF = std::numeric_limits<int>::max();

    // Per-cell bookkeeping stored in a 2-D grid for O(1) access
    struct CellData {
        int    g = std::numeric_limits<int>::max();   // best known cost from start
        int    f = std::numeric_limits<int>::max();   // g + h
        Point  parent = { -1, -1 };
        bool   inOpen = false;
        bool   inClosed = false;
    };
    std::vector<std::vector<CellData>> data(rows, std::vector<CellData>(cols));

    // Open list: plain vector – small grids don't need a heap
    std::vector<Point> openList;

    // --- Step 1: seed the open list with the start node ---
    data[start.row][start.col].g = 0;
    data[start.row][start.col].f = manhattanDistance(start, end);
    data[start.row][start.col].inOpen = true;
    openList.push_back(start);

    // 4-directional offsets: up, down, left, right
    constexpr int DR[4] = { -1,  1,  0, 0 };
    constexpr int DC[4] = { 0,  0, -1, 1 };

    // --- Step 2: main loop ---
    while (!openList.empty()) {

        // 2a. Pick the open node with the lowest f cost
        auto bestIt = std::min_element(openList.begin(), openList.end(),
            [&](const Point& a, const Point& b) {
                return data[a.row][a.col].f < data[b.row][b.col].f;
            });

        Point current = *bestIt;
        openList.erase(bestIt);
        data[current.row][current.col].inOpen = false;

        // 2b. Goal check
        if (current == end) {
            // Reconstruct path by walking parent pointers from end → start
            std::vector<Point> path;
            Point step = end;
            while (!(step == start)) {
                path.push_back(step);
                step = data[step.row][step.col].parent;
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        // 2c. Move to closed list
        data[current.row][current.col].inClosed = true;

        // 2d. Expand neighbours
        for (int d = 0; d < 4; ++d) {
            const int nr = current.row + DR[d];
            const int nc = current.col + DC[d];

            // Bounds check
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            // Obstacle check
            if (matrix[nr][nc] == 1) continue;
            // Already fully evaluated
            if (data[nr][nc].inClosed) continue;

            const int tentativeG = data[current.row][current.col].g + 1;

            // Only update if we found a cheaper route to this neighbour
            if (tentativeG < data[nr][nc].g) {
                const Point neighbour{ nr, nc };
                data[nr][nc].g = tentativeG;
                data[nr][nc].f = f_cost(tentativeG, manhattanDistance(neighbour, end));
                data[nr][nc].parent = current;

                if (!data[nr][nc].inOpen) {
                    openList.push_back(neighbour);
                    data[nr][nc].inOpen = true;
                }
            }
        }
    }

    return {}; // open list exhausted – no path exists
}

// ---------------------------------------------------------------------------
// Solve and display
// ---------------------------------------------------------------------------
void BinaryMatrix::solveAndDisplay() const {
    const std::vector<Point> path = runAStar();

    // ANSI colour codes
    const char* GREEN = "\x1b[32m";
    const char* RED = "\x1b[31m";
    const char* CYAN = "\x1b[36m";
    const char* YELLOW = "\x1b[33m";
    const char* RESET = "\x1b[0m";

    // Build character overlay (S, E, *)
    std::vector<std::vector<char>> overlay(rows, std::vector<char>(cols, 0));
    for (const auto& p : path)     overlay[p.row][p.col] = '*';
    overlay[start.row][start.col] = 'S';
    overlay[end.row][end.col] = 'E';

    // Print grid
    std::cout << "\nBinary Matrix (" << rows << "x" << cols << "):\n";
    std::cout << "--------------------\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const char o = overlay[i][j];
            if (o == 'S') std::cout << GREEN << 'S' << RESET << ' ';
            else if (o == 'E') std::cout << RED << 'E' << RESET << ' ';
            else if (o == '*') std::cout << CYAN << '*' << RESET << ' ';
            else               std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "--------------------\n";
    std::cout << "Legend: "
        << GREEN << "S" << RESET << " = Start, "
        << RED << "E" << RESET << " = End, "
        << CYAN << "*" << RESET << " = Path, "
        << "0 = free, 1 = obstacle\n";

    // Handle no-path case
    if (path.empty()) {
        std::cout << YELLOW << "\nNo path found between S and E.\n" << RESET;
        return;
    }

    std::cout << "Path length (steps): " << static_cast<int>(path.size()) - 1 << '\n';

    // Per-step A* cost table
    // h(n) = |row_current - row_end| + |col_current - col_end|
    std::cout << "\nPer-step A* costs:\n";
    std::cout << "  h(n) = Manhattan distance = |row - " << end.row << "| + |col - " << end.col << "|\n\n";
    std::cout << "  Step | (row,col) |  g  | h formula (Manhattan)               |  h  |  f  \n";
    std::cout << "  -----|-----------|-----|-------------------------------------|-----|-----\n";
    for (std::size_t i = 0; i < path.size(); ++i) {
        const Point& cur = path[i];
        const int g = static_cast<int>(i);
        const int dr = (cur.row > end.row) ? cur.row - end.row : end.row - cur.row;
        const int dc = (cur.col > end.col) ? cur.col - end.col : end.col - cur.col;
        const int h = dr + dc;
        std::cout << "  " << i
            << "    | (" << cur.row << "," << cur.col << ")"
            << "      |  " << g
            << "  | |" << cur.row << "-" << end.row << "| + |" << cur.col << "-" << end.col << "|"
            << " = " << dr << "+" << dc << " = " << h
            << "  |  " << h
            << "  |  " << f_cost(g, h) << '\n';
    }
}

// ---------------------------------------------------------------------------
// Plain display (no colour, no path overlay)
// ---------------------------------------------------------------------------
void BinaryMatrix::displayMatrix() const {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r == start.row && c == start.col) std::cout << "S ";
            else if (r == end.row && c == end.col)   std::cout << "E ";
            else                                        std::cout << matrix[r][c] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// ---------------------------------------------------------------------------
// Getters
// ---------------------------------------------------------------------------
int BinaryMatrix::getRows() const { return rows; }
int BinaryMatrix::getCols() const { return cols; }
std::vector<std::vector<int>> BinaryMatrix::getMatrix() const { return matrix; }