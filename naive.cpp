#include <iostream>
#include <vector>
#include <chrono>  // Usamos chrono para medir el tiempo
#include <iomanip> // Necesario para usar setprecision

using namespace std;
using namespace chrono;  // Para la medición del tiempo con chrono

// Función que implementa la multiplicación de matrices con bloqueos (blocking)
void blockedMultiply(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int blockSize) {
    int m = A.size();  // Filas de A
    int p = A[0].size();  // Columnas de A (y filas de B)
    int n = B[0].size();  // Columnas de B

    for (int ii = 0; ii < m; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < p; kk += blockSize) {
                int iMax = min(ii + blockSize, m);
                int jMax = min(jj + blockSize, n);
                int kMax = min(kk + blockSize, p);

                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        int sum = C[i][j];
                        for (int k = kk; k < kMax; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}

int main() {
    int blockSize = 2;  // Tamaño del bloque para la multiplicación por bloques
    int choice;

    cout << "Seleccione el tamaño de la matriz:" << endl;
    cout << "1. 128x128" << endl;
    cout << "2. 256x256" << endl;
    cout << "3. 512x512" << endl;
    cout << "4. 1024x1024" << endl;
    cout << "Ingrese su opción (1-4): ";
    cin >> choice;

    // Determinar el tamaño de las matrices según la opción seleccionada
    int m, p, n;
    switch (choice) {
        case 1:
            m = p = n = 128;
            break;
        case 2:
            m = p = n = 256;
            break;
        case 3:
            m = p = n = 512;
            break;
        case 4:
            m = p = n = 1024;
            break;
        default:
            cout << "Opción no válida." << endl;
            return 0;
    }

    // Inicializar las matrices A y B con valores arbitrarios
    vector<vector<int>> A(m, vector<int>(p, 1)); // Llenamos A con 1s
    vector<vector<int>> B(p, vector<int>(n, 1)); // Llenamos B con 1s
    vector<vector<int>> C(m, vector<int>(n, 0)); // Inicializamos C con 0s

    // Medir el tiempo de ejecución del algoritmo usando chrono
    auto start = high_resolution_clock::now();  // Inicio de la medición
    blockedMultiply(A, B, C, blockSize);
    auto end = high_resolution_clock::now();  // Fin de la medición

    // Calcular el tiempo tomado en segundos con decimales
    auto duration = duration_cast<microseconds>(end - start);  // Medir en microsegundos
    double time_taken = duration.count() / 1000000.0;  // Convertir a segundos
    cout << "Tiempo tomado por blockedMultiply: " << fixed << setprecision(6) << time_taken << " segundos" << endl;

    // Imprimir la matriz resultante C (opcional)
    // cout << "Matriz resultado C:" << endl;
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << C[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // Calcular la memoria utilizada por las matrices
    size_t memory_used = m * p * sizeof(int) + p * n * sizeof(int) + m * n * sizeof(int);
    cout << "Memoria utilizada: " << memory_used / (1024.0 * 1024.0) << " MB" << endl;

    return 0;
}