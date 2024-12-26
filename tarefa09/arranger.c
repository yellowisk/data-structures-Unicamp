#include <stdlib.h>
#include <stdio.h>
#include "arranger.h"

Item createItem(int value, int key) {
    Item item = {value, key};
    return item;
}

p_queue createCache(int numAllocated) {
    p_queue queue = malloc(sizeof(struct queue));
    queue->numAllocated = numAllocated;
    queue->numElements = 0;
    queue->vector = malloc(numAllocated * sizeof(Item));
    return queue;
}

p_batch createBatch(int numPositions, int priority, int currentPosition, int isCached) {
    p_batch batch = malloc(sizeof(struct batch));
    batch->positions = malloc(numPositions * sizeof(int));
    batch->priority = priority;
    batch->currentPosition = currentPosition;
    batch->isCached = isCached;
    return batch;
}

void switchItem(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}


void goDown(p_queue queue, int k, int *cachePositions) {
    int biggestChild, child;
    if (C_LEFT(k) < queue->numElements) { // has left child
        biggestChild = C_LEFT(k); // child that'll go up
        child = 1;
        if (C_RIGHT(k) < queue->numElements && queue->vector[C_LEFT(k)].key < queue->vector[C_RIGHT(k)].key) {
            /* if the right child is greater than the left one, it'll be the child that'll go up */
            biggestChild = C_RIGHT(k);
            child = 2;
        }
        if (queue->vector[k].key < queue->vector[biggestChild].key) {
            /* if the parent is greater than the child, I switch both of their positions,
            so that its child goes up */
            if (child == 1) { // left one will go up
                cachePositions[queue->vector[k].value] = biggestChild;
                cachePositions[queue->vector[biggestChild].value] = k;
            } else { // right one will go up
                cachePositions[queue->vector[biggestChild].value] = k;
                cachePositions[queue->vector[k].value] = biggestChild;
            }
            switchItem(&queue->vector[k], &queue->vector[biggestChild]);
            goDown(queue, biggestChild, cachePositions);
        }
    }
}


void goUp(p_queue queue, int k, int *cachePositions) {
    /* if the parent is greater than the child, I switch both of their positions,
    so that its child goes up */
    if (k > 0 && queue->vector[PARENT(k)].key < queue->vector[k].key) {
        cachePositions[queue->vector[k].value] = PARENT(k);
        cachePositions[queue->vector[PARENT(k)].value] = k;
        switchItem(&queue->vector[k], &queue->vector[PARENT(k)]);
        goUp(queue, PARENT(k), cachePositions);
    }
}

void insert(p_queue queue, Item item, int *cachePositions) {
    queue->vector[queue->numElements] = item;
    cachePositions[item.value] = queue->numElements;
    queue->numElements++;
    goUp(queue, queue->numElements - 1, cachePositions);
}

 void changePriority(p_queue queue, int k, int value, int *cachePositions) {
    if (queue->vector[k].key < value) {
        /* if the new value is greater than the old one, 
        it's more prioritary, so I make it go up the queue */
        queue->vector[k].key = value;
        goUp(queue, k, cachePositions);
    } else {
        /* if the new value is less than the old one,
        it's less prioritary, so I make it go down the queue */
        queue->vector[k].key = value;
        goDown(queue, k, cachePositions);
    }
}

Item extractMax(p_queue queue, int *cachePositions) {
    Item item = queue->vector[0];
    switchItem(&queue->vector[0], &queue->vector[queue->numElements - 1]);
    /* decrease the number of elements, so that the last 
    one can be overwritten when adding a new item */
    queue->numElements--;
    /* since I put the last item at the top, I gotta put 
    it in its right place, if that's the case */
    goDown(queue, 0, cachePositions);
    return item;
}

void freeBatch(p_batch *batchList, int m) {
    for (int i = 0; i < m; i++) {
        free(batchList[i]->positions);
        free(batchList[i]);
    }
    free(batchList);
}

void cleanCache(p_queue queue) {
    free(queue->vector);
    free(queue);
}

void insertAllInBatchList(p_batch *batchList, int n, int m, int *actions, int *quantity) {
    for (int i = 0; i < m; i++) {
        int value;
        scanf("%d", &value);
        /* here we increase the current position we are in the
        batch stored in the index 'value' of the batchList
        and add the position the value was last called */
        actions[i] = value;
        quantity[value]++;
    }
    for (int i = 0; i < n; i++) {
        batchList[i] = createBatch(quantity[i] + 1, 0, 0, 0);
    }
    free(quantity);
    for (int i = 0; i < m; i++) {
        batchList[actions[i]]->positions[batchList[actions[i]]->currentPosition++] = i;
        batchList[actions[i]]->isCached = 1;
    }
}

void initalizeBatchList(p_batch *batchList, int n, int m, int *actions) {
    int *quantity = calloc(n, sizeof(int));
    insertAllInBatchList(batchList, n, m, actions, quantity);
}

void resetBatch(p_batch *batchList, int n, int m) {
    for (int i = 0; i < n; i++) {
        batchList[i]->positions[batchList[i]->currentPosition] = m + 1;
        batchList[i]->currentPosition = 0;
        batchList[i]->isCached = 0;
    }
}

void heapManager(p_batch *batchList, int n, int m, p_queue queue, int *insertions, int *actions, int *cachePositions) {
    for (int i = 0; i < m; i++) {
        int pos = actions[i];
        if (!batchList[pos]->isCached && queue->numElements == queue->numAllocated) {
            /* if the cache is full and the element is not cached, 
            we remove from the heap the element with highest priority/weight */
            Item item = extractMax(queue, cachePositions);
            batchList[item.value]->isCached = 0;
            batchList[pos]->currentPosition++;
            insert(queue, createItem(pos, batchList[pos]->positions[batchList[pos]->currentPosition]), cachePositions);
            batchList[pos]->isCached = 1;
            (*insertions)++;
        } else {
            if (!batchList[pos]->isCached) {
                /* if the element is not cached, we insert it in the heap */
                batchList[pos]->currentPosition++;
                insert(queue, createItem(pos, batchList[pos]->positions[batchList[pos]->currentPosition]), cachePositions);
                batchList[pos]->isCached = 1;
                (*insertions)++;
            } else {
                /* if the element is already cached, we change its priority */
                batchList[pos]->currentPosition++;
                changePriority(queue, cachePositions[pos], batchList[pos]->positions[batchList[pos]->currentPosition], cachePositions);
            }
        }
    }
}