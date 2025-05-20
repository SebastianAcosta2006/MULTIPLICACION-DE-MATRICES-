package arqui;

public class Strassen {

    public static void main(String[] args) {
        int[] sizes = {128, 256, 512, 1024};

        for (int n : sizes) {
            int[][] A = generarMatrizAleatoria(n, n);
            int[][] B = generarMatrizAleatoria(n, n);

            // Medición de memoria antes
            Runtime runtime = Runtime.getRuntime();
            runtime.gc(); // sugerencia de recolección de basura
            long memoriaAntes = runtime.totalMemory() - runtime.freeMemory();

            // Medición de tiempo
            long inicio = System.nanoTime();
            int[][] resultado = strassenMultiply(A, B);
            long fin = System.nanoTime();

            // Medición de memoria después
            long memoriaDespues = runtime.totalMemory() - runtime.freeMemory();

            long memoriaUsada = (memoriaDespues - memoriaAntes) / (1024 * 1024); // en MB
            long tiempoMs = (fin - inicio) / 1_000_000; // en milisegundos

            System.out.printf("Tamaño: %d, Memoria: %.2f MB, Tiempo: %d ms%n",
                    n, (double) memoriaUsada, tiempoMs);
        }
    }

    public static int[][] strassenMultiply(int[][] A, int[][] B) {
        int n = A.length;
        if (n == 1) {
            int[][] result = new int[1][1];
            result[0][0] = A[0][0] * B[0][0];
            return result;
        }

        int newSize = n / 2;
        int[][] A11 = new int[newSize][newSize];
        int[][] A12 = new int[newSize][newSize];
        int[][] A21 = new int[newSize][newSize];
        int[][] A22 = new int[newSize][newSize];
        int[][] B11 = new int[newSize][newSize];
        int[][] B12 = new int[newSize][newSize];
        int[][] B21 = new int[newSize][newSize];
        int[][] B22 = new int[newSize][newSize];

        splitMatrix(A, A11, 0, 0);
        splitMatrix(A, A12, 0, newSize);
        splitMatrix(A, A21, newSize, 0);
        splitMatrix(A, A22, newSize, newSize);
        splitMatrix(B, B11, 0, 0);
        splitMatrix(B, B12, 0, newSize);
        splitMatrix(B, B21, newSize, 0);
        splitMatrix(B, B22, newSize, newSize);

        int[][] M1 = strassenMultiply(add(A11, A22), add(B11, B22));
        int[][] M2 = strassenMultiply(add(A21, A22), B11);
        int[][] M3 = strassenMultiply(A11, subtract(B12, B22));
        int[][] M4 = strassenMultiply(A22, subtract(B21, B11));
        int[][] M5 = strassenMultiply(add(A11, A12), B22);
        int[][] M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
        int[][] M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

        int[][] C11 = add(subtract(add(M1, M4), M5), M7);
        int[][] C12 = add(M3, M5);
        int[][] C21 = add(M2, M4);
        int[][] C22 = add(subtract(add(M1, M3), M2), M6);

        int[][] C = new int[n][n];
        joinMatrix(C11, C, 0, 0);
        joinMatrix(C12, C, 0, newSize);
        joinMatrix(C21, C, newSize, 0);
        joinMatrix(C22, C, newSize, newSize);

        return C;
    }

    public static void splitMatrix(int[][] parent, int[][] child, int rowOffset, int colOffset) {
        for (int i = 0; i < child.length; i++) {
            for (int j = 0; j < child[0].length; j++) {
                child[i][j] = parent[i + rowOffset][j + colOffset];
            }
        }
    }

    public static void joinMatrix(int[][] child, int[][] parent, int rowOffset, int colOffset) {
        for (int i = 0; i < child.length; i++) {
            for (int j = 0; j < child[0].length; j++) {
                parent[i + rowOffset][j + colOffset] = child[i][j];
            }
        }
    }

    public static int[][] add(int[][] A, int[][] B) {
        int n = A.length;
        int[][] result = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = A[i][j] + B[i][j];
        return result;
    }

    public static int[][] subtract(int[][] A, int[][] B) {
        int n = A.length;
        int[][] result = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = A[i][j] - B[i][j];
        return result;
    }

    public static int[][] generarMatrizAleatoria(int filas, int columnas) {
        int[][] matriz = new int[filas][columnas];
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                matriz[i][j] = (int) (Math.random() * 10);
            }
        }
        return matriz;
    }
}
