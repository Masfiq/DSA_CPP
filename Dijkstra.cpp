#include <iostream>
#include <climits>

// Function to initialize the adjacency matrix
void initializeMatrix(int** &matrix, int vertices) {
    matrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        matrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
        }
    }
}


// Function to add an edge
void addEdge(int** matrix, int vertices, int i, int j, int weight) {
    if (i >= 0 && i < vertices && j >= 0 && j < vertices) {
        matrix[i][j] = weight;
        matrix[j][i] = weight; // Remove this line for a directed graph
    }
}

// Function to find the vertex with the minimum distance value
int minDistance(int distance[], bool isVisited[], int vertices) {
    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < vertices; v++) {
        if (!isVisited[v] && distance[v] <= min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to implement Dijkstra's algorithm
void dijkstra(int** matrix, int vertices, int source) {
    int* distance = new int[vertices]; // The output array. distance[i] will hold the shortest distance from source to every node
    bool* isVisited = new bool[vertices]; // isVisited[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and isVisited[] as false
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        isVisited[i] = false;
    }

    // Distance of source vertex from itself is always 0
    distance[source] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(distance, isVisited, vertices);

        // Mark the picked vertex as processed
        isVisited[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 1; v < vertices; v++) {
            // Update distance[v] only if is not in isVisited, there is an edge from u to v,
            // and total weight of path from source to v through u is smaller than current value of distance[v]
            if (!isVisited[v] && matrix[u][v] && distance[u] != INT_MAX && distance[u] + matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + matrix[u][v];
            }
        }
    }

    // Print the constructed distance array
    std::cout << "Vertex \t Distance from Source" << std::endl;
    for (int i = 0; i < vertices; i++) {
        std::cout << i << " \t\t " << distance[i] << std::endl;
    }
}

int main() {
    int vertices = 6+1;
    int** adjMatrix;

    initializeMatrix(adjMatrix, vertices);

    // Add edges
    addEdge(adjMatrix, vertices, 1, 2, 2);
    addEdge(adjMatrix, vertices, 1, 3, 4);
    addEdge(adjMatrix, vertices, 2, 3, 1);
    addEdge(adjMatrix, vertices, 2, 4, 7);
    addEdge(adjMatrix, vertices, 3, 5, 3);
    addEdge(adjMatrix, vertices, 4, 6, 1);
    addEdge(adjMatrix, vertices, 5, 4, 2);
    addEdge(adjMatrix, vertices, 5, 6, 5);

    dijkstra(adjMatrix, vertices, 1);


    return 0;
}

