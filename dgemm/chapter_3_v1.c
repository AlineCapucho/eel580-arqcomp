#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// dgemm code extracted from textbook chapter 3 (going faster)
void dgemm (size_t n, double* A, double* B, double* C) {
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      double cij = C[i + j*n]; //cij = C[i][j]
      for (size_t k = 0; k < n; ++k) {
        cij += A[i + k*n] * B[k + j*n]; // *cij += A[i][k] * B[k][j]
      }
      C[i+j*n] = cij; // C[i][j] = cij
    }
  }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Número incorreto de parâmetros passados. Encerrando programa.\n");
        return -1;
    }
    else {
        size_t n = atoi(argv[1]);

        // Initialize matrixes
        double *A = malloc(sizeof(double)*n*n);
        double *B = malloc(sizeof(double)*n*n);
        double *C = malloc(sizeof(double)*n*n);
        
        generate_matrix(A, n);
        generate_matrix(B, n);

        struct timespec start, finish;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &start);

        dgemm(n, A, B, C);

        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        write_runtime_data(n, elapsed, "Runtimes_v1.txt");

        free(A);
        free(B);
        free(C);
    }

    return 0;
}
