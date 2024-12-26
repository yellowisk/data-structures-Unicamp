typedef struct node {
    int vertex;
    int weight;
    struct node *next;
} *p_node;

typedef struct graph {
    int n;
    p_node *adj;
} *p_graph;

p_graph createGraph(int numOfCities);

p_node insertInList(p_node head, int vertex, int weight);

void insertEdge(p_graph g, int u, int v, int weight);

void freeList(p_node head);

void destroyGraph(p_graph g);