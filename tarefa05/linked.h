typedef struct node {
    int index;
    char value;
    struct node *next;
} *p_node;

p_node searchByIndex(p_node head, int index);

void printList(p_node head);

char removeNodeByIndex(p_node *head, int index);

p_node createNode(char value, int index);

void insertNodeAt(p_node *head, char value, int index);

void destroyList(p_node head);

void invertPrefix(p_node *head, int prefixLength);

void invertSuffix(p_node *head, int suffixLength);

void transpose(p_node *head, int p, int q, int r);