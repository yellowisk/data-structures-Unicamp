#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

int hash(char *key) {
    int i, n = 0;
    for (i = 0; i < strlen(key); i++)
        n = (256 * n + key[i]) % MAX;
    return n;
}

p_hash createHash() {
    p_hash hash = (p_hash) malloc(sizeof(struct hash));
    for (int i = 0; i < MAX; i++)
        hash->list[i] = NULL;
    return hash;
}

p_node insertInList(p_node node, char *key) {
    p_node newNode = (p_node) malloc(sizeof(struct node));
    strcpy(newNode->key, key);
    newNode->next = node;
    return newNode;
}

void insertInHash(p_hash hashTable, char *key) {
    int n = hash(key);
    hashTable->list[n] = insertInList(hashTable->list[n], key);
}

void destroyList(p_node node) {
    if (node != NULL) {
        destroyList(node->next);
    }
    free(node);
}

void destroyHash(p_hash hashTable) {
    for (int i = 0; i < MAX; i++) {
        destroyList(hashTable->list[i]);
    }
    free(hashTable);
}

int isInList(p_node head, char *word) {
    if (!head)
        return !IS_IN_LIST;

    return (strcmp(word, head->key) == 0) ? 
    IS_IN_LIST : isInList(head->next, word);
}

int testCombinations(char *word, p_hash hashTable, int listPosition) {
    int positionInList;
    for (int i = 0; i < strlen(word); i++) {
        for (int j = 0; j < 26; j++) {
            /* I set temp's length to be bigger 
            than the max length for words to have 
            room for the '\0' character */
            char toChange[MAX_LENGTH + 1];
            strcpy(toChange, word);
            // changing letter here
            char letter = 'a' + j;
            toChange[i] = letter;
            toChange[strlen(word)] = '\0';
            positionInList = hash(toChange);
            if (isInList(hashTable->list[positionInList], toChange) == IS_IN_LIST)
                return IS_IN_LIST;

            // adding letter to different positions in the word
            char prefix[MAX_LENGTH];
            char suffix[MAX_LENGTH];
            char letterChar[SINGLE_CHAR_LENGTH] = {letter, '\0'};

            strncpy(prefix, word, i);
            prefix[i] = '\0';

            strncpy(suffix, word + i, strlen(word) - i);
            suffix[strlen(word) - i] = '\0';

            strcat(prefix, letterChar);
            strcat(prefix, suffix);
            positionInList = hash(prefix);
            if (isInList(hashTable->list[positionInList], prefix) == IS_IN_LIST)
                return IS_IN_LIST;

            if (i == 0) {
            /* Adding letter at the final of the word */
                strncpy(prefix, word, strlen(word));
                prefix[strlen(word)] = '\0';

                strcat(prefix, letterChar);
                positionInList = hash(prefix);
                if (isInList(hashTable->list[positionInList], prefix) == IS_IN_LIST)
                    return IS_IN_LIST;
            }
            
        }

        // create word without a letter
        char toRemove[MAX_LENGTH];
        for (int k = 0; k < strlen(word); k++) {
            if (i == k) {
                continue;
            } else if (k > i) {
                toRemove[k - 1] = word[k];
            } else {
                toRemove[k] = word[k];
            }
        }

        toRemove[strlen(word) - 1]='\0';
        positionInList = hash(toRemove);
        if (isInList(hashTable->list[positionInList], toRemove) == IS_IN_LIST)
            return IS_IN_LIST;
    }

    return !IS_IN_LIST;
}

void getResponse(p_hash hashTable, int numWordsInDict, char *word, char *response) {
    strcpy(response, "vermelho");
    int n = hash(word);
    if (isInList(hashTable->list[n], word)) {
        strcpy(response, "verde");
    } else if (testCombinations(word, hashTable, n)) {
        strcpy(response, "amarelo");
    }
}