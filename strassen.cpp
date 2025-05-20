#include <iostream>
#include <vector>
#include <chrono>  // Usamos chrono para medir el tiempo
#include <iomanip> // Necesario para usar setprecision

using namespace std;
using namespace chrono;  // Para la medición del tiempo con chrono

// Función para dividir una matriz en sub-matrices más pequeñas
void splitMatrix(const vector<vector<int>>& A, vector<vector<int>>& B, int rowStart, int colStart) {
    int newSize = A.size() / 2;  // Tamaño de las sub-matrices
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            B[i][j] = A[i + rowStart][j + colStart];  // Copiar los elementos de la matriz A a la sub-matriz B
        }
    }
}

// Función para sumar dos matrices
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int size = A.size();
    vector<vector<int>> C(size, vector<int>(size));  // Matriz para guardar el resultado
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] + B[i][j];  // Sumar las matrices A y B
        }
    }
    return C;
}

// Función para restar dos matrices
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int size = A.size();
    vector<vector<int>> C(size, vector<int>(size));  // Matriz para guardar el resultado
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] - B[i][j];  // Restar las matrices A y B
        }
    }
    return C;
}

// Algoritmo de Strassen para multiplicar dos matrices
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();  // Tamaño de la matriz (suponemos que A y B son matrices cuadradas)
    
    // Caso base: Si la matriz es de tamaño 1x1, solo multiplicamos sus elementos
    if (n == 1) {
        vector<vector<int>> result(1, vector<int>(1));
        result[0][0] = A[0][0] * B[0][0];  // Multiplicación de los elementos
        return result;
    }

    int newSize = n / 2;  // Nuevo tamaño para las sub-matrices
    vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize)),
                        A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize)),
                        B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize)),
                        B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize));

    // Dividir las matrices A y B en 4 sub-matrices
    splitMatrix(A, A11, 0, 0);
    splitMatrix(A, A12, 0, newSize);
    splitMatrix(A, A21, newSize, 0);
    splitMatrix(A, A22, newSize, newSize);
    splitMatrix(B, B11, 0, 0);
    splitMatrix(B, B12, 0, newSize);
    splitMatrix(B, B21, newSize, 0);
    splitMatrix(B, B22, newSize, newSize);

    // Calcular los 7 productos de Strassen
    vector<vector<int>> M1 = strassenMultiply(add(A11, A22), add(B11, B22));
    vector<vector<int>> M2 = strassenMultiply(add(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiply(A11, subtract(B12, B22));
    vector<vector<int>> M4 = strassenMultiply(A22, subtract(B21, B11));
    vector<vector<int>> M5 = strassenMultiply(add(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
    vector<vector<int>> M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

    // Calcular los 4 sub-cuadrantes de la matriz resultante
    vector<vector<int>> C11 = add(subtract(add(M1, M4), M5), M7);
    vector<vector<int>> C12 = add(M3, M5);
    vector<vector<int>> C21 = add(M2, M4);
    vector<vector<int>> C22 = add(subtract(add(M1, M3), M2), M6);

    // Unir las sub-matrices para formar la matriz final C
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

int main() {
    int choice;

    // Menú interactivo para elegir el tamaño de la matriz
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
    vector<vector<int>> result = strassenMultiply(A, B);
    auto end = high_resolution_clock::now();  // Fin de la medición

    // Calcular el tiempo tomado en segundos con decimales
    auto duration = duration_cast<microseconds>(end - start);  // Medir en microsegundos
    double time_taken = duration.count() / 1000000.0;  // Convertir a segundos

    // Mostrar la salida de la forma correcta
    cout << "\nTiempo tomado por strassenMultiply: " << fixed << setprecision(6) << time_taken << " segundos" << endl;

    // Calcular la memoria utilizada por las matrices
    size_t memory_used_A = m * p * sizeof(int);
    size_t memory_used_B = p * n * sizeof(int);
    size_t memory_used_C = m * n * sizeof(int);
    size_t total_memory_used = memory_used_A + memory_used_B + memory_used_C;

    // Mostrar la memoria utilizada
    cout << "Memoria utilizada: " << fixed << setprecision(6) << total_memory_used / (1024.0 * 1024.0) << " MB" << endl;

    return 0;
}