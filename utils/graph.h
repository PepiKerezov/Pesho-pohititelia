#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

// Vertex structure
typedef struct Vertex {
    int id;
    void* data;
    struct Vertex* next;
    struct Vertex* parent;
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
void graph_free(Graph* graph, void (*free_data)(void*));

#endif // GRAPH_H 