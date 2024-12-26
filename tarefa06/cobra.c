#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct snake_node {
    int i;
    int j;
    struct snake_node *next;
    struct snake_node *previous;
} *p_snake_node;

p_snake_node createSnakeNode(int **matrix, int i, int j, p_snake_node next, p_snake_node previous) {
    p_snake_node new_node = (p_snake_node) malloc(sizeof(struct snake_node));
    new_node->i = i;
    new_node->j = j;
    new_node->next = next;
    new_node->previous = previous;
    matrix[i][j] = 1;
    return new_node;
};

p_snake_node getTail(p_snake_node head) {
    while (head->previous != NULL) {
        head = head->previous;
    }
    return head;
}

void checkMove(p_snake_node head, int **matrix, int i, int j) {
    while (head != NULL) {
        if (head->i == i && head->j == j) {
            printf("GAME OVER\n");
            exit(0);
        }
        head = head->previous;
    }
}

void eatFruit(int **matrix, p_snake_node head) {
    p_snake_node tail = getTail(head);
    tail->previous = createSnakeNode(matrix, head->i, head->j, tail, NULL);
}

void moveSnake(int **matrix, p_snake_node *head, int m, int n, int i, int j) {
    int new_i = (*head)->i + i;
    int new_j = (*head)->j + j;

    if (!(0 <= new_i && new_i < m))
        new_i = (new_i > (m - 1)) ? m - ((*head)->i + i) : m + ((*head)->i + i);
    
    if (!(0 <= new_j && new_j < n))
        new_j = (new_j > (n - 1)) ? n - ((*head)->j + j) : n + ((*head)->j + j);

    checkMove(*head, matrix, new_i, new_j);
    p_snake_node tail = getTail(*head);

    if (tail != *head) {
        (*head)->next = tail;
        tail->next->previous = NULL;
        tail->previous = *head;
        tail->next = NULL;
        *head = tail;
    }

    if (matrix[new_i][new_j] != 2) { 
        matrix[(*head)->i][(*head)->j] = 0;
    } else { 
        eatFruit(matrix, *head);
    }
    matrix[new_i][new_j] = 1;
    (*head)->i = new_i;
    (*head)->j = new_j;
}

void populateMatrix(int **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));\
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
}

void printMatrix(int **matrix, int m, int n) {
    int nodeCounter = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            (matrix[i][j] == 0) ? printf("_ ") : 
            (matrix[i][j] == 1) ? printf("# ") : printf("* ");
            if (matrix[i][j] == 1) nodeCounter += 1;
        }
        printf("\n");
    }
    printf("\n");
    if (nodeCounter == m*n) printf("YOU WIN");
}

void initializeGame(int **matrix, int m, int n, int i, int j, int k, int l, p_snake_node *head) {
    populateMatrix(matrix, m, n);
    *head = createSnakeNode(matrix, i, j, NULL, NULL);
    scanf("FRUTA %d %d", &k, &l);
    matrix[k][l] = 2;
}

void freeMatrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    char command[MAX];
    int m, n, i, j, k, l;
    scanf("MATRIZ %d %d", &m, &n);
    scanf(" COBRA %d %d", &i, &j);
    scanf(" FRUTA %d %d", &k, &l);
    int **matrix = (int **)malloc(m * sizeof(int *));
    p_snake_node head = NULL;

    initializeGame(matrix, m, n, i, j, k, l, &head);
    printMatrix(matrix, m, n);

    /* MENU */
    do {
        if (scanf(" %s", command) == EOF) {
            break;
        }
        if (strcmp(command, "FRUTA") == 0) {
            int i, j;
            scanf(" %d %d", &i, &j);
            matrix[i][j] = 2;
        } else if (strcmp(command, "w") == 0) {
            moveSnake(matrix, &head, m, n, -1, 0);
        } else if (strcmp(command, "a") == 0) {
            moveSnake(matrix, &head, m, n, 0, -1);
        } else if (strcmp(command, "s") == 0) {
            moveSnake(matrix, &head, m, n, 1, 0);
        } else if (strcmp(command, "d") == 0) {
            moveSnake(matrix, &head, m, n, 0, 1);
        }
        printMatrix(matrix, m, n);
    } while (1);

    freeMatrix(matrix, m);
    return 0;
}
