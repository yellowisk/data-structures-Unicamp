#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void print_centroid(int dimension, double *centroid, char type) {
    if (type == 's') {
        printf("nenhum: ");
    } else if (type == 'n') {
        printf("normal: ");
    } else {
        printf("janela: ");
    }

    for (int i = 0; i < dimension; i++) {
        printf("%.3f ", centroid[i]);
    }
    printf("\n");
}

void average_centroid(double *centroid_simple_average, double **matrix, int n_points, int dimension) {
    for (int i = 0; i < dimension; i++) {
        centroid_simple_average[i] = 0;
        for (int j = 0; j < n_points; j++) {
            centroid_simple_average[i] += matrix[j][i] / n_points;
        }
    }
}

void fin_min_max_of_column(double *min, double *max, double **matrix, int n_points, int column) {
    *min = matrix[0][column];
    *max = matrix[0][column];
    for (int i = 0; i < n_points; i++) {
        if (matrix[i][column] < *min) {
            *min = matrix[i][column];
        }
        if (matrix[i][column] > *max) {
            *max = matrix[i][column];
        }
    }
}

void normalize_centroid(double *centroid_normalized, double **matrix, int n_points, int dimension) {
    double *average = malloc(dimension * sizeof(double));
    average_centroid(average, matrix, n_points, dimension);
    for (int i = 0; i < dimension; i++) {
        double min, max;
        centroid_normalized[i] = 0;
        fin_min_max_of_column(&min, &max, matrix, n_points, i);
        if (max == min) {
            centroid_normalized[i] = 0;
            continue;
        }
        centroid_normalized[i] = (2 * (average[i] - min)) / ((max - min)) -1;
    }
    free(average);
}

void euclidian_normalization(double *euclidian_centroid, double **matrix, int n_points, int dimension) {
    double *norms = malloc(n_points * sizeof(double));
    for (int i = 0; i < n_points; i++) {
        norms[i] = 0;
        for (int j = 0; j < dimension; j++) {
            norms[i] += pow(matrix[i][j], 2);
        }
        norms[i] = sqrt(norms[i]);
    }
    for (int i = 0; i < dimension; i++) {
        euclidian_centroid[i] = 0;
        for (int j = 0; j < n_points; j++) {
            euclidian_centroid[i] += (matrix[j][i] / norms[j]) / n_points;
        }
    }
    free(norms);
}

void free_matrix(double **matrix, int n_points) {
    for (int i = 0; i < n_points; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int dimension, n_points;
    scanf("%d %d", &dimension, &n_points);
    double **matrix = malloc(n_points * sizeof(double *));
    for (int i = 0; i < n_points; i++) {
        matrix[i] = malloc(dimension * sizeof(double));
    }

    for (int i = 0; i < n_points; i++) {
        for (int j = 0; j < dimension; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    double *centroid_simple_average = malloc(dimension * sizeof(double));
    average_centroid(centroid_simple_average, matrix, n_points, dimension);
    print_centroid(dimension, centroid_simple_average, 's');

    double *normal_centroid = malloc(dimension * sizeof(double));
    normalize_centroid(normal_centroid, matrix, n_points, dimension);
    print_centroid(dimension, normal_centroid, 'j');

    double *euclidian_centroid = malloc(dimension * sizeof(double));
    euclidian_normalization(euclidian_centroid, matrix, n_points, dimension);
    print_centroid(dimension, euclidian_centroid, 'n');

    free(centroid_simple_average);
    free(normal_centroid);
    free(euclidian_centroid);
    free_matrix(matrix, n_points);

    return 0;
}