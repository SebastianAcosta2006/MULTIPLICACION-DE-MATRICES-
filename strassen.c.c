#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void add(int *restrict A, int *restrict B, int *restrict C, int size) {
    for (int i = 0; i < size * size; i++) {
        C[i] = A[i] + B[i];
    }
}

void subtract(int *restrict A, int *restrict B, int *restrict C, int size) {
    for (int i = 0; i < size * size; i++) {
        C[i] = A[i] - B[i];
    }
}

void strassen(int *A, int *B, int *C, int size) {
    if (size == 1) {
        C[0] = A[0] * B[0];
        return;
    }

    int newSize = size / 2;
    int block = newSize * newSize * sizeof(int);

    int *A11 = malloc(block), *A12 = malloc(block), *A21 = malloc(block), *A22 = malloc(block);
    int *B11 = malloc(block), *B12 = malloc(block), *B21 = malloc(block), *B22 = malloc(block);
    int *M1 = malloc(block), *M2 = malloc(block), *M3 = malloc(block), *M4 = malloc(block);
    int *M5 = malloc(block), *M6 = malloc(block), *M7 = malloc(block);
    int *Atemp = malloc(block), *Btemp = malloc(block);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            int idx = i * size + j;
            A11[i * newSize + j] = A[idx];
            A12[i * newSize + j] = A[idx + newSize];
            A21[i * newSize + j] = A[(i + newSize) * size + j];
            A22[i * newSize + j] = A[(i + newSize) * size + j + newSize];

            B11[i * newSize + j] = B[idx];
            B12[i * newSize + j] = B[idx + newSize];
            B21[i * newSize + j] = B[(i + newSize) * size + j];
            B22[i * newSize + j] = B[(i + newSize) * size + j + newSize];
        }
    }

    add(A11, A22, Atemp, newSize);
    add(B11, B22, Btemp, newSize);
    strassen(Atemp, Btemp, M1, newSize);

    add(A21, A22, Atemp, newSize);
    strassen(Atemp, B11, M2, newSize);

    subtract(B12, B22, Btemp, newSize);
    strassen(A11, Btemp, M3, newSize);

    subtract(B21, B11, Btemp, newSize);
    strassen(A22, Btemp, M4, newSize);

    add(A11, A12, Atemp, newSize);
    strassen(Atemp, B22, M5, newSize);

    subtract(A21, A11, Atemp, newSize);
    add(B11, B12, Btemp, newSize);
    strassen(Atemp, Btemp, M6, newSize);

    subtract(A12, A22, Atemp, newSize);
    add(B21, B22, Btemp, newSize);
    strassen(Atemp, Btemp, M7, newSize);

    int *C11 = malloc(block), *C12 = malloc(block), *C21 = malloc(block), *C22 = malloc(block);

    add(M1, M4, Atemp, newSize);
    subtract(Atemp, M5, Btemp, newSize);
    add(Btemp, M7, C11, newSize);

    add(M3, M5, C12, newSize);
    add(M2, M4, C21, newSize);

    add(M1, M3, Atemp, newSize);
    subtract(Atemp, M2, Btemp, newSize);
    add(Btemp, M6, C22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i * size + j] = C11[i * newSize + j];
            C[i * size + j + newSize] = C12[i * newSize + j];
            C[(i + newSize) * size + j] = C21[i * newSize + j];
            C[(i + newSize) * size + j + newSize] = C22[i * newSize + j];
        }
    }

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(M1); free(M2); free(M3); free(M4); free(M5); free(M6); free(M7);
    free(C11); free(C12); free(C21); free(C22);
    free(Atemp); free(Btemp);
}

int main() {
    int choice;
    int n;

    printf("Seleccione el tamaño de la matriz:\n");
    printf("1. 128x128\n2. 256x256\n3. 512x512\n4. 1024x1024\nIngrese su opción (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: n = 128; break;
        case 2: n = 256; break;
        case 3: n = 512; break;
        case 4: n = 1024; break;
        default:
            printf("Opción no válida.\n");
            return 1;
    }

    int *A = malloc(n * n * sizeof(int));
    int *B = malloc(n * n * sizeof(int));
    int *C = calloc(n * n, sizeof(int));

    if (!A || !B || !C) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < n * n; i++) {
        A[i] = 1;
        B[i] = 1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    strassen(A, B, C, n);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Tiempo tomado por strassenMultiply: %.6f segundos\n", time_taken);

    size_t memory_used = 3 * n * n * sizeof(int);
    printf("Memoria utilizada: %.2f MB\n", memory_used / (1024.0 * 1024.0));

    free(A);
    free(B);
    free(C);

    return 0;
}