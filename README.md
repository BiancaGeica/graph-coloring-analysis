# proiect_analiza_algoritmilor
 Graph Coloring - Greedy Implementation

 This file implements the classic greedy sequential coloring algorithm
 for the graph coloring problem.

 COMPLEXITY ANALYSIS:
 Time Complexity: O(N * M) or O(N * d_avg) where d_avg is average degree
   - Process vertices sequentially: O(N)
   - For each vertex, check all neighbors: O(degree)
   - Total: O(N * average_degree) = O(N + M) for sparse graphs
   - Worst case (complete graph): O(N^2)
 Space Complexity: O(N + M) for storing the graph

 This classic greedy approach processes vertices in natural order (0, 1, 2, ...)
 and assigns each vertex the smallest available color. It makes a locally optimal
 choice at each step without look-ahead or sophisticated heuristics.

 Key differences from Backtracking:
 - Greedy makes ONE pass through vertices (no backtracking)
 - Greedy commits to first valid color found (no exploration of alternatives)
 - Greedy is deterministic and fast but may not find optimal solution

 Graph Coloring - Backtracking Implementation

 This file implements the backtracking algorithm to find the exact
 chromatic number of a graph.

 COMPLEXITY ANALYSIS:
Time Complexity: O(k^N) where k is the chromatic number and N is number of vertices
- In worst case, we try all possible color combinations for all vertices
- For each vertex, we try up to k colors
- With backtracking, we prune invalid branches early
Space Complexity: O(N + M) for storing the graph and O(N) for recursion stack
- Total: O(N + M)

This approach guarantees finding the optimal solution (minimum chromatic number)
but can be exponential for large graphs. Works well for small to medium graphs.
  