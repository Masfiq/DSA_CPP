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
        // matrix[j][i] = 1; // Remove this line for a directed graph
    }
}

// Function to display the adjacency matrix
void displayMatrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Bellman-Ford algorithm to find shortest paths from source vertex source
void bellmanFord(int** matrix, int vertices, int source) {
    int* distance = new int[vertices];

    // Initialize distances from source to all other vertices as INFINITE
    for (int i = 1; i < vertices; i++) {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;

    // Relax all edges |V| - 1 times
    for (int k = 0; k < vertices - 1; k++) {
        for (int u = 1; u < vertices; u++) {
            for (int v = 1; v < vertices; v++) {
                if (matrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + matrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + matrix[u][v];
                }
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

    // Initialize the adjacency matrix
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

    // Display the adjacency matrix
    std::cout << "Adjacency Matrix:" << std::endl;
    displayMatrix(adjMatrix, vertices);

    // Run Bellman-Ford algorithm
    bellmanFord(adjMatrix, vertices, 1);


    return 0;
}
