#include <stdio.h>
#include <stdlib.h>
#include "expression.h"

#define MAX 4000

int main() {
    char input[MAX];
    scanf(" %s", input);

    char *expr = input;

    p_node root = readTree(&expr);
    printTree(root);
    printf("\n");

    root = DeMorgan(root);
    printTree(root);
    printf("\n");
    
    root = simplify(root);
    printTree(root);
    printf("\n");

    freeTree(root);
    return 0;
}
