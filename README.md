# Project Algorithm Analysis

HOW TO USE THE MAKEFILE

1. Build All - Compiles all .c files in the current directory into executable files.

$ make


2. Clean - Deletes all executables and temporary files.

$ make clean

Welsh-Powell Algorithm Overview:
 - Welsh-Powell is a Greedy heuristic based on vertex degrees.
 - The core idea is that vertices with many connections (high degree) are the most difficult to color, so we color them first.

Consulted various C [1] and C++ [2] implementations found on GitHub, as well as algorithm descriptions [3], [4].


About Tests:
Among the test graphs, tests 1 to 5 were created manually, while the others (6-16) were automatically generated using generator_teste.c. The tests are divided into 3 categories, with 5 tests in each category:

1. Correctness (Small Tests)
Files: test1.in ... test5.in

Content:
test1.in - Minimal complete graph (K3). Has 3 vertices, each connected to all others (a triangle). Tests if the algorithm correctly allocates 3 distinct colors when all neighbors conflict.

test2.in - Even cycle (C4). Has 4 vertices arranged in a circle (node 0 connected to 1, 1 to 2, 2 to 3, and 3 back to 0). Tests color alternation. Since the number of nodes is even, it should use only 2 colors.

test3.in - Complete graph (K5) - "Worst case". Has 5 vertices, all interconnected. Should choose exactly N colors (5 in this case).

test4.in - Star graph. Has a central node connected to multiple peripheral nodes that are not connected to each other. Perfect test for Welsh-Powell because the algorithm sorts nodes by degree: the central node has a high degree (5), while the rest have a low degree (1). It should color the center first and then reuse a single color for all surrounding nodes (2 colors total).

test5.in - Graph with isolated components. Contains two separate groups of nodes with no connections between them (a triangle on one side and another triangle on the other). If the first group uses colors 1, 2, 3, the algorithm should also use colors 1, 2, 3 for the second group.

Purpose: To demonstrate that the algorithm provides correct results without errors.

Generated: Manually

2. Scalability (Large Random Tests)
Files: test6.in ... test10.in

Content: Randomly generated graphs where N increases progressively (50 -> 2000).
Purpose: To observe how the algorithm behaves as the number of nodes (N) increases. Useful for generating an "execution time vs. number of nodes" plot.

Generated: Automatically

3. Density (Complex Random Tests)
Files: test11.in ... test16.in
Content: Graphs with N = 500, but with density varying from 10% to 100%.
Purpose: Generating a "number of colors vs. density" (or time vs. density) plot to see how the algorithm performs when the graph is denser (more edges) while keeping the number of nodes fixed.
Generated: Automatically


References:

[1] https://github.com/leovargasdev/grafos/blob/master/welshPowell.c
[2] https://github.com/aprilcoskun/graph-coloring/blob/master/Welsh-Powell.cpp
[3] https://www.geeksforgeeks.org/dsa/welsh-powell-graph-colouring-algorithm/
[4] https://en.wikipedia.org/wiki/Floyd–Warshall_algorithm

=====Degree of Saturation Algorithm=====

This project contains two C implementations of the DSATUR (Degree of Saturation) algorithm, a heuristic used for solving the graph coloring problem. The goal of the algorithm is to color the vertices of a graph such that no two adjacent vertices share the same color, attempting to minimize the total number of colors used (the chromatic number).

The project offers two distinct approaches regarding memory management and graph representation:

Adjacency Matrix Variant

    Uses a uint8_t matrix of size N×N.

    Pros: Direct implementation and fast (O(1)) edge existence verification.

    Cons: Higher memory footprint O(N²), making it less suitable for very large, sparse graphs.
    
Optimized Variant (Adjacency Lists)

    Uses linked lists to store the neighbors of each vertex.

    Pros: Memory-efficient for sparse graphs where the number of edges is significantly lower than the square of the number of vertices.

**DSat Algorithm for Sparse Graphs with Many Nodes**

*Pros:* 

    - High efficiency on graphs with many nodes and few edges (sparse); memory usage is proportional to the number of edges due to using adjacency lists instead of an adjacency matrix.
    - Neighbor traversal is done via the adjacency list, avoiding unconnected nodes.
    - DSatur dynamically selects the next node to color based on saturation degree, frequently obtaining a smaller chromatic number (a more optimal solution) compared to algorithms like Greedy or Welsh-Powell, as it prioritizes nodes with the highest saturation degree.
    
*Cons:*

    - On dense graphs (with a high number of edges), adjacency lists introduce significant memory overhead.
    - The algorithm does not check whether a newly added edge already exists because doing so would consume too many resources (verification would take O(node_degree)).

**DSat Algorithm for Dense Graphs with Few Nodes**

*Pros:* 

    - Superior performance on dense graphs.
    - Instant access to edges via direct matrix lookups.
    - Since the implementation uses uint8_t (1 byte) instead of int (4 bytes) to store the matrix, memory usage is reduced, allowing larger graphs to be processed.
    
*Cons:*

    - Wastes memory on sparse graphs because it allocates memory for a complete graph regardless of the actual edge count.
    - Inefficient for finding neighbors, as the algorithm must traverse all nodes in the graph for every check.