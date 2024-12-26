#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "graph.h"
#include "cities.h"

int main() {
    int numOfCities, numOfPaths;
    scanf(" %d", &numOfCities);
    p_graph graph = createGraph(numOfCities);

    p_city cities = malloc(numOfCities * (sizeof(struct city)));

    // storing the cities
    for (int i = 0; i < numOfCities; i++) {
        char name[MAX_NAME];
        int population;
        scanf(" %s %d", name, &population);
        cities[i] = createCity(name, population, i);
    }

    // storing the paths
    scanf(" %d", &numOfPaths);
    for (int i = 0; i < numOfPaths; i++) {
        int distance;
        char cityOne[MAX_NAME], cityTwo[MAX_NAME];
        scanf("%s %s %d", cityOne, cityTwo, &distance);
        int cityOnePos = searchCity(cities, cityOne, numOfCities);
        int cityTwoPos = searchCity(cities, cityTwo, numOfCities);

        insertEdge(graph, cityOnePos, cityTwoPos, distance);
    }

    int **matrix = malloc(numOfCities * sizeof(int *));
    for (int i = 0; i < numOfCities; i++) {
        matrix[i] = dijkstra(graph, i); // Mapping the distances from city i to the others
    }

    int leastMaxPair = INT_MAX, cityOneId = 0, cityTwoId = 1;
    getLeastMaxPair(cities, matrix, numOfCities, &cityOneId, &cityTwoId, &leastMaxPair);

    printf("Centros de distribuicao: %s e %s\n", cities[cityOneId].name,
           cities[cityTwoId].name);
    printf("Distancia de atendimento: %d\n", leastMaxPair);

    for (int i = 0; i < numOfCities;i++){
        free(matrix[i]);
    }
    free(matrix);
    destroyGraph(graph);
    free(cities);

    return 0;
}