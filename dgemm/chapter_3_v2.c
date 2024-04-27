#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>
#include "utils.h"

//dgemm code extracted from textbook chapter 3 (going faster)
void dgemm(size_t n, double* A, double* B, double* C) {
  for (size_t i = 0; i < n; i+=4)
    for (size_t j = 0; j < n; j++) {
      __m256d c0 = _mm256_load_pd(C+i+j*n); // c0 = C[i][j]
      for (size_t k = 0; k < n; k++)
        c0 = _mm256_add_pd(c0, // *c0 += A[i][k] * B[k][j]
        _mm256_mul_pd(_mm256_load_pd(A+i+k*n),
        _mm256_broadcast_sd(B+k+j*n)));
      _mm256_store_pd(C+i+j*n, c0); // C[i][j] = c0
    }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Número incorreto de parâmetros passados. Encerrando programa.\n");
    return -1;
  }
  else {
    size_t n = atoi(argv[1]);

    double *A, *B, *C;

    // Initialize matrixes
    A = (double *)malloc(sizeof(double)*n*n);
    B = (double *)malloc(sizeof(double)*n*n);
    C = (double *)malloc(sizeof(double)*n*n);
    
    generate_matrix(A, n);
    generate_matrix(B, n);

    clock_t start = clock();
    dgemm(n, A, B, C);
    clock_t end = clock();

    double elapsed = (double)(end - start)/CLOCKS_PER_SEC;;

    write_runtime_data(n, elapsed, "Runtimes_v2.txt");

    free(A);
    free(B);
    free(C);
  }

  return 0;
}
