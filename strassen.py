import time
import sys


def split_matrix(A, row_start, col_start, size):
    return [[A[i + row_start][j + col_start] for j in range(size)] for i in range(size)]


def add(A, B):
    size = len(A)
    return [[A[i][j] + B[i][j] for j in range(size)] for i in range(size)]


def subtract(A, B):
    size = len(A)
    return [[A[i][j] - B[i][j] for j in range(size)] for i in range(size)]


def strassen_multiply(A, B):
    n = len(A)  


    if n == 1:
        return [[A[0][0] * B[0][0]]]

    new_size = n // 2  


    A11 = split_matrix(A, 0, 0, new_size)
    A12 = split_matrix(A, 0, new_size, new_size)
    A21 = split_matrix(A, new_size, 0, new_size)
    A22 = split_matrix(A, new_size, new_size, new_size)

    B11 = split_matrix(B, 0, 0, new_size)
    B12 = split_matrix(B, 0, new_size, new_size)
    B21 = split_matrix(B, new_size, 0, new_size)
    B22 = split_matrix(B, new_size, new_size, new_size)


    M1 = strassen_multiply(add(A11, A22), add(B11, B22))
    M2 = strassen_multiply(add(A21, A22), B11)
    M3 = strassen_multiply(A11, subtract(B12, B22))
    M4 = strassen_multiply(A22, subtract(B21, B11))
    M5 = strassen_multiply(add(A11, A12), B22)
    M6 = strassen_multiply(subtract(A21, A11), add(B11, B12))
    M7 = strassen_multiply(subtract(A12, A22), add(B21, B22))


    C11 = add(subtract(add(M1, M4), M5), M7)
    C12 = add(M3, M5)
    C21 = add(M2, M4)
    C22 = add(subtract(add(M1, M3), M2), M6)


    C = [[0] * n for _ in range(n)]
    for i in range(new_size):
        for j in range(new_size):
            C[i][j] = C11[i][j]
            C[i][j + new_size] = C12[i][j]
            C[i + new_size][j] = C21[i][j]
            C[i + new_size][j + new_size] = C22[i][j]

    return C

def main():
    print("Seleccione el tamaño de la matriz:")
    print("1. 128x128")
    print("2. 256x256")
    print("3. 512x512")
    print("4. 1024x1024")
    choice = int(input("Ingrese su opción (1-4): "))


    if choice == 1:
        n = 128
    elif choice == 2:
        n = 256
    elif choice == 3:
        n = 512
    elif choice == 4:
        n = 1024
    else:
        print("Opción no válida.")
        return


    A = [[1 for _ in range(n)] for _ in range(n)]  
    B = [[1 for _ in range(n)] for _ in range(n)]  


    start = time.time()  
    C = strassen_multiply(A, B)
    end = time.time()  


    time_taken = end - start
    print(f"\nTiempo tomado por strassenMultiply: {time_taken:.6f} segundos")


    memory_used_A = n * n * sys.getsizeof(1) 
    memory_used_B = n * n * sys.getsizeof(1)  
    memory_used_C = n * n * sys.getsizeof(1) 
    total_memory_used = memory_used_A + memory_used_B + memory_used_C


    print(f"Memoria utilizada: {total_memory_used / (1024 * 1024):.6f} MB")

if __name__ == "__main__":
    main()