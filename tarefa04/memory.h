#define START 8
#define MAX_OPERATION_LENGTH 10
#define IS_TIME_TO_DECREASE 1
#define NO_FREE_SPACE -1

typedef struct vector {
    int *numbers;
    int used;
    int allocated;
} *p_vector;

p_vector createVector(int size);

void addElement(p_vector v, int element, int index);

int findFreeSpace(p_vector vector, int numElements);

void doubleVector(p_vector v);

void batAlloc(p_vector batMemory);

int batFree(p_vector batMemory, int index);

void batPrint(p_vector batMemory, int index);

void batUsage(p_vector batMemory);