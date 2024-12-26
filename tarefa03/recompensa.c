#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double probability(int distance, int tries_left) {
    if (tries_left == 0 || distance <= 0) {
        return 0.0;
    }

    double prob = 0.0;

    for (int i = 1; i <= 6; i++) {
        if (distance == i) {
            prob += 1.0 / 6;
        } else {
            prob += probability(distance - i, tries_left - 1) / 6;
        }
    }

    return prob;
}

int main() {
    int distance, tries;
    scanf("%d %d", &distance, &tries);
    printf("%.3f\n", probability(tries, distance));
    return 0;
}