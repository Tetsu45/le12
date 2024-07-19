#include <iostream>
using namespace std;

// Define an edge structure
struct Edge {
    int src, dest, weight;
};

// A class to represent a graph
class Graph {
public:
    int V, E; // V -> number of vertices, E -> number of edges
    Edge* edges; // collection of all edges
    int edgeCount;

    Graph(int V, int E);
    ~Graph();
    void addEdge(int u, int v, int w);
    int find(int parent[], int i);
    void Union(int parent[], int rank[], int x, int y);
    void kruskalMST();
};

// Constructor
Graph::Graph(int V, int E) {
    this->V = V;
    this->E = E;
    edges = new Edge[E];
    edgeCount = 0;
}

// Destructor
Graph::~Graph() {
    delete[] edges;
}

// Function to add an edge to the graph
void Graph::addEdge(int u, int v, int w) {
    if (edgeCount < E) {
        edges[edgeCount].src = u;
        edges[edgeCount].dest = v;
        edges[edgeCount].weight = w;
        edgeCount++;
    }
}

// A utility function to find set of an element i (uses path compression technique)
int Graph::find(int parent[], int i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

// A function that does union of two sets of x and y (uses union by rank)
void Graph::Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Function to sort edges based on their weights using bubble sort
void bubbleSort(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// The main function to construct MST using Kruskal's algorithm
void Graph::kruskalMST() {
    Edge* result = new Edge[V]; // Store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight.
    bubbleSort(edges, edgeCount);

    // Allocate memory for creating V subsets
    int* parent = new int[V];
    int* rank = new int[V];

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        parent[v] = v;
        rank[v] = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < edgeCount) {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        Edge next_edge = edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // If including this edge does not cause a cycle, include it in result
        // and increment the index of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, rank, x, y);
        }
        // Otherwise discard the next_edge
    }

    // Print the resultant MST
    cout << "Following are the edges in the constructed MST\n";
    for (int j = 0; j < e; ++j) {
        cout << result[j].src << " -- " << result[j].dest << " == " << result[j].weight << endl;
    }

    delete[] parent;
    delete[] rank;
    delete[] result;
}

int main() {
    int V = 4; // Number of vertices in graph
    int E = 5; // Number of edges in graph
    Graph graph(V, E);

    // Add edges
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    // Function call
    graph.kruskalMST();

    return 0;
}
