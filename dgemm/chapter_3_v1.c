#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

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

void generate_matrix(double* matrix, size_t n) {
    srand(time(NULL)); // generate the randomic seed with current time
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            matrix[i * n + j] = (double)rand() / RAND_MAX; //generate random double numbers between 0 and 1
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

        dgemm(n, A, B, C);

        free(A);
        free(B);
        free(C);
    }

    return 0;
}
