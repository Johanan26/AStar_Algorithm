#include "AStar.h"
#include <algorithm>
#include <limits>
#include <vector>

std::vector<Point> AStar::findPath(const Grid& grid) {
    const Point start = grid.start();
    const Point goal = grid.end();

    struct CellData {
        int g;
        int f;
        Point parent;
        bool inOpen;
        bool inClosed;

        CellData()
            : g(std::numeric_limits<int>::max()),
            f(std::numeric_limits<int>::max()),
            parent(-1, -1),
            inOpen(false),
            inClosed(false) {
        }
    };

    std::vector<std::vector<CellData>> data(
        grid.rows(),
        std::vector<CellData>(grid.cols())
    );

    std::vector<Point> openList;

    data[start.row][start.col].g = 0;
    data[start.row][start.col].f = manhattanDistance(start, goal);
    data[start.row][start.col].inOpen = true;
    openList.push_back(start);

    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };

    while (!openList.empty()) {
        auto bestIt = std::min_element(
            openList.begin(),
            openList.end(),
            [&](const Point& a, const Point& b) {
                return data[a.row][a.col].f < data[b.row][b.col].f;
            }
        );

        Point current = *bestIt;
        openList.erase(bestIt);
        data[current.row][current.col].inOpen = false;

        if (current == goal) {
            std::vector<Point> path;
            Point step = goal;

            while (step != start) {
                path.push_back(step);
                step = data[step.row][step.col].parent;
            }

            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        data[current.row][current.col].inClosed = true;

        for (int i = 0; i < 4; ++i) {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];

            if (!grid.isWalkable(nr, nc)) {
                continue;
            }

            if (data[nr][nc].inClosed) {
                continue;
            }

            int newG = data[current.row][current.col].g + 1;

            if (newG < data[nr][nc].g) {
                Point neighbour(nr, nc);

                data[nr][nc].g = newG;
                data[nr][nc].f = fCost(newG, manhattanDistance(neighbour, goal));
                data[nr][nc].parent = current;

                if (!data[nr][nc].inOpen) {
                    openList.push_back(neighbour);
                    data[nr][nc].inOpen = true;
                }
            }
        }
    }

    return {};
}