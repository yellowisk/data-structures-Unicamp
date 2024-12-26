#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_DIVIDED 1
#define MAX_NAME 100
#define COMMAND_LENGTH 1

enum RegionType {
    NW,
    NE,
    SW,
    SE
};

typedef struct Dot {
    int x, y;
    char name[MAX_NAME];
} *p_dot;

typedef struct Region {
    int x, y, width, height, isDivided;
    struct Region *NW, *NE, *SW, *SE;
    enum RegionType type;
    p_dot dot;
} *p_region;

void freeTree(p_region root) {
    if (!root) return;
    freeTree(root->NE);
    freeTree(root->NW);
    freeTree(root->SE);
    freeTree(root->SW);
    free(root->dot);
    free(root);
}

p_region createNode(p_region ne, p_region nw, p_region se, p_region sw,
 int x, int y, int width, int height, int isDivided, enum RegionType type,
 p_dot dot) {
    p_region node = (p_region)malloc(sizeof(struct Region));
    node->NE = ne;
    node->NW = nw;
    node->SE = se;
    node->SW = sw;
    node->x = x;
    node->y = y;
    node->width = width;
    node->height = height;
    node->isDivided = !IS_DIVIDED;
    node->type = type;
    node->dot = dot;
    return node;
}

p_dot createDot(int x, int y, char name[MAX_NAME]) {
    p_dot dot = (p_dot)malloc(sizeof(struct Dot));
    dot->x = x;
    dot->y = y;
    strcpy(dot->name, name);
    return dot;
}

void insertNewDot(int x, int y, char name[MAX_NAME], p_region tree) {
    if (tree->isDivided) {
        /* If the tree has sub-regions, we get into the region where
        the dot should be in. All this through recursion. */
        if (x < tree->x + tree->width / 2) {
            if (y < tree->y + tree->height / 2) {
                insertNewDot(x, y, name, tree->SW);
            } else {
                insertNewDot(x, y, name, tree->NW);
            }
        } else {
            if (y < tree->y + tree->height / 2) {
                insertNewDot(x, y, name, tree->SE);
            } else {
                insertNewDot(x, y, name, tree->NE);
            }
        }
    } else if (tree->dot == NULL) {
        /* When we find a region that doesn't have a dot, we straight up
        add the point into it. */
        tree->dot = createDot(x, y, name);
    } else {
        /* Otherwise, if there's already a dot in this region, we divide this region
        and call the function again twice. Once to add the dot already in this region
        to the new sub-region perfect for it and another time to insert the new dot 
        in also one of the new sub-regions. */
        tree->isDivided = IS_DIVIDED;
        int newHeight1 = (tree->height % 2 == 0) ? tree->height / 2 : (tree->height / 2) + 1;
        int newWidth1 = (tree->width % 2 == 0) ? tree->width / 2 : (tree->width / 2) + 1;
        int newHeight2 = (tree->width % 2 == 0) ? tree->height / 2 : (tree->height / 2);
        int newWidth2 = (tree->width % 2 == 0) ? tree->width / 2 : (tree->width / 2);
        
        tree->NW = createNode(NULL, NULL, NULL, NULL, tree->x, tree->y + newHeight1, newWidth1, newHeight2, !IS_DIVIDED, NW, NULL);
        tree->NE = createNode(NULL, NULL, NULL, NULL, tree->x + newWidth1, tree->y + newHeight1, newWidth2, newHeight2, !IS_DIVIDED, NE, NULL);
        tree->SW = createNode(NULL, NULL, NULL, NULL, tree->x, tree->y, newWidth1, newHeight1, !IS_DIVIDED, SW, NULL);
        tree->SE = createNode(NULL, NULL, NULL, NULL, tree->x + newWidth1, tree->y, newWidth2, newHeight1, !IS_DIVIDED, SE, NULL);
        
        insertNewDot(tree->dot->x, tree->dot->y, tree->dot->name, tree);
        free(tree->dot);
        tree->dot = NULL;
        insertNewDot(x, y, name, tree);
    }
}

void searchDot(p_region tree, int x, int y) {
    if (!tree) {
        printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
        return;
    }

    if (tree->dot && tree->dot->x == x && tree->dot->y == y) {
        printf("Cidade %s encontrada no ponto (%d,%d).\n", tree->dot->name, x, y);
        return;
    }

    if (tree->isDivided) {
        if (x < tree->x + tree->width / 2) {
            if (y < tree->y + tree->height / 2) {
                searchDot(tree->SW, x, y);
            } else {
                searchDot(tree->NW, x, y);
            }
        } else {
            if (y < tree->y + tree->height / 2) {
                searchDot(tree->SE, x, y);
            } else {
                searchDot(tree->NE, x, y);
            }
        }
    } else {
        printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x, y);
    }
}

void removeDot(p_region tree, int x, int y) {
    if (!tree) return;

    if (tree->dot && tree->dot->x == x && tree->dot->y == y) {
        printf("Cidade %s removida no ponto (%d,%d).\n", tree->dot->name, x, y);
        free(tree->dot);
        tree->dot = NULL;
        return;
    }

    if (tree->isDivided == IS_DIVIDED) {
        if (x < tree->x + tree->width / 2) {
            if (y < tree->y + tree->height / 2) {
                removeDot(tree->SW, x, y);
            } else {
                removeDot(tree->NW, x, y);
            }
        } else {
            if (y < tree->y + tree->height / 2) {
                removeDot(tree->SE, x, y);
            } else {
                removeDot(tree->NE, x, y);
            }
        }

        if (!tree->NW && !tree->NE && !tree->SW && !tree->SE) {
            tree->isDivided = !IS_DIVIDED;
        }
    }
}


int main() {
    int dimension;
    scanf(" %d", &dimension);

    p_region tree = createNode(NULL, NULL, NULL, NULL, 0, 0, dimension, dimension, !IS_DIVIDED, NE, NULL);

    char command[COMMAND_LENGTH];
    
    do {
        scanf(" %s", command);
        if (strcmp(command, "i") == 0) {
            int x, y;
            char *name = malloc(sizeof(char) * MAX_NAME);
            scanf(" %d %d %s", &x, &y, name);
            insertNewDot(x, y, name, tree);
            printf("Cidade %s inserida no ponto (%d,%d).\n", name, x, y);
            free(name);
        } else if (strcmp(command, "b") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            searchDot(tree, x, y);
        } else if (strcmp(command, "o") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            searchDot(tree, x, y);
        } else if (strcmp(command, "r") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            removeDot(tree, x, y);
        }
    } while (strcmp(command, "s") != 0);
    printf("Sistema encerrado.");

    freeTree(tree);
    return 0;
}