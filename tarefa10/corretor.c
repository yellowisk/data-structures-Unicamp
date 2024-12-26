#include <stdio.h>
#include <stdlib.h>
#include "grammar.h"

int main() {
    int numWordsInDict, wordsToSearch;
    scanf(" %d %d", &numWordsInDict, &wordsToSearch);

    p_hash hashTable = createHash();

    for (int i = 0; i < numWordsInDict; i++) {
        char word[MAX_LENGTH];
        scanf("%s", word);
        insertInHash(hashTable, word);
    }
    
    for (int i = 0; i < wordsToSearch; i++) {
        char word[MAX_LENGTH];
        char response[MAX_LENGTH];
        scanf("\n%s", word);

        getResponse(hashTable, numWordsInDict, word, response);
        printf("%s: %s\n", word, response);
    }

    destroyHash(hashTable);

    return 0;
}