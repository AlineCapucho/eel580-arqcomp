import numpy as np
import time
import sys

def dgemm(n, A, B):
    C = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]
    
    return C

def main(n):
    A = np.zeros((n, n))
    B = np.zeros((n, n))

    start_time = time.time()  # Registrar o tempo inicial
    C = dgemm(n, A, B)
    end_time = time.time()  # Registrar o tempo final

    execution_time = end_time - start_time
    with open("Runtimes_c1.txt", "a") as file:
        file.write("{} {:.6f}\n".format(n, execution_time))  # Escrevendo o valor de n e o tempo de execução na mesma linha

    return C

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Número incorreto de parâmetros passados. Encerrando programa.\n")
        sys.exit(1)
    
    n = int(sys.argv[1])
    main(n)
