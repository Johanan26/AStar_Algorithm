#include "Display.h"
#include <iostream>
#include <vector>

namespace Color {
    constexpr const char* Green = "\x1b[32m";
    constexpr const char* Red = "\x1b[31m";
    constexpr const char* Cyan = "\x1b[36m";
    constexpr const char* Yellow = "\x1b[33m";
    constexpr const char* Reset = "\x1b[0m";
}

void Display::render(const Grid& grid, const std::vector<Point>& path) {
    printGrid(grid, path);

    if (path.empty()) {
        std::cout << Color::Yellow << "\nNo path found between S and E.\n" << Color::Reset;
        return;
    }

    std::cout << "\nShortest path found.\n";
    std::cout << "Path length (steps): " << static_cast<int>(path.size()) - 1 << "\n";

    printCostTable(grid, path);
}

void Display::printGrid(const Grid& grid, const std::vector<Point>& path) {
    int rows = grid.rows();
    int cols = grid.cols();

    std::vector<std::vector<char>> overlay(rows, std::vector<char>(cols, 0));

    for (const auto& p : path) {
        overlay[p.row][p.col] = '*';
    }

    overlay[grid.start().row][grid.start().col] = 'S';
    overlay[grid.end().row][grid.end().col] = 'E';

    std::cout << "\nGrid (" << rows << " x " << cols << ")\n";
    std::cout << "-------------------------\n";

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (overlay[r][c] == 'S') {
                std::cout << Color::Green << 'S' << Color::Reset << ' ';
            }
            else if (overlay[r][c] == 'E') {
                std::cout << Color::Red << 'E' << Color::Reset << ' ';
            }
            else if (overlay[r][c] == '*') {
                std::cout << Color::Cyan << '*' << Color::Reset << ' ';
            }
            else {
                std::cout << grid.cell(r, c) << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << "-------------------------\n";
    std::cout << "Legend: "
        << Color::Green << "S" << Color::Reset << " = Start, "
        << Color::Red << "E" << Color::Reset << " = End, "
        << Color::Cyan << "*" << Color::Reset << " = Path, "
        << "0 = free, 1 = obstacle\n";
}

void Display::printCostTable(const Grid& grid, const std::vector<Point>& path) {
    Point end = grid.end();

    std::cout << "\nA* Cost Table\n";
    std::cout << "Step | Position | g | h | f\n";
    std::cout << "-----|----------|---|---|---\n";

    for (std::size_t i = 0; i < path.size(); ++i) {
        const Point& p = path[i];
        int g = static_cast<int>(i);
        int h = manhattanDistance(p, end);
        int f = fCost(g, h);

        std::cout << i
            << "    | (" << p.row << "," << p.col << ")"
            << "   | " << g
            << " | " << h
            << " | " << f << '\n';
    }
}