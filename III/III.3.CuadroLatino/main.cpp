#include <iostream>

using namespace std;

class CuadroLatino {
private:
    int** matriz;
    int N;

    // --- MÉTODOS PRIVADOS ---

    // Verifica si es válido poner un número en (fila, col)
    // Para Cuadro Latino solo revisamos Fila y Columna (No hay cuadros 3x3)
    bool esSeguro(int fila, int col, int num) {
        for (int x = 0; x < N; x++) {
            // Revisamos la fila: *(*(matriz + fila) + x)
            // Revisamos la columna: *(*(matriz + x) + col)
            
            // Si el numero ya existe en la fila O en la columna, retorna falso
            if (*(*(matriz + fila) + x) == num || *(*(matriz + x) + col) == num) {
                return false;
            }
        }
        return true;
    }

    // Backtracking Recursivo
    bool resolverRecursivo(int fila, int col) {
        // Caso Base: Si llegamos a la fila N y col 0 (después de la última celda)
        if (fila == N) return true;

        // Cálculo de siguientes coordenadas
        int siguienteFila = fila;
        int siguienteCol = col + 1;
        
        if (siguienteCol == N) {
            siguienteFila = fila + 1;
            siguienteCol = 0;
        }

        // Si la celda actual ya tiene valor, pasamos a la siguiente
        if (*(*(matriz + fila) + col) != 0) {
            return resolverRecursivo(siguienteFila, siguienteCol);
        }

        // Intentamos números del 1 al N
        for (int num = 1; num <= N; num++) {
            if (esSeguro(fila, col, num)) {
                
                // Asignar (usando punteros)
                *(*(matriz + fila) + col) = num;

                // Recursión
                if (resolverRecursivo(siguienteFila, siguienteCol)) {
                    return true;
                }

                // Backtracking: Si no funcionó, borramos
                *(*(matriz + fila) + col) = 0;
            }
        }
        return false;
    }

public:
    // --- CONSTRUCTOR ---
    CuadroLatino(int size) {
        N = size;
        matriz = new int*[N]; // Array de punteros
        
        for (int i = 0; i < N; ++i) {
            *(matriz + i) = new int[N]; // Filas
            
            // Inicializamos todo en 0
            for(int j = 0; j < N; j++) {
                *(*(matriz + i) + j) = 0;
            }
        }
    }

    // --- DESTRUCTOR ---
    ~CuadroLatino() {
        for (int i = 0; i < N; ++i) {
            delete[] *(matriz + i);
        }
        delete[] matriz;
        cout << "[Memoria del Cuadro Latino liberada]" << endl;
    }

    // Método para iniciar la resolución
    void generarSolucion() {
        // Empezamos desde 0,0. Si retorna true, se llenó la matriz.
        if (resolverRecursivo(0, 0)) {
            cout << "\n--- CUADRO LATINO DE ORDEN " << N << " ---" << endl;
            imprimir();
        } else {
            cout << "No se encontró solución." << endl;
        }
    }

    void imprimir() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Imprimir con punteros y formato bonito
                cout << *(*(matriz + i) + j) << "\t"; 
            }
            cout << endl;
        }
    }
    
    // Opcional: Para pre-llenar valores si quisieras (como en el sudoku)
    void setValor(int f, int c, int valor) {
        if (f >= 0 && f < N && c >= 0 && c < N) {
             *(*(matriz + f) + c) = valor;
        }
    }
};

int main() {
    int orden;
    cout << "Ingrese el orden del Cuadro Latino (ej. 4, 5, 9): ";
    cin >> orden;

    // 1. Crear Objeto
    CuadroLatino latino(orden);

    // Opcional: Podrías poner una restricción inicial para forzar resultados distintos
    // latino.setValor(0, 0, 1); 

    // 2. Generar
    latino.generarSolucion();

    // 3. El destructor se llama automáticamente al salir
    return 0;
}