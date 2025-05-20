import time
import numpy as np

def blocked_multiply(A, B, block_size):
    m, p = A.shape
    p, n = B.shape
    C = np.zeros((m, n), dtype=int)

    for ii in range(0, m, block_size):
        for jj in range(0, n, block_size):
            for kk in range(0, p, block_size):
                i_max = min(ii + block_size, m)
                j_max = min(jj + block_size, n)
                k_max = min(kk + block_size, p)

                for i in range(ii, i_max):
                    for j in range(jj, j_max):
                        sum_ = C[i, j]
                        for k in range(kk, k_max):
                            sum_ += A[i, k] * B[k, j]
                        C[i, j] = sum_
    return C

def main():
    block_size = 2  # Tamaño del bloque para la multiplicación por bloques

    print("Seleccione el tamaño de la matriz:")
    print("1. 128x128")
    print("2. 256x256")
    print("3. 512x512")
    print("4. 1024x1024")
    choice = int(input("Ingrese su opción (1-4): "))

    # Determinar el tamaño de las matrices según la opción seleccionada
    if choice == 1:
        m = p = n = 128
    elif choice == 2:
        m = p = n = 256
    elif choice == 3:
        m = p = n = 512
    elif choice == 4:
        m = p = n = 1024
    else:
        print("Opción no válida.")
        return

    # Inicializar las matrices A y B con valores arbitrarios
    A = np.ones((m, p), dtype=int)  # Llenamos A con 1s
    B = np.ones((p, n), dtype=int)  # Llenamos B con 1s

    # Medir el tiempo de ejecución del algoritmo
    start = time.time()  # Inicio de la medición
    C = blocked_multiply(A, B, block_size)
    end = time.time()  # Fin de la medición

    # Calcular el tiempo tomado en segundos con decimales
    time_taken = end - start
    print(f"Tiempo tomado por blocked_multiply: {time_taken:.6f} segundos")

    # Calcular la memoria utilizada por las matrices
    memory_used = (m * p * A.itemsize + p * n * B.itemsize + m * n * C.itemsize) / (1024 * 1024)
    print(f"Memoria utilizada: {memory_used:.2f} MB")

    # Imprimir la matriz resultante C (opcional)
    # print("Matriz resultado C:")
    # print(C)

if __name__ == "__main__":
    main()