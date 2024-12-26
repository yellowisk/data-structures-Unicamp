#include <stdio.h>

#define MAX_SIZE 100

void readRow(int row[], int colsNum) {
    for (int i = 0; i < colsNum; i++) {
        scanf("%d", &row[i]);
    }
}

void genMatrix(int matrix[][MAX_SIZE], int columns, int rows) {
    int row[MAX_SIZE];
    int i, j;
    for (i = 0; i < rows; i++) {
        readRow(row, columns);
        for (j = 0; j < columns; j++) {
            matrix[i][j] = row[j];
        }
    }
}

void display_matrix(int matrix[][MAX_SIZE], int rows, int columns) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int checkForSaddlePoint(int matrix[][MAX_SIZE], int rows, int columns) {
    int i, j, k;
    for (i = 0; i < rows; i++) {
        int least = matrix[i][0];
        int leastIndex = 0;
        int leastCount = 1;

        for (j = 1; j < columns; j++) {
            if (matrix[i][j] < least) {
                least = matrix[i][j];
                leastIndex = j;
                leastCount = 1;
            } else if (matrix[i][j] == least) {
                leastCount++;
            }
        }

        if (leastCount > 1) {
            continue;
        }

        int isSaddlePoint = 1;
        int maxCount = 1;
        for (k = 0; k < rows; k++) {
            if (matrix[k][leastIndex] > least) {
                isSaddlePoint = 0;
                break;
            } else if (matrix[k][leastIndex] == least && k != i) {
                maxCount++;
            }
        }

        if (maxCount > 1) {
            continue;
        }

        if (isSaddlePoint) {
            printf("(%d, %d) eh ponto de sela com valor %d\n", i, leastIndex, least);
            return 1;
        }
    }

    return 0;
}

int main() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int colsNum, rowsNum;
    
    scanf("%d", &rowsNum);
    scanf("%d", &colsNum);

    genMatrix(matrix, colsNum, rowsNum);

    if (!checkForSaddlePoint(matrix, rowsNum, colsNum))
        printf("nao existe ponto de sela");

    return 0;
}
