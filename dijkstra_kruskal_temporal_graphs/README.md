# Temporal Network Analysis in Graphs

This folder contains a C++ implementation designed to analyze and optimize a temporal network. The provided algorithm computes shortest paths, determines the earliest year for complete interconnection, and calculates the minimum spanning tree cost in a dynamically evolving network.
Before we go into further detail, What does shortest paths, earlist year and minimum cost means? It means that all the edges are not available at the start, some will just be availabe with the passage of time. Each edge takes time to be run through and costs something to be built.

## The Algorithms

The C++ implementation includes three primary algorithms:

### Dijkstra's Algorithm

Computes the shortest paths from one vertice to all others. This algorithm ensures the minimum traversal time required to reach each vertex from the source.

### Kruskal's Algorithm

Determines the earliest year when all vertices are interconnected. This involves sorting the edges by the year they become available and merging the sets of connected components to find the first year when the graph is fully connected.

### Minimum Spanning Tree Calculation

Calculates the minimum cost necessary to interconnect all vertices. Using Kruskal's algorithm, this calculation ensures that all vertices are connected with the least possible construction cost.

## Complexity

### Dijkstra's Algorithm

- **Time Complexity**: O((V + E) log V), where `V` is the number of vertices and `E` is the number of edges. This complexity comes from using a priority queue to find the shortest path in a graph with non-negative edge weights.
That is to show how impactful the Data Strucure choice is, so it can't be overlooked.
- **Space Complexity**: O(V + E), as it needs to store the graph structure and the priority queue.

### Kruskal's Algorithm

- **Time Complexity**: O(E log E + E log V), which simplifies to O(E log E) since sorting the edges dominates the complexity. This complexity comes from sorting the edges and performing the union-find operations.
- **Space Complexity**: O(E + V), as it needs to store the edges and the union-find data structures.

### Minimum Spanning Tree Calculation

- **Time Complexity**: O(E log E) for sorting the edges and O(E log V) for the union-find operations, making the overall complexity O(E log E). This is because it builds upon Kruskal's algorithm for finding the MST.
- **Space Complexity**: O(E + V), similar to Kruskal's algorithm, for storing edges and the union-find data structures.

By leveraging these efficient algorithms, this program ensures that the temporal network is analyzed and optimized within reasonable computational limits, making it suitable for large-scale networks with dynamic properties. A case were we can imagine it being useful is traffic, so it can updates when a road closes, becomes busier or the price of gas changes, so the cost to travel changes too.

## Input Format

The input format is as follows:

1. The first line contains two integers, `N` (number of vertices) and `M` (number of edges).
2. Each of the next `M` lines describes a edge between two vertices `u` and `v` with three parameters: year `a`, traversal time `t`, and construction cost `c`.

## Output Format

1. Each of the first `N` lines contains a single integer.
    - This integer represents the minimum time required to travel from the vertice number 1 to vertice `i`.

2. Contains a single integer `A1`.
    - `A1` represents the earliest year when all the distances listed in the first `N` lines are simultaneously achievable.

3. **N + 2-th Line**:
    - Contains a single integer `A2`.
    - `A2` represents the earliest year when it is possible to reach any vertice in the graph from the number 1 vertice.

4. **N + 3-th Line**:
    - Contains a single integer.
    - This integer represents the minimum cost required to interconnect the entire graph.

### Example of Input and Output Structure

    9 14
    1 2 16 4 7
    2 3 16 8 5
    3 4 3 7 6
    4 5 2 9 13
    5 6 2 10 14
    6 7 2 2 5
    7 8 15 1 12
    8 9 5 7 9
    2 8 15 11 18
    3 9 6 2 10
    3 6 19 4 5
    4 6 17 14 7
    1 8 6 8 2
    7 9 10 6 14

    0
    4
    12
    19
    21
    11
    9
    8
    14
    16
    15
    52