# Graph Algorithms Toolkit

## Description
This project is a modular C-based toolkit designed to process, analyze, and visualize complex graph structures. It supports both directed and undirected graphs, handling edge weights and providing rigorous implementations of classical algorithms for pathfinding, connectivity, and minimum spanning trees.

## Technologies
-   **C11**
-   **MinGW/GCC**
-   **Graphviz API** (libcgraph, libgvc)
-   **DOT Language**

## Features
-   **Traversal Algorithms**: Full implementations of Breadth-First Search (BFS) and Depth-First Search (DFS).
-   **Pathfinding**: Bellman-Ford algorithm to find shortest paths and detect negative cycles in directed graphs.
-   **Minimum Spanning Tree**: Kruskal’s algorithm using Disjoint-Set Union (Union-Find) with path compression and rank optimization.
-   **Connectivity Analysis**: Identification of Connected Components (undirected) and Strongly Connected Components (directed).
-   **Visual Export**: Automatic generation of PNG images highlighting specific algorithm results, such as MST edges in red or colored strongly connected components.

## How to Run

### Prerequisites

-   **GCC Compiler** installed (e.g., MinGW on Windows).
-   **Graphviz** installed and added to your system path.

### Compiling

Navigate to the project root and run the compilation command (adjust paths if your Graphviz installation differs):

    gcc -o main.exe sources/*.c main.c -I"C:\Program Files\Graphviz\include" -L"C:\Program Files\Graphviz\lib" -lcgraph -lgvc

### Execution
Run the executable to access the interactive menu:

    .\main.exe

## Project Structure

-   **`headers/grafo.h`**: Core graph data structures (Adjacency List) and basic manipulation functions.
-   **`headers/algoritmos.h`**: Interface for the search, pathfinding, and optimization algorithms.
-   **`sources/grafo.c`**: Implementation of graph loading, memory management, and DOT file generation.
-   **`sources/algoritmos.c`**: Implementation of BFS, DFS, Bellman-Ford, Kruskal, and SCC logic.
-   **`main.c`**: The interactive CLI menu for user interaction.
-   **`input/`**: Example graph text files using a specific `(origin, destination):weight` syntax.
- 
## What I Learned

-   **Memory Management**: Handled complex pointer arithmetic and nested data structures (linked lists within arrays) to represent adjacency lists.
-   **Disjoint-Set Optimization**: Improved Kruskal's performance by implementing path compression and union-by-rank.
-   **Transposed Graphs**: Used graph transposition as a prerequisite for identifying strongly connected components.
-   **External API Integration**: Interfaced directly with the Graphviz C libraries to automate technical drawing.


## Future Improvements
-   **Dijkstra's Algorithm**: Add support for Dijkstra using a Priority Queue (Min-Heap) for faster pathfinding on graphs without negative weights.
-   **Topological Sorting**: Implement sorting for Directed Acyclic Graphs (DAGs).
-   **Dynamic Input**: Allow users to add vertices and edges manually through the CLI menu.



