#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_matrix(double* matrix, size_t n) {
    srand(time(NULL)); // generate the randomic seed with current time
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            matrix[i * n + j] = (double)rand() / RAND_MAX; //generate random double numbers between 0 and 1
        }
    }
}

void write_runtime_data(int N, double runtime, char *filename) {
    FILE* ptr;
    ptr = fopen(filename, "a");

    if (ptr == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(ptr, "%d", N);
    fprintf(ptr, "%s", " ");
    fprintf(ptr, "%f", runtime);
    fprintf(ptr, "%s", "\n");

    fclose(ptr);
}