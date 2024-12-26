#include <stdio.h>
#define MAX_SIZE 1000

void readNums(int nums[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &nums[i]);
    }
}

void genPartials(int nums[], int partials[], int size) {
    int sum = nums[0];
    int i;

    partials[0] = sum;
    for (i = 1; i < size; i++) {
        sum += nums[i];
        partials[i] = sum;
    }
}

void reverseParials(int partials[], int size) {
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = partials[i];
        partials[i] = partials[size - i - 1];
        partials[size - i - 1] = temp;
    }
}

void displayList(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int size;
    scanf("%d", &size);

    int nums[MAX_SIZE];
    int partials[MAX_SIZE];

    readNums(nums, size);
    genPartials(nums, partials, size);
    reverseParials(partials, size);
    displayList(partials, size);

    return 0;
}
