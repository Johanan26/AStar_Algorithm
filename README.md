# AStar_Algorithm

A C++ implementation of the **A\* search algorithm** applied to a randomly generated binary grid. The program finds the shortest path between a random start and end point, avoiding obstacles, and displays a colour-coded grid alongside a per-step cost breakdown.

---

## Demo

```
Binary Matrix (6x8):
--------------------
1 1 0 0 0 0 0 0
1 0 1 1 0 1 1 0
1 1 1 0 0 0 1 0
1 1 1 0 1 S 0 E
0 0 0 0 0 0 0 1
1 0 0 1 0 0 1 0
--------------------
Legend: S = Start,  E = End,  * = Path,  0 = free,  1 = obstacle
```

---

## Features

- **Random binary matrix generation** — each cell is independently assigned as free (`0`) or obstacle (`1`)
- **Random start/end placement** — S and E are always placed on free cells
- **A\* search** — finds the optimal (shortest) path using Manhattan distance as the heuristic
- **ANSI colour output** — Start in 🟢 green, End in 🔴 red, Path in 🔵 cyan
- **Per-step cost table** — prints `g`, `h`, and `f` values at every step along the found path
- **No-path detection** — clearly reports when no path exists between S and E

---

## Algorithm

A\* is a best-first search that finds the shortest path by evaluating nodes using:

```
f(n) = g(n) + h(n)
```

| Symbol | Meaning |
|--------|---------|
| `g(n)` | Cost to reach node `n` from the start |
| `h(n)` | Heuristic estimate from `n` to the goal (Manhattan distance) |
| `f(n)` | Total estimated cost — the priority score |

**Manhattan distance** is used as the heuristic since movement is restricted to 4 directions (up, down, left, right — no diagonals):

```
h(n) = |row_n - row_goal| + |col_n - col_goal|
```

### Algorithm Steps

1. Add the start node to the open list with `g = 0`
2. Repeat until the open list is empty:
   - Pick the node with the lowest `f` score
   - If it's the goal → reconstruct and return the path
   - Move it to the closed list
   - Expand all 4-directional walkable neighbours:
     - Skip if already evaluated (closed list)
     - Update `g`, `h`, `f` and parent if a cheaper route is found
3. If the open list empties with no goal found → no path exists

---

## Project Structure


## How to Build & Run

### Requirements
- C++17 or later
- Any standard C++ compiler (MSVC, GCC, Clang)

### Using g++
```bash
g++ -std=c++17 -O2 main.cpp AStar.cpp -o astar
./astar
```

### Using Visual Studio
Open the project folder, set `main.cpp` as the entry point, and press **F5** to build and run.

---

## Sample Output

```
=== A* Pathfinding on a Random Binary Matrix ===

Binary Matrix (6x8):
--------------------
1 1 0 * * * * 0
...
--------------------
Path length (steps): 7

Per-step A* costs:
  h(n) = Manhattan distance = |row - 3| + |col - 7|

  Step | (row,col) |  g  | h formula (Manhattan)     |  h  |  f
  -----|-----------|-----|---------------------------|-----|-----
  0    | (3,5)     |  0  | |3-3| + |5-7| = 0+2 = 2  |  2  |  2
  1    | (3,6)     |  1  | |3-3| + |6-7| = 0+1 = 1  |  1  |  2
  2    | (3,7)     |  2  | |3-3| + |7-7| = 0+0 = 0  |  0  |  2
```

---

## Development Progress

### Week 1 — Binary Matrix Generator
- Designed the `BinaryMatrix` class with `rows`, `cols`, and a 2D `matrix` member
- Implemented `generateRandomMatrix()` to randomly populate cells with `0` or `1`
- Implemented `displayMatrix()` to print the grid to the console

### Week 2 — Random Start & End + Colour Display
- Added `randomizeStartEnd()` to pick two distinct free cells for start and end
- Integrated ANSI colour codes — `S` printed in green, `E` in red
- Updated `displayMatrix()` to overlay S and E on the grid with a legend

### Week 3 — A\* Implementation
- Introduced the `Point` struct and the `manhattanDistance` / `f_cost` helpers in `AStar.h`
- Implemented `runAStar()` with open/closed list bookkeeping and parent-pointer path reconstruction
- Implemented `solveAndDisplay()` to print the solved grid and the full per-step cost table

---

## Notes

- The grid uses ~60% obstacle density by default, making "no path" scenarios common — a useful stress test
- Movement is strictly 4-directional (no diagonal steps)
- The open list is a plain `std::vector`; for larger grids a `std::priority_queue` would improve performance

---

## Author

**G00419446** — Atlantic Technological University, Year 4 C++ Final Project
