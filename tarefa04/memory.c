#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

p_vector createVector(int size) {
    p_vector v = (p_vector) malloc(sizeof(struct vector));
    v->numbers = malloc(size * sizeof(int));
    for (int i = 0; i < START; i++)
        v->numbers[i] = 0;
    v->used = 0;
    v->allocated = size;
    return v;
}

void addElement(p_vector v, int element, int index) {
    v->numbers[index] = element;
    v->used++;
}

int findFreeSpace(p_vector vector, int numElements) {
    int counter = 0;
    int start = NO_FREE_SPACE;
    
    for (int i = 0; i < vector->allocated; i++) {
        if (vector->numbers[i] == 0) {
            if (counter == 0) start = i; // defines this index as the start of the free space
            counter++;
            if (counter == numElements + 1) return start; // if there's enough free space, we return the start index
        } else {
            counter = 0;
            start = NO_FREE_SPACE;
        }
    }
    return NO_FREE_SPACE;
}

void doubleVector(p_vector v) {
    int *tempNumbers = v->numbers;
    v->allocated *= 2;
    v->numbers = malloc(v->allocated * sizeof(int));
    
    for (int i = 0; i < v->allocated; i++)
        v->numbers[i] = (i < v->allocated/2) ? tempNumbers[i] : 0;
    free(tempNumbers);
}

void batAlloc(p_vector batMemory) {
	int numElements, free_space_index;
	scanf("%d", &numElements);
	
    int* listOfElements = (int *) malloc((numElements + 1) * sizeof(int));
    listOfElements[0] = numElements;

    for (int j = 0; j < numElements; j++) {
        int element;
        scanf("%d", &element);
        listOfElements[j + 1] = element;
    }

    free_space_index = findFreeSpace(batMemory, numElements);

    if (free_space_index == -1) {
        /* Here I verify if there's enough space in the vector to store the new elements */
        doubleVector(batMemory);
        free_space_index = findFreeSpace(batMemory, numElements);
    }

    for (int j = 0; j < numElements + 1; j++)
        addElement(batMemory, listOfElements[j], free_space_index + j);

    free(listOfElements);
    printf("%d\n", free_space_index);
}

int batFree(p_vector batMemory, int index) {
    int counter = 0;
    int numElements = batMemory->numbers[index];
    for (int i = 0; i < numElements + 1; i++) {
        batMemory->numbers[index + i] = 0;
        batMemory->used--;
    }

    for (int i = batMemory->allocated/4; i < batMemory->allocated; i++)
        if (batMemory->numbers[i] == 0) counter++; // counting the number of free spaces

    if (counter == ((batMemory->allocated/4)*3) && batMemory->allocated != START)
        return IS_TIME_TO_DECREASE; // if 3/4 of the vector is free, we can decrease its size

    return !IS_TIME_TO_DECREASE;
}

void batPrint(p_vector batMemory, int index) {
    int j = 0;
    for (int i = index + 1; j < batMemory->numbers[index]; i++) {
        printf("%d ", batMemory->numbers[i]);
        j++;
    }
    printf("\n");
}

void batUsage(p_vector batMemory) {
    printf("%d de %d\n", batMemory->used, batMemory->allocated);
}