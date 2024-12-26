#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked.h"

#define MAX 100

int main() {
    p_node head = NULL;
    char option[MAX];
    char value;
    int index;
    /* menu */
    do {
        scanf("%s", option);
        if (strcmp(option, "inserir") == 0) {
            scanf(" %c %d", &value, &index);
            insertNodeAt(&head, value, index);
            printf("%c inserido em %d\n", value, index);
        } else if (strcmp(option, "remover") == 0) {
            scanf(" %d", &index);
            char character = removeNodeByIndex(&head, index);
            printf("%c removido de %d\n", character, index);
        } else if (strcmp(option, "inverter-prefixo") == 0) {
            scanf(" %d", &index);
            invertPrefix(&head, index);
        } else if (strcmp(option, "inverter-sufixo") == 0) {
            scanf(" %d", &index);
            invertSuffix(&head, index);
        } else if (strcmp(option, "transpor") == 0) {
            int p, q, r;
            scanf(" %d %d %d", &p, &q, &r);
            transpose(&head, p, q, r);
        } else if (strcmp(option, "imprimir") == 0) {
            printf("sequencia ");
            printList(head);
        }
    } while (strcmp(option, "sair") != 0);

    destroyList(head);

    return 0;
}
