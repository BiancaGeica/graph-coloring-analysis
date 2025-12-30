#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 2005;

// Global variables for the graph
int N, M;
vector<int> adj[MAXN];
int color[MAXN];
bool adjMatrix[MAXN][MAXN];

// ============================================================================
// BACKTRACKING APPROACH - Finds exact chromatic number
// ============================================================================

// Check if current color assignment is safe for vertex v
bool isSafeBacktrack(int v, int c) {
    for (int u : adj[v]) {
        if (color[u] == c) {
            return false;
        }
    }
    return true;
}

// Backtracking function to color graph with at most maxColors
bool graphColoringBacktrack(int v, int maxColors) {
    // All vertices colored successfully
    if (v == N) {
        return true;
    }
    
    // Try all colors from 1 to maxColors
    for (int c = 1; c <= maxColors; c++) {
        if (isSafeBacktrack(v, c)) {
            color[v] = c;
            
            // Recursively color remaining vertices
            if (graphColoringBacktrack(v + 1, maxColors)) {
                return true;
            }
            
            // Backtrack
            color[v] = 0;
        }
    }
    
    return false;
}

// Find minimum number of colors needed (chromatic number)
int findChromaticNumberBacktrack() {
    // Try increasing number of colors starting from 1
    for (int numColors = 1; numColors <= N; numColors++) {
        memset(color, 0, sizeof(color));
        
        if (graphColoringBacktrack(0, numColors)) {
            return numColors;
        }
    }
    
    return N; // Worst case: every vertex gets a different color
}

// ============================================================================
// GREEDY APPROACH - Welsh-Powell Algorithm
// ============================================================================

struct Node {
    int id;
    int degree;
    
    bool operator<(const Node& other) const {
        return degree > other.degree; // Sort in descending order of degree
    }
};

int findChromaticNumberGreedy() {
    // Create array of nodes with their degrees
    vector<Node> nodes;
    for (int i = 0; i < N; i++) {
        nodes.push_back({i, (int)adj[i].size()});
    }
    
    // Sort nodes by degree in descending order (Welsh-Powell)
    sort(nodes.begin(), nodes.end());
    
    // Reset colors
    memset(color, 0, sizeof(color));
    
    int maxColor = 0;
    
    // Color each vertex
    for (const Node& node : nodes) {
        int v = node.id;
        
        // Find the smallest color not used by adjacent vertices
        // Only need to track N+1 colors maximum
        vector<bool> usedColors(N + 1, false);
        
        for (int u : adj[v]) {
            if (color[u] != 0) {
                usedColors[color[u]] = true;
            }
        }
        
        // Assign the smallest available color
        for (int c = 1; c <= N; c++) {
            if (!usedColors[c]) {
                color[v] = c;
                maxColor = max(maxColor, c);
                break;
            }
        }
    }
    
    return maxColor;
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Read input
    cin >> N >> M;
    
    // Initialize adjacency list and matrix
    memset(adjMatrix, false, sizeof(adjMatrix));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
        adjMatrix[u][v] = true;
        adjMatrix[v][u] = true;
    }
    
    // Solve using Backtracking
    int chromaticBacktrack = findChromaticNumberBacktrack();
    
    // Solve using Greedy (Welsh-Powell)
    int chromaticGreedy = findChromaticNumberGreedy();
    
    // Output results
    cout << "Backtracking: " << chromaticBacktrack << endl;
    cout << "Greedy: " << chromaticGreedy << endl;
    
    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * 
 * BACKTRACKING APPROACH:
 * Time Complexity: O(k^N) where k is the chromatic number and N is number of vertices
 *   - In worst case, we try all possible color combinations for all vertices
 *   - For each vertex, we try up to k colors
 *   - With backtracking, we prune invalid branches early
 * Space Complexity: O(N + M) for storing the graph and O(N) for recursion stack
 *   - Total: O(N + M)
 * 
 * This approach guarantees finding the optimal solution (minimum chromatic number)
 * but can be exponential for large graphs. Works well for small to medium graphs.
 * 
 * GREEDY APPROACH (Welsh-Powell):
 * Time Complexity: O(N^2) 
 *   - Sorting nodes by degree: O(N log N)
 *   - For each vertex, checking adjacent vertices: O(N * degree_avg)
 *   - In worst case (complete graph): O(N^2)
 * Space Complexity: O(N + M) for storing the graph
 * 
 * This approach provides an upper bound on the chromatic number. It's much faster
 * but doesn't guarantee the optimal solution. The Welsh-Powell heuristic of
 * coloring high-degree vertices first often produces good results in practice.
 * 
 * COMPARISON:
 * - Backtracking: Exact but slow for large graphs
 * - Greedy: Fast approximation, good for large graphs
 * - For sparse graphs, greedy often finds optimal or near-optimal solutions
 * - For dense graphs (like complete graphs), both find the same answer but
 *   backtracking takes much longer
 */
