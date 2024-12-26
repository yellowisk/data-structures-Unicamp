#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct s_name {
    char f_name[MAX_LENGTH];
    char l_name[MAX_LENGTH];
} name;

name * create_list(int numElements) {
    name *list = malloc(numElements * sizeof(name));
    if (list == NULL) {
        printf("Nao ha memoria\n");
        exit(1);
    }
    return list;
}

int find_underscore(const char *fullName, int length) {
    for (int i = 0; i < length; i++) {
        if (fullName[i] == '_') {
            return i;
        }
    }
    return -1;
}

int find_space(const char *fullName, int length) {
    for (int i = 0; i < length; i++) {
        if (fullName[i] == ' ') {
            return i;
        }
    }
    return -1;
}

void split_text_parts(const char *text, int breakerIndex, char *part1, char *part2) {
    int i;

    for (i = 0; i < breakerIndex; i++) {
        part1[i] = text[i];
    }
    part1[i] = '\0'; // Null-terminate

    int j = 0;
    for (i = breakerIndex + 1; text[i] != '\0'; i++, j++) {
        part2[j] = text[i];
    }
    part2[j] = '\0'; // Null-terminate
}

name split_name(const char *fullName, int length) {
    char part1[MAX_LENGTH];
    char part2[MAX_LENGTH];

    int underscoreIndex = find_underscore(fullName, length);

    split_text_parts(fullName, underscoreIndex, part1, part2);
    
    name nameStruct;

    int i;
    for (i = 0; i < MAX_LENGTH - 1 && part1[i] != '\0'; i++) {
        nameStruct.f_name[i] = part1[i];
    }
    nameStruct.f_name[i] = '\0';

    for (i = 0; i < MAX_LENGTH - 1 && part2[i] != '\0'; i++) {
        nameStruct.l_name[i] = part2[i];
    }
    nameStruct.l_name[i] = '\0';
    
    return nameStruct;
}

void find_homonymes(name *names, const char *desiredName, int length) {
    int j = 0;
    name *homonymes = create_list(length);

    for (int i = 0; i < length; i++) {
        if (strcmp(names[i].f_name, desiredName) == 0) {
            homonymes[j] = names[i];
            j++;
        }
    }

    for (int i = 0; i < j; i++) {
        printf("%s_%s\n", homonymes[i].f_name, homonymes[i].l_name);
    }

    free(homonymes);
}

void find_relatives(name *names, const char *desiredName, int length) {
    int j = 0;
    name *relatives = create_list(length);

    for (int i = 0; i < length; i++) {
        if (strcmp(names[i].l_name, desiredName) == 0) {
            relatives[j] = names[i];
            j++;
        }
    }

    for (int i = 0; i < j; i++) {
        printf("%s_%s\n", relatives[i].f_name, relatives[i].l_name);
    }

    free(relatives);
}

int main() {
    int length;
    scanf("%d", &length);
    
    name *people = create_list(length);

    for (int i = 0; i < length; i++) {
        char fullName[MAX_LENGTH];
        scanf("%s", fullName);
        name splitName = split_name(fullName, strlen(fullName));
        people[i] = splitName;
    }

    char command[MAX_LENGTH];
    char type[MAX_LENGTH];
    char desiredName[MAX_LENGTH];

    scanf(" %[^\n]", command);
    int spaceIndex = find_space(command, MAX_LENGTH);
    
    split_text_parts(command, spaceIndex, type, desiredName);

    if (strcmp(type, "homonimos") == 0) {
        find_homonymes(people, desiredName, length);
    } else {
        find_relatives(people, desiredName, length);
    }
    
    free(people);

    return 0;
}