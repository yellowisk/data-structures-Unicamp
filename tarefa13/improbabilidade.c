#include <stdio.h>
#include <stdlib.h>

typedef struct Lever {
    int weight, leverIndex;
    char direction;
    struct Lever *next;
} *p_lever;

p_lever createLever(p_lever next, char direction, int leverIndex,
                 int weight) {
    p_lever lever = (p_lever)malloc(sizeof(struct Lever));
    lever->direction = direction;
    lever->leverIndex = leverIndex;
    lever->weight = weight;
    lever->next = next;
    return lever;
}

void destroyLevers(p_lever levers) {
    if (levers != NULL) {
        destroyLevers(levers->next);
        free(levers);
    }
}

void destroyCircuits(p_lever *circuitSequence, int numOfCircuits) {
    for (int i = 0; i < numOfCircuits; i++)
        destroyLevers(circuitSequence[i]);
    free(circuitSequence);
}

int calcImprobability(char *leverSequence, int numOfCircuits, p_lever *circuitSequence) {
    int improbability = 0;
    for (int i = 0; i < numOfCircuits; i++)
        for (p_lever current = circuitSequence[i]; current != NULL; current = current->next) {
            if (leverSequence[current->leverIndex] == current->direction) {
                /* If the direction is equal, we know the lever will be activated and we can
                already consider the weight of the circuit, I guess */
                improbability += current->weight;
                break;
            }
        }
    return improbability;
}

void getBestSequence(int numOfCircuits, p_lever *circuitSequence, int *maxProbability, char *bestSequence, char *levers, int currentLever, int numOfLevers) {
    if (currentLever == numOfLevers) { /* When the sequence/combination is completely formed */
        int improbabilty = calcImprobability(levers, numOfCircuits, circuitSequence);
        if (improbabilty > *maxProbability) {
            *maxProbability = improbabilty;
            for (int i = 0; i < numOfLevers; i++) {
                bestSequence[i] = levers[i];
            }
        }
        return;
    }

    /* If we ain't at the end of the circuit's levers yet, we increment the index of the sequence.
    By using recursion here, we end up testing all possibilites */
    levers[currentLever] = '-'; /* try with a '-' at this position of the sequence */
    getBestSequence(numOfCircuits, circuitSequence, maxProbability, bestSequence, levers, currentLever + 1, numOfLevers);
    levers[currentLever] = '+'; /* Then with a '+* */
    getBestSequence(numOfCircuits, circuitSequence, maxProbability, bestSequence, levers, currentLever + 1, numOfLevers);
}

void printBestSequence(char *leverSequence, int numOfLevers) {
    for (int i = 0; i < numOfLevers; i++)
        printf("%c%d ", leverSequence[i], i);
    printf("\n");
}

int main() {
    int numOfCircuits, numOfLevers;
    scanf(" %d %d", &numOfCircuits, &numOfLevers);

    /* Here I'm basically creating a list of linked lists, 
    just like in a hash table. In some way, this works like a matrix */
    p_lever *circuitsSequence = (p_lever *)malloc(numOfCircuits * sizeof(p_lever));
    for (int i = 0; i < numOfCircuits; i++) {
        circuitsSequence[i] = NULL;
    }

    /* Storing the circuit data.... */
    for (int i = 0; i < numOfCircuits; i++) {
        int weight, numOfLevers, leverIndex;
        char direction;
        scanf(" %d %d", &weight, &numOfLevers);
        for (int j = 0; j < numOfLevers; j++) {
            scanf(" %c%d", &direction, &leverIndex);
            p_lever next = circuitsSequence[i];
            circuitsSequence[i] = createLever(next, direction, leverIndex, weight);
        }
    }

    int bestImprobability = 0;
    char *bestLeverSequence = (char *)malloc(sizeof(char) * numOfLevers);
    char *levers = (char *)malloc(sizeof(char) * numOfLevers);

    getBestSequence(numOfCircuits, circuitsSequence, &bestImprobability, bestLeverSequence, levers, 0, numOfLevers);
    printf("%d\n", bestImprobability);
    printBestSequence(bestLeverSequence, numOfLevers);

    free(bestLeverSequence);
    free(levers);
    destroyCircuits(circuitsSequence, numOfCircuits);
    return 0;
}