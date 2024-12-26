#define MAX_NAME 100
#define INT_MAX 10000000

typedef struct city {
    char name[MAX_NAME];
    int population, id;
} *p_city;

struct city createCity(char *name, int population, int id);

int searchCity(p_city cities, char *name, int numOfCities);

int *dijkstra(p_graph g, int cityId);

void getLeastMaxPair(p_city cities, int **matrix, int numOfCities, int *cityOneId, int *cityTwoId, int *leastMaxPair);