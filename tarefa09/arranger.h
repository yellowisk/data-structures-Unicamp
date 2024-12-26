#define PARENT(i) ((i - 1)/2)
#define C_LEFT(i) (2*i + 1)
#define C_RIGHT(i) (2*i + 2)

typedef struct {    
    int value; // value of the element
    int key; // priority of the element
} Item;

typedef struct queue {
    Item *vector;
    int numElements, numAllocated;
} *p_queue;

typedef struct batch {
    int *positions;
    int priority, currentPosition, isCached;
} *p_batch;

Item createItem(int value, int key);

p_queue createCache(int numAllocated);

p_batch createBatch(int numPositions, int priority, int currentPosition, int isCached);

void switchItem(Item *a, Item *b);


void goDown(p_queue queue, int k, int *cachePositions);


void goUp(p_queue queue, int k, int *cachePositions);

void insert(p_queue queue, Item item, int *cachePositions);

 void changePriority(p_queue queue, int k, int value, int *cachePositions);

Item extractMax(p_queue queue, int *cachePositions);

void freeBatch(p_batch *batchList, int m);

void cleanCache(p_queue queue);

void insertAllInBatchList(p_batch *batchList, int n, int m, int *actions, int *quantity);

void initalizeBatchList(p_batch *batchList, int n, int m, int *actions);

void resetBatch(p_batch *batchList, int n, int m);

void heapManager(p_batch *batchList, int n, int m, p_queue queue, int *insertions, int *actions, int *cachePositions);