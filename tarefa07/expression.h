typedef struct node {
    char op;
    struct node *left;
    struct node *right;
} *p_node;

void freeTree(p_node root);

void printTree(p_node root);

p_node createNode(p_node left, char op, p_node right);

char readChar(char** expression);

p_node readTree(char** expression);

p_node removeDoubleExclamation(p_node root);

p_node moveNegationFromConstOrVars(p_node root);

p_node DeMorgan(p_node root);

int isEqual(p_node subtree1, p_node subtree2);

p_node simplify(p_node root);