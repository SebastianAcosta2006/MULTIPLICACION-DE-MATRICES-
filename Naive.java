package arqui;

public class Naive {

    public static void main(String[] args) {
        int[] sizes = {128, 256, 512, 1024};
        int blockSize = 32;

        for (int n : sizes) {
            int[][] A = generarMatrizAleatoria(n, n);
            int[][] B = generarMatrizAleatoria(n, n);

        
            Runtime runtime = Runtime.getRuntime();
            runtime.gc(); 
            long memoriaAntes = runtime.totalMemory() - runtime.freeMemory();

           
            long inicio = System.nanoTime();
            int[][] resultado = blockedMultiply(A, B, blockSize);
            long fin = System.nanoTime();

            
            long memoriaDespues = runtime.totalMemory() - runtime.freeMemory();

            long memoriaUsada = (memoriaDespues - memoriaAntes) / (1024 * 1024); 
            long tiempoMs = (fin - inicio) / 1_000_000; 

            System.out.printf("Tamaño: %d, Memoria: %.2f MB, Tiempo: %d ms%n",
                    n, (double) memoriaUsada, tiempoMs);
        }
    }

    public static int[][] blockedMultiply(int[][] A, int[][] B, int blockSize) {
        int m = A.length;
        int p = A[0].length;
        int n = B[0].length;

        if (B.length != p) {
            throw new IllegalArgumentException("Incompatibilidad: A es m×p y B debe ser p×n");
        }

        int[][] C = new int[m][n];

        for (int ii = 0; ii < m; ii += blockSize) {
            for (int jj = 0; jj < n; jj += blockSize) {
                for (int kk = 0; kk < p; kk += blockSize) {
                    int iMax = Math.min(ii + blockSize, m);
                    int jMax = Math.min(jj + blockSize, n);
                    int kMax = Math.min(kk + blockSize, p);

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

        return C;
    }

    public static int[][] generarMatrizAleatoria(int filas, int columnas) {
        int[][] matriz = new int[filas][columnas];
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                matriz[i][j] = (int) (Math.random() * 10); // valores del 0 al 9
            }
        }
        return matriz;
    }
}