#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph* graph_create(void) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph != NULL) {
        graph->vertices = NULL;
        graph->vertex_count = 0;
    }
    return graph;
}

Vertex* graph_add_vertex(Graph* graph, void* data) {
    if (graph == NULL) return NULL;

    Vertex* new_vertex = (Vertex*)malloc(sizeof(Vertex));
    if (new_vertex == NULL) return NULL;

    new_vertex->data = data;
    new_vertex->next = graph->vertices;
    new_vertex->parent = NULL;
    new_vertex->edges = NULL;

    // Set the id
    new_vertex->id = graph->vertex_count;  // assign current count as id

    // Add vertex to graph
    graph->vertices = new_vertex;
    graph->vertex_count++;

    return new_vertex;
}


Edge* graph_add_edge(Graph* graph, void* from_data, void* to_data, double weight) {
    if (graph == NULL) return NULL;

    Vertex* from_vertex = NULL;
    Vertex* to_vertex = NULL;
    Vertex* current = graph->vertices;

    while (current != NULL) {
        if (current->data == from_data) {
            from_vertex = current;
        }
        if (current->data == to_data) {
            to_vertex = current;
        }
        current = current->next;
    }

    if (from_vertex == NULL || to_vertex == NULL) return NULL;

    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    if (new_edge == NULL) return NULL;

    new_edge->destination = to_vertex;
    new_edge->weight = weight;
    new_edge->next = from_vertex->edges;
    from_vertex->edges = new_edge;

    return new_edge;
}

void graph_free(Graph* graph, void (*free_data)(void*)) {
    if (graph == NULL) return;

    Vertex* current_vertex = graph->vertices;
    while (current_vertex != NULL) {
        Edge* current_edge = current_vertex->edges;
        while (current_edge != NULL) {
            Edge* next_edge = current_edge->next;
            free(current_edge);
            current_edge = next_edge;
        }
        current_vertex = current_vertex->next;
    }

    current_vertex = graph->vertices;
    while (current_vertex != NULL) {
        Vertex* next_vertex = current_vertex->next;
        if (free_data != NULL && current_vertex->data != NULL) {
            free_data(current_vertex->data);
        }
        free(current_vertex);
        current_vertex = next_vertex;
    }

    free(graph);
}

