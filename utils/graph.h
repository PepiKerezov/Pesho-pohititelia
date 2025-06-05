#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

// Vertex structure
typedef struct Vertex {
    void* data;
    struct Vertex* next;
    struct Edge* edges;  // List of edges from this vertex
} Vertex;

// Edge structure
typedef struct Edge {
    Vertex* destination;
    double weight;
    struct Edge* next;
} Edge;

// Graph structure
typedef struct {
    Vertex* vertices;
    size_t vertex_count;
} Graph;

// Function declarations
Graph* graph_create(void);
Vertex *  graph_add_vertex(Graph* graph, void* data);
Edge * graph_add_edge(Graph* graph, void* from_data, void* to_data, double weight);
void graph_print(const Graph* graph, void (*print_vertex)(const void*));
void graph_free(Graph* graph, void (*free_data)(void*));

// New function for building graph from matrix
Graph* graph_from_matrix(const int* matrix, size_t size, void** vertex_data);

#endif // GRAPH_H 