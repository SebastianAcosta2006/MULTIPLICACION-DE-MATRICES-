#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void blockedMultiply(int *restrict A, int *restrict B, int *restrict C, int m, int p, int n, int blockSize) {
    for (int ii = 0; ii < m; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < p; kk += blockSize) {
                int iMax = (ii + blockSize < m) ? ii + blockSize : m;
                int jMax = (jj + blockSize < n) ? jj + blockSize : n;
                int kMax = (kk + blockSize < p) ? kk + blockSize : p;

                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        int sum = C[i * n + j];
                        for (int k = kk; k < kMax; k++) {
                            sum += A[i * p + k] * B[k * n + j];
                        }
                        C[i * n + j] = sum;
                    }
                }
            }
        }
    }
}

int main() {
    int blockSize = 2;
    int choice, m, p, n;

    printf("Seleccione el tamaño de la matriz:\n");
    printf("1. 128x128\n2. 256x256\n3. 512x512\n4. 1024x1024\nIngrese su opción (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: m = p = n = 128; break;
        case 2: m = p = n = 256; break;
        case 3: m = p = n = 512; break;
        case 4: m = p = n = 1024; break;
        default:
            printf("Opción no válida.\n");
            return 1;
    }

    int *A = malloc(m * p * sizeof(int));
    int *B = malloc(p * n * sizeof(int));
    int *C = calloc(m * n, sizeof(int));

    if (!A || !B || !C) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < m * p; i++) A[i] = 1;
    for (int i = 0; i < p * n; i++) B[i] = 1;

    clock_t start = clock();
    blockedMultiply(A, B, C, m, p, n, blockSize);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo tomado por blockedMultiply: %.6f segundos\n", time_taken);

    size_t memory_used = (m * p + p * n + m * n) * sizeof(int);
    printf("Memoria utilizada: %.2f MB\n", memory_used / (1024.0 * 1024.0));

    free(A);
    free(B);
    free(C);

    return 0;
}