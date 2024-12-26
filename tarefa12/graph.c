#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

p_graph createGraph(int numOfCities) {
    p_graph g = malloc(sizeof(struct graph));
    g->n = numOfCities;
    g->adj = malloc(numOfCities * sizeof(p_node));
    for (int i = 0; i < numOfCities; i++) g->adj[i] = NULL;
    return g;
}

p_node insertInList(p_node head, int vertex, int weight) {
    p_node new = malloc(sizeof(struct node));
    new->next = head;
    new->vertex = vertex;
    new->weight = weight;
    return new;
}

void insertEdge(p_graph g, int u, int v, int weight) {
    /* Always inserting at the head!!! */
    g->adj[v] = insertInList(g->adj[v], u, weight);
    g->adj[u] = insertInList(g->adj[u], v, weight);
}

void freeList(p_node head) {
    if (head != NULL) {
        freeList(head->next);
        free(head);
    }
}
void destroyGraph(p_graph g) {
    for (int i = 0; i < g->n; i++) freeList(g->adj[i]);
    free(g->adj);
    free(g);
}