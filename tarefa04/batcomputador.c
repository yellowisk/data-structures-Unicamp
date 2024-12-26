#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

int main() {
	p_vector batMemory = createVector(START);

	int operationsNumber;
	scanf("%d", &operationsNumber);

	for (int i = 0; i < operationsNumber; i++) {
		char operation[MAX_OPERATION_LENGTH];
		scanf("%s", operation);

		if (strcmp(operation, "bat-alloc") == 0) {
			batAlloc(batMemory);
		} else if (strcmp(operation, "bat-free") == 0) {
			int index;
			scanf("%d", &index);
			/* batFree retunrs a value which tells us whether or not we
			 should divide teh memory in half */
            if (batFree(batMemory, index)) batMemory->allocated /= 2; 
		} else if (strcmp(operation, "bat-print") == 0) {
            int index;
            scanf("%d", &index);
            batPrint(batMemory, index);
        } else if (strcmp(operation, "bat-uso") == 0) {
            batUsage(batMemory);
        }
	}

    free(batMemory->numbers);
    free(batMemory);
	return 0;
}