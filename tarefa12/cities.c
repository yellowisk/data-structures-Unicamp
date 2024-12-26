#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "heap.h"
#include "cities.h"

struct city createCity(char *name, int population, int id) {
    struct city city;
    city.id = id;
    city.population = population;
    strcpy(city.name, name);
    return city;
}

int searchCity(p_city cities, char *name, int numOfCities) {
    for (int i = 0; i < numOfCities; i++)
        if (strcmp(cities[i].name, name) == 0) return cities[i].id;
    return -1;
}

int *dijkstra(p_graph g, int cityId) {
    /* With Dijkstra, I find the shortest path 
    from a city to the others... I'm storing the distance
    from these shortest paths in a list, that is in order of
    addition of the cities I got from the input */
    int vertex;
    int *parent = malloc(g->n * sizeof(int)); // list of distances
    p_node node;
    p_queue queue = createQueue(g->n);

    for (vertex = 0; vertex < g->n; vertex++) {
        /* I insert all the cities in the queue with priority INT_MAX...
        Will be changed later */
        parent[vertex] = INT_MAX;
        insertInQueue(queue, createItem(INT_MAX, vertex));
    }

    parent[cityId] = 0; /* top city has to have the least priority */
    changePriority(queue, cityId, 0); /* changing the priority of the top city */
    while (queue->numOfCities) {
        vertex = extractMin(queue).id; /* getting the city with least priority, the top one */
        if (priority(queue,g->n, vertex) != INT_MAX) { /* if the vertex can be reached */
            for (node = g->adj[vertex]; node != NULL; node = node->next) {
                if (priority(queue, g->n, vertex) + node->weight < priority(queue, g->n, node->vertex)) {
                    /* If the top the searched vertex has a higher priority than the top vertex + the weight of the edge */
                    changePriority(queue, searchId(queue,g->n, node->vertex),
                                   priority(queue, g->n, vertex) + node->weight);
                    parent[node->vertex] = priority(queue,g->n, vertex) + node->weight;
                }
            }
        }
    }
    free(queue->list);
    free(queue);
    return parent;
}

void getLeastMaxPair(p_city cities, int **matrix, int numOfCities, int *cityOneId, int *cityTwoId, int *leastMaxPair) {
    /* Here, I'm going to find the pair of cities that has the least maximum distance.
    Basically, I test each pair of cities and them check if their 'worst' minimum distance
    of shipping is less than any of the other ones I found in previous pairs. If so, I set it
    as the new least maximum distance. If there's a draw, then I just follow the rule of checking
    which pair has the biggest population. */
    for (int i = 0; i < numOfCities; i++) {
        for (int j = i + 1; j < numOfCities; j++) {
            int greatestMinPair = -1;
            for (int k = 0; k < numOfCities; k++) {
                int minPair = (matrix[i][k] > matrix[j][k]) ? matrix[j][k] : matrix[i][k];
                if (minPair > greatestMinPair) greatestMinPair = minPair;
            }

            if (greatestMinPair < *leastMaxPair ) {
                *leastMaxPair = greatestMinPair;
                *cityOneId = i;
                *cityTwoId = j;
            }

            if (greatestMinPair == *leastMaxPair) {
                int previousPopSum = cities[*cityOneId].population + cities[*cityTwoId].population;
                int newPopSum = cities[i].population + cities[j].population;
                if (newPopSum > previousPopSum) {
                    *cityOneId = i;
                    *cityTwoId = j;
                }
            }
        }
    }
}