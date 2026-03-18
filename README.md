# AStar Pathfinding Project

**Student:** Johanan Seeruthen  

**Student Number** G00419446

**Module:** C++ Programming  

**Project Title:** AStar Pathfinding in C++   

**Language:** C++ 14

---
## Table of Contents

1. [Overview](#overview)
2. [Project Aims](#project-aims)
3. [How the Program Works](#how-the-program-works)
4. [Program Structure](#program-structure)
   - [Point](#point)
   - [Grid](#grid)
   - [AStar](#astar)
   - [Display](#display)
   - [main](#main)
5. [Design Choices](#design-choices)
   - [Why Manhattan Distance Was Used](#why-manhattan-distance-was-used)
   - [Why Modular Design Was Used](#why-modular-design-was-used)
6. [Core Algorithm Explanation](#core-algorithm-explanation)
7. [Screenshots](#screenshots)
   - [Program Setup](#program-setup)
   - [Grid Logic](#grid-logic)
   - [AStar Core Logic](#astar-core-logic)
   - [Output / Display](#output--display)
   - [Program Output](#program-output)
8. [Testing and Validation](#testing-and-validation)
   - [Test Case 1: Normal Path Available](#test-case-1-normal-path-available)
   - [Test Case 2: Dense Obstacle Layout](#test-case-2-dense-obstacle-layout)
   - [Test Case 3: No Path Possible](#test-case-3-no-path-possible)
9. [Project Management](#project-management)
   - [Progress Tracking](#progress-tracking)
10. [Problems Encountered](#problems-encountered)
11. [Reflection](#reflection)
12. [References](#references)

---
## Overview:

This project implements the **AStar** algorithm in **modern C++** to find the shortest path between the start point and the end point on a grid containing obstacles. The system was designed using a modular and object-oriented structure so that the logic for the grid, algorithm, point handling, and display are separated into different files. In terms of the movement calculations I used Manhattan Distance to calculate where the algorithm can move and where it is restricted.

The project aimed not just to deliver a functional pathfinding program, but to showcase a broader understanding of algorithmic design, modular software development, problem solving, and the process of iterative improvement throughout development.

This project uses:
- Modern C++ features and standard library containers
- Object-oriented design
- A heuristic based shortest path algorithm
- Clear terminal-based output showing the discovered path
- Structured code split across multiple source and header files

---

## Project Aims:

The main aims of my project were:

- To implement the **AStar** algorithm correctly
- To represent a grid with blocked and unblocked cells
- To calculate and display the shortest valid path
- Structure the codebase using a modular design approach
- To make the solution understandable and maintainable
- To demonstrate reasoning behind design decisions rather than only showing final output

---

## How the Program Works:

The program creates a matrix grid made up of cells (6,8). Some cells are walkable (0) and some are obstacles (1). A start point (S) and an end point (E) are chosen, and the AStar algorithm searches for the shortest route between them.

AStar works by combining:
- **g-cost**: the distance travelled from the start node
- **h-cost**: the estimated distance to the goal
- **f-cost**: the total cost, calculated as **f = g + h**

For this project, the heuristic used is **Manhattan distance**, because movement is limited to four directions:
- up
- down
- left
- right

This made Manhattan distance a suitable and efficient choice.

---

## Program Structure:

The project is split into several files, each with a specific responsibility.

### `Point`
The **Point** class stores row and column positions on the grid. It also supports comparison between points and helper functions such as Manhattan distance.

### `Grid`
The **Grid** class stores the matrix grid layout, including blocked (1) and free cells (0), as well as the start and end positions. It also provides functions for checking if a cell is valid and walkable.

### `AStar`
The **AStar** class contains the core pathfinding logic, handling the evaluation of neighbouring cells, tracking of movement costs, recording of parent nodes, and reconstructs the final path once the goal is reached.

### `Display`
The **Display** class is responsible for showing the grid and path in a readable format. This separation keeps the algorithms logic independent from the output logic.

### `main`
The **main.cpp** file sets up the program, creates test cases, runs the algorithm, and displays the result.

---

## Design Choices:
### Why Manhattan distance was used:

Manhattan distance was chosen because movement in the grid is limited to vertical and horizontal directions only. This makes it a better heuristic than Euclidean distance, because it estimates distance using the same movement rules as the program.

This means Manhattan distance is:
- simple to calculate
- appropriate for the grid design

**Formula:**
h(n)= |current row - goal row| + |current col - goal col|

### Why modular design was used:

The code was split into different files so that each class has a clear responsibility. This makes the program easier to test, debug, and extend.

For example:
- the grid logic can be changed without rewriting the algorithm
- the output style can be changed without affecting pathfinding
- the algorithm can be reused with different grid sizes or test setups

This supports better software engineering practices than placing all logic into one large file.

---

## Core Algorithm Explanation:

The AStar algorithm begins at the starting point and keeps track of nodes to be explored. For each node, it calculates the movement cost from the start and the estimated cost to the goal.

**Formula:**
f(n)=g(n)+h(n)
Meaning:
g(n) = cost from start to current node
h(n) = estimated cost from current node to goal
f(n) = total estimated cost

The process is:

1. Add the start node to the open list
2. Repeatedly choose the node with the lowest **f-cost**
3. Check whether it is the goal
4. If not, inspect its neighbours
5. Ignore blocked cells and already closed cells
6. Update costs if a better route is found
7. Continue until the goal is reached or no valid path remains

Once the end node is reached, the path is reconstructed by following parent nodes backward from the goal to the start.

This approach is guaranteed to produce the shortest path in this context for the following reasons:
-the cost of each step remains consistent throughout the search
-the heuristic is reliable and suitable for four-directional movement
-nodes are revisited and updated whenever a more optimal route is discovered

---

## Screenshots:

### Program Setup

screenshot here showing the section of your **main.cpp** where the grid is created, the test case is run, and the algorithm is called.

screenshot here: `images/main-setup.png`  
What it should show: 
 grid creation  
 random fill or manual setup  
call to `AStar::findPath()`  
call to `Display::render()`  
 
*Figure 1. Main program flow showing grid setup, pathfinding call, and rendering of the result.*

---

### Grid Logic

screenshot here showing functions from `Grid.cpp` and `Grid.h`.

 screenshot here:`images/grid-logic.png`  
What it should show:  
 `isInside()`  
`isWalkable()`  
grid generation or obstacle handling  
 start/end setup if possible  

*Figure 2. Grid logic used to validate positions and represent blocked and walkable cells.*

---

### AStar Core Logic

screenshot here showing the main section of `AStar.cpp`.

screenshot here: `images/astar-core.png`  
**What it should show:**  
open list selection  
neighbour checking  
cost updates (`g`, `h`, `f`)  
parent assignment  
path reconstruction if possible  

*Figure 3. Core AStar implementation showing cost calculation, node expansion, and path reconstruction.*

---

### Output / Display

screenshot here showing your display logic or terminal output code.

screenshot here: `images/display-output.png`  
What it should show:  
rendering of grid  
start/end labels  
path symbols  
any printed cost or legend  

*Figure 4. Display logic used to present the shortest path clearly to the user.*

---

### Program Output

screenshot here of the program running successfully in the terminal.

screenshot here: `images/program-run.png`  
**What it should show:**  
full program execution  
visible start point  
visible end point  
obstacles  
shortest path result  
any “no path found” message if you want an edge case example too  

*Figure 5. Example execution of the program showing a successful shortest-path result.*

---

## Testing and Validation

Testing was important to confirm that the algorithm works correctly under both normal and edge-case conditions.

### Test Case 1: Normal path available
A standard grid with a moderate number of obstacles was used to verify that the algorithm could find a valid shortest path between the start and end points.

**Expected result:**  
A path should be found and displayed.

**Actual result:**  
The algorithm successfully returned a path and displayed it clearly.

### Test Case 2: Dense obstacle layout
A denser obstacle configuration was tested to check whether the algorithm still behaved correctly in more difficult conditions.

**Expected result:**  
The program should either find a valid route or correctly report that no route exists.

**Actual result:**  
The algorithm handled the case correctly and did not crash or produce invalid output.

### Test Case 3: No path possible
A scenario where the start or end is effectively blocked can be used to confirm that the program behaves safely when no route exists.

**Expected result:**  
The program should report that no path was found.

**Actual result:**  
The program returned an empty result and handled the case safely.

---

## Project Management:

The development process was carried out iteratively rather than trying to build the entire solution in one step. This made it easier to debug and improve the program gradually.

The development sequence was:
1. Create a basic grid structure
2. Add point handling and coordinate logic
3. Implement obstacle support
4. Build the AStar pathfinding logic
5. Add path reconstruction
6. Improve the display and readability of the output
7. Test with different obstacle layouts and scenarios
8. Refactor the code into a cleaner modular structure

This approach helped keep the project manageable and made debugging easier because problems could be isolated to one section at a time.

### Progress Tracking:

Progress was tracked by focusing on one main development goal at a time. Instead of treating the program as a single task, it was divided into smaller milestones such as:
- making the grid functional
- validating movement
- implementing cost calculations
- reconstructing the path
- improving output clarity
- testing edge cases

This process made the project easier to manage and helped show continuous improvement.

---

## Problems Encountered:

One of the biggest challenges was ensuring that the algorithm did not revisit nodes unnecessarily or keep worse paths when a better one had already been found. This required careful handling of open and closed states, as well as correct updating of parent nodes and costs.

Another challenge was keeping the project understandable. It is easy for pathfinding code or the code Ai had given me to become difficult to read when all logic is placed in one file. Splitting responsibilities across classes improved readability and made debugging easier.

A further issue was that the Manhattan distance was continuously outputting the path in an L shape which I had noticed after rerunning the program.

These problems were addressed through iterative debugging, testing different scenarios, and improving the structure of the code rather than only trying to “make it work”.

---

## Reflection:

This project improved my understanding of both algorithmic problem-solving and code organisation in C++. Before completing the project, I understood the general idea of pathfinding, but implementing AStar in code made the importance of data structures, cost tracking, and parent reconstruction much clearer.

Dividing the project into distinct classes proved to be an effective decision. It made the overall system easier to understand, resulting in a cleaner implementation. It also aided in explaining the project, as each component had a well-defined and clearly identifiable purpose.

Another positive outcome was using a heuristic that matched the movement model. Choosing Manhattan distance made the behaviour of the algorithm easier to justify, rather than simply selecting a formula without reasoning.

If I were to redo this project i would improve it by:
- allowing diagonal movement (Euclidean)
- supporting multiple heuristics
- adding weighted terrain
- adding more formal automated tests

Overall, the project was successful because it not only produced a functional implementation, but also improved my understanding of algorithm design, modular development, and the importance of clear technical communication.

## References:
-cppreference.com (2025) std::vector. https://en.cppreference.com/w/cpp/container/vector.html

-cppreference.com (2025) std::abs. https://en.cppreference.com/w/cpp/numeric/math/abs

-Patel, A. Introduction to the A Algorithm* (2023). Red Blob Games. www.redblobgames.com/pathfinding/a-star/introduction.html

-Chat Gpt (2025). https://chatgpt.com

-Claude Ai (2025). https://claude.ai

-GeeksforGeeks (2025) Manhattan Distance. https://www.geeksforgeeks.org/data-science/manhattan-distance/
