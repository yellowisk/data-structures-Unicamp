#include <stdio.h>

int isCapicua(long long int number) {
    long long int originalNumber = number;
    long long int reversedNumber = 0;
    long long int remainder;

    while (number != 0) {
        remainder = number % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        number /= 10;
    }

    if (reversedNumber == originalNumber)
        return 1;
    else
        return 0;

}

int main() {

    int times, i;
    scanf("%d", &times);

    for (i = 0; i < times; i++) {
        long long int number;
        scanf("%lld", &number);

        if (isCapicua(number))
            printf("%lld eh capicua\n", number);
        else
            printf("%lld nao eh capicua\n", number);
    }

    return 0;
}