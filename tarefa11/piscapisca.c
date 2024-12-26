#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATUS_LENGTH 10

enum Status {
    ON,
    OFF,
    DEAD,
    NONE
};

void getStatus(enum Status s, char response[MAX_STATUS_LENGTH]) {
    if (s == ON)
        strcpy(response, "acesa");
    else if (s == OFF)
        strcpy(response, "apagada");
    else
        strcpy(response, "queimada");
}

typedef struct LampData {
    int id, distance;
    enum Status status;
} LampData;

typedef struct LampList {
    LampData data;
    struct LampList *next;
} *p_lampList;

typedef struct Graph {
    int n;
    int **adj;
} *p_graph;

typedef struct Stack {
    p_lampList top;
} *p_stack;

typedef struct Queue {
    p_lampList first, last;
} *p_queue;

p_graph createGraph(int n) {
    int i, j;
    p_graph g = (p_graph)malloc(sizeof(struct Graph));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        g->adj[i] = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0;
    return g;
}

p_queue createQueue() {
    p_queue q;
    q = malloc(sizeof(struct Queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}

LampData createLamp(int id, int distance, enum Status status) {
    LampData lamp;
    lamp.id = id;
    lamp.distance = distance;
    lamp.status = status;
    return lamp;
}

void destroyGraph(p_graph g) {
    int i;
    for (i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

void destroyList(p_lampList lamp) {
    if (lamp) {
        destroyList(lamp->next);
        free(lamp);
    }
}

void destroyStack(p_stack stack) {
    p_lampList current = stack->top;
    while (current != NULL) {
        p_lampList temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}

void destroyQueue(p_queue q) {
    destroyList(q->first);
    free(q);
}

void enqueue(p_queue q, LampData data) {
    p_lampList lamp;
    lamp = malloc(sizeof(struct LampList));
    lamp->data = data;
    lamp->next = NULL;
    if (q->first == NULL)
        q->first = lamp;
    else
        q->last->next = lamp;
    q->last = lamp;
}

int dequeue(p_queue q) {
    p_lampList first = q->first;
    int x = first->data.id;
    q->first = q->first->next;
    if (q->first == NULL)
        q->last = NULL;
    free(first);
    return x;
}

p_stack createStack() {
    p_stack stack = (p_stack)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

void stack(p_stack heap, LampData lamp) {
    p_lampList head = malloc(sizeof(struct LampList));
    head->data = lamp;
    head->next = heap->top;
    heap->top = head;
}

LampData unstack(p_stack stack) {
    LampData topCopy = stack->top->data;
    p_lampList top = stack->top;
    stack->top = stack->top->next;
    free(top);
    return topCopy;
}

int isStackEmpty(p_stack stack) {
    if (!stack->top)
        return 1;
    return 0;
}

int isQueueEmpty(p_queue q) {
    if (!q->first)
        return 1;
    return 0;
}

void insertEdge(p_graph g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

int isInList(LampData *lamps, int listSize, int id) {
    for (int i = 0; i < listSize; i++)
        if (lamps[i].id == id) return 1;
    return 0;
}

int findCycle(p_graph g, int origin, int v, int parent, int *visitedInCycle, p_stack deadStack, LampData *lamps, int *distances) {
    /* Tests a path till its end (like a in a DFS) while tryna find out whether it forms a cycle */
    visitedInCycle[v] = 1;
    for (int w = 0; w < g->n; w++)
        if (g->adj[v][w]) {
            if (!visitedInCycle[w]) { /* If adjancency exists and the node w hasn't been visited yet */
                if (findCycle(g, origin, w, v, visitedInCycle, deadStack, lamps, distances)) { 
                    /* If `findCycle` returns true, we mark the node w as DEAD*/
                    lamps[w] = createLamp(w, distances[v], DEAD);
                    stack(deadStack, lamps[w]);
                    return 1;
                }
            } else if (w != parent && w == origin) { /* When we find the node that closes teh cycle */
                lamps[w] = createLamp(w, distances[v], DEAD); /* Setting it as DEAD */
                stack(deadStack, lamps[w]);
                return 1;
            }
        }
    if (!isInList(lamps, g->n, v)) 
        /* If it ain't in a cycle and isn't on the list, we create the lamp nnode */
        lamps[v] = createLamp(v, distances[v], ON);
    return 0; /*If ther'es no cycle */
}

int isInCycle(p_stack deadStack, int id) {
    for (p_lampList top = deadStack->top; top; top = top->next)
        if (top->data.id == id)
            return 1;
    return 0;
}

LampData *breadthSearch(p_graph g, int x, LampData *lamps, LampData *orderedLamps, p_stack deadStack, int *distances, int *listCounter) {
    int *parents = malloc(g->n * sizeof(int));
    int *visited = malloc(g->n * sizeof(int));
    p_queue q = createQueue();

    for (int i = 0; i < g->n; i++) {
        visited[i] = 0;
        parents[i] = -1;
        lamps[i] = createLamp(-1, -1, NONE);
        distances[i] = -1;
        orderedLamps[i] = createLamp(-1, -1, NONE);
    }

    parents[x] = x;
    visited[x] = 1;
    distances[x] = 0;
    lamps[x] = createLamp(x, 0, ON); /* Making sure the origin lamp exists */
    orderedLamps[*listCounter] = lamps[x];
    enqueue(q, lamps[x]);

    for (int i = 0; i < g->n; i++) {
        int *visitedInCycle = malloc(g->n * sizeof(int));
        if (isInCycle(deadStack, i)) { /* Prevents creating redundant cycles */
            free(visitedInCycle);
            continue;
        } else {
            for (int j = 0; j < g->n; j++)
                visitedInCycle[j] = 0;
            findCycle(g, i, i, -1, visitedInCycle, deadStack, lamps, distances);
        }
        free(visitedInCycle);
    }

    while (!isQueueEmpty(q)) {
        int v = dequeue(q);

        /* Here we get the distances and set it along with some other operations */
        for (int w = 0; w < g->n; w++)
            if (g->adj[v][w] && !visited[w]) {
                visited[w] = 1;
                parents[w] = v;
                distances[w] = distances[v] + 1;
                lamps[w].distance = distances[w];
                /* If a lamp node is next to a DEAD or OFF one, it becomes OFF */
                if (lamps[w].status == ON && (lamps[parents[w]].status == DEAD || lamps[parents[w]].status == OFF))
                    lamps[w].status = OFF;
                /* Adding to the orderedLamps list in the order of the queue operations */
                orderedLamps[++(*listCounter)] = lamps[w];
                enqueue(q, lamps[w]);
            }
    }

    if (isInCycle(deadStack, x)) { /* Makes sure the origin is DEAD if it's in a cycle */
        for (int i = 0; i < *listCounter; i++) {
            if (orderedLamps[i].id == x) {
                orderedLamps[i].status = DEAD;
                break;
            }
        }
    }

    free(visited);
    free(parents);
    destroyGraph(g);
    destroyQueue(q);
    free(lamps);
    return orderedLamps;
}

void selectionsort(LampData *lamps, int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (lamps[j].distance == lamps[min].distance && lamps[j].id < lamps[min].id)
                min = j;
        LampData temp = lamps[i];
        lamps[i] = lamps[min];
        lamps[min] = temp;
    }
}

int main() {
    int numOfLamps, numOfConnections, sourceLampId;
    scanf(" %d %d %d", &numOfLamps, &numOfConnections, &sourceLampId);
    p_graph graph = createGraph(numOfLamps);

    for (int i = 0; i < numOfConnections; i++) {
        int originId, destinyId;
        scanf(" %d %d", &originId, &destinyId);
        insertEdge(graph, originId, destinyId);
    }

    int listCounter = 0;
    p_stack deadStack = createStack();
    int *distances = malloc(numOfLamps * sizeof(int));
    LampData *lamps = malloc(numOfLamps * sizeof(struct LampData));
    LampData *orderedLamps = malloc(numOfLamps * sizeof(struct LampData));

    orderedLamps = breadthSearch(graph, sourceLampId, lamps, orderedLamps, deadStack, distances, &listCounter);
    selectionsort(orderedLamps, listCounter + 1); /* Sorting by id */

    for (int i = 0; i < listCounter + 1; i++) {
        char status[MAX_STATUS_LENGTH];
        getStatus(orderedLamps[i].status, status);
        printf("%d a distancia %d: %s\n", orderedLamps[i].id, orderedLamps[i].distance, status);
    }

    free(orderedLamps);
    destroyStack(deadStack);
    free(distances);

    return 0;
}
