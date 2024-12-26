#define MAX_LENGTH 25
#define MAX 1783
#define IS_IN_LIST 1
#define SINGLE_CHAR_LENGTH 2

typedef struct node {
    char key[MAX_LENGTH];
    struct node *next;
} *p_node;

typedef struct hash {
    p_node list[MAX];
} *p_hash;

int hash(char *key);

p_hash createHash();

p_node insertInList(p_node node, char *key);

void insertInHash(p_hash hashTable, char *key);

void destroyList(p_node node);

void destroyHash(p_hash hashTable);

int isInList(p_node head, char *word);

int testCombinations(char *word, p_hash hashTable, int listPosition);

void getResponse(p_hash hashTable, int numWordsInDict, char *word, char *response);