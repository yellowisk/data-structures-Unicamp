#include <stdlib.h>
#include <stdio.h>
#include "arranger.h"

int main() {
    int c, n, m; //c size of cache, n numOfEls, m lenght of input
    scanf(" %d %d %d", &c, &n, &m);

    p_batch *bacthList = malloc(n * sizeof(p_batch));
    int *actions = malloc(m * sizeof(int));
    int *cachePositions = malloc(n * sizeof(int));
    p_queue cache = createCache(c);

    initalizeBatchList(bacthList, n, m, actions);
    resetBatch(bacthList, n, m);

    int insertions = 0;
    heapManager(bacthList, n, m, cache, &insertions, actions, cachePositions);

    printf("%d\n", insertions);

    freeBatch(bacthList, n);
    free(actions);
    free(cachePositions);
    cleanCache(cache);

    return 0;
}
