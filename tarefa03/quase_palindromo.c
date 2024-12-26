#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 400

int is_palindrome_by_tolerance_recursive(char *string, int left, int right, int tolerance) {
    if (right == 0) {
        return 1;
    }
    if (string[left] != string[right]) {
        if (tolerance == 0) {
            return 0;
        }
        return is_palindrome_by_tolerance_recursive(string, left + 1, right - 1, tolerance - 1);
    }
    return is_palindrome_by_tolerance_recursive(string, left + 1, right - 1, tolerance);
}

int main() {
    char string[MAX];
    int tolerance;
    scanf("%d %s", &tolerance, string);
    int length = strlen(string);
    if (is_palindrome_by_tolerance_recursive(string, 0, length - 1, tolerance)) {
        printf("sim\n");
    } else {
        printf("nao\n");
    }
    return 0;
}