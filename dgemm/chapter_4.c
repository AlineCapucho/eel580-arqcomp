#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>
#include "utils.h"

#define UNROLL (4)

void dgemm(int n, double* A, double* B, double* C) {
  printf("Entrou no dgemm.\n");
  for (int i = 0; i < n; i+=UNROLL*4)
    for (int j = 0; j < n; j++) {
      __m256d c[4];
      for (int x; x < UNROLL; x++)
        c[x] = _mm256_load_pd(C+i+x*4+j*n);
      for (int k = 0; k < n; k++) {
        __m256d b = _mm256_broadcast_sd(B+k+j*n);
        for (int x; x < UNROLL; x++)
          c[x] = _mm256_add_pd(c[x],
          _mm256_mul_pd(_mm256_load_pd(A+n*k+x*4+i), b));
      }
      for (int x; x < UNROLL; x++)
        _mm256_store_pd(C+i+x*4+j*n, c[x]);
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

    if (A == NULL || B == NULL || C == NULL) {
      printf("Erro na alocação de memória. Encerrando programa.\n");
      return -1;
    }

    generate_matrix(A, n);
    generate_matrix(B, n);

    clock_t start = clock();
    dgemm(n, A, B, C);
    clock_t end = clock();

    double elapsed = (double)(end - start)/CLOCKS_PER_SEC;;

    write_runtime_data(n, elapsed, "Runtimes_v3.txt");

    free(A);
    free(B);
    free(C);
  }

    return 0;
}
