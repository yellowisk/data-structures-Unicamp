#define PARENT(i) ((i - 1)/2)
#define C_LEFT(i) (2*i + 1)
#define C_RIGHT(i) (2*i + 2)

typedef struct {
    int distance, id; // distance will be the priority
} queueItem;

typedef struct queue {
    queueItem *list;
    int numOfCities;
} *p_queue;

queueItem createItem(int distance, int id);

p_queue createQueue(int numOfCities);

void switchItem(queueItem *a, queueItem *b);

void goUp(p_queue queue, int k);

void goDown(p_queue queue, int position);

void insertInQueue(p_queue queue, queueItem item);

queueItem extractMin(p_queue queue);

void changePriority(p_queue queue, int k, int value);

int searchId(p_queue queue, int numOfCities, int id);

int priority(p_queue queue, int numOfCities, int id);