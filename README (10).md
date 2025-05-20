
# Multiplicación de Matrices: Algoritmos Naive y Strassen

Este proyecto implementa dos algoritmos para la multiplicación de matrices: el método **Naive (tradicional)** y el método **Strassen**, en los lenguajes **Python**, **C**, **C++** y **Java**.

## Requisitos

### Python
- Python 3.x

### C/C++
- Compilador C: `gcc`
- Compilador C++: `g++`

### Java
- JDK 8 o superior (`javac`, `java`)

---

## Archivos

| Archivo            | Lenguaje | Algoritmo  |
|--------------------|----------|------------|
| `naive.py`         | Python   | Naive      |
| `strassen.py`      | Python   | Strassen   |
| `naive.c.c`        | C        | Naive      |
| `strassen.c.c`     | C        | Strassen   |
| `naive.cpp`        | C++      | Naive      |
| `strassen.cpp`     | C++      | Strassen   |
| `Naive.java`       | Java     | Naive      |
| `Strassen.java`    | Java     | Strassen   |

---

## Ejecución por Lenguaje

### 🐍 Python

```bash
python3 naive.py
python3 strassen.py
```

---

### 🇨 C

```bash
# Naive
gcc naive.c.c -o naive_c
./naive_c

# Strassen
gcc strassen.c.c -o strassen_c
./strassen_c
```

---

### 🇨++ C++

```bash
# Naive
g++ naive.cpp -o naive_cpp
./naive_cpp

# Strassen
g++ strassen.cpp -o strassen_cpp
./strassen_cpp
```

---

### ☕ Java

```bash
# Naive
javac Naive.java
java Naive

# Strassen
javac Strassen.java
java Strassen
```

---

## Funcionalidad

Al ejecutar cualquier archivo:

1. Se solicita al usuario elegir el tamaño de la matriz (128x128 hasta 1024x1024).
2. Las matrices se llenan automáticamente con valores (por defecto: `1`).
3. Se realiza la multiplicación y se mide:
   - Tiempo de ejecución.
   - Memoria utilizada.

---

## Notas

- Asegúrate de tener suficiente memoria disponible si usas matrices grandes como 1024x1024.
- Para evitar confusión, los archivos `.c.c` pueden renombrarse a `.c` si lo deseas.
