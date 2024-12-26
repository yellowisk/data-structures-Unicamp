#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

queueItem createItem(int distance, int id) { 
    return (queueItem) {distance, id}; 
}

p_queue createQueue(int numOfCities) {
    p_queue queue = (p_queue) malloc(sizeof(struct queue));
    queue->numOfCities = 0;
    queue->list = malloc(numOfCities * sizeof(queueItem));
    return queue;
}

void switchItem(queueItem *a, queueItem *b) {
    queueItem temp = *a;
    *a = *b;
    *b = temp;
}

void goUp(p_queue queue, int k) {
    /* if the parent is greater than the child, I switch both of their positions,
    so that its child goes up */
    if (k > 0 && queue->list[PARENT(k)].distance > queue->list[k].distance) {
        switchItem(&queue->list[k], &queue->list[PARENT(k)]);
        goUp(queue, PARENT(k));
    }
}

void goDown(p_queue queue, int position) {
    int greatestChild;
    if (C_LEFT(position) < queue->numOfCities) {  // has left child
        greatestChild = C_LEFT(position);         // child that'll go up
        if (C_RIGHT(position) < queue->numOfCities && queue->list[C_LEFT(position)].distance >
                queue->list[C_RIGHT(position)].distance) {
            /* if the right child is less than the left one,
             the right one will be the child that'll go up */
            greatestChild = C_RIGHT(position);
        }
        if (queue->list[position].distance > queue->list[greatestChild].distance) {
            /* if the parent is greater than the child, I switch both of their positions,
            so that its child goes up */
            switchItem(&queue->list[position], &queue->list[greatestChild]);
            goDown(queue, greatestChild);
        }
    }
}

void insertInQueue(p_queue queue, queueItem item) {
    queue->list[queue->numOfCities] = item;
    queue->numOfCities++;
    goUp(queue, queue->numOfCities - 1);
}

queueItem extractMin(p_queue queue) {
    queueItem item = queue->list[0]; /* the one with least priority */
    switchItem(&queue->list[0], &queue->list[queue->numOfCities - 1]); /* switch with the last one */
    /* decrease the number of elements, so that the last 
    one can be overwritten when adding a new item */
    queue->numOfCities--;
    /* since I put the last item at the top, I gotta put 
    it in its right place, if that's the case */
    goDown(queue, 0);
    return item;
}

void changePriority(p_queue queue, int k, int value) {
    if (queue->list[k].distance < value) {
        /* if the new value is greater than the old one, 
        it's less prioritary, so I make it go down the queue */
        queue->list[k].distance = value;
        goDown(queue, k);
    } else {
        /* if the new value is less than the old one,
        it's more prioritary, so I make it go up the queue */
        queue->list[k].distance = value;
        goUp(queue, k);
    }
}

int searchId(p_queue queue, int numOfCities, int id) {
    for (int i = 0; i < numOfCities; i++)
        if (queue->list[i].id == id) return i; // returning the position of the item with this id
    return -1;
}

int priority(p_queue queue, int numOfCities, int id) {
    int foundId = searchId(queue, numOfCities, id);
    return (foundId == -1) ? foundId : queue->list[foundId].distance;
}