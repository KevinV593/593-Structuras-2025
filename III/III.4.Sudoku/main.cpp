#include <iostream>

using namespace std;

class SudokuSolver {
private:
    int** tablero;
    int N;

    // --- MÉTODOS PRIVADOS ---

    bool esSeguro(int fila, int col, int num) {
        // 1. Verificar fila y columna usando punteros
        for (int x = 0; x < N; x++) {
            // Fila: *(*(tablero + fila) + x)  <-- Equivale a tablero[fila][x]
            // Col:  *(*(tablero + x) + col)   <-- Equivale a tablero[x][col]
            
            if (*(*(tablero + fila) + x) == num || *(*(tablero + x) + col) == num) {
                return false;
            }
        }

        // 2. Verificar subcuadro 3x3
        int inicioFila = fila - fila % 3;
        int inicioCol = col - col % 3;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Cálculo de la dirección exacta en el subcuadro
                int filaExacta = i + inicioFila;
                int colExacta = j + inicioCol;
                
                if (*(*(tablero + filaExacta) + colExacta) == num) {
                    return false;
                }
            }
        }
        return true;
    }

    bool resolverRecursivo(int fila, int col) {
        if (fila == N - 1 && col == N) return true;

        if (col == N) {
            fila++;
            col = 0;
        }

        // Verificamos si la celda actual (*(*(tablero + fila) + col)) ya tiene valor
        if (*(*(tablero + fila) + col) != 0) {
            return resolverRecursivo(fila, col + 1);
        }

        for (int num = 1; num <= 9; num++) {
            if (esSeguro(fila, col, num)) {
                
                // Asignación usando punteros
                *(*(tablero + fila) + col) = num;

                if (resolverRecursivo(fila, col + 1)) return true;

                // Backtracking (resetear a 0) usando punteros
                *(*(tablero + fila) + col) = 0;
            }
        }
        return false;
    }

public:
    // --- CONSTRUCTOR ---
    SudokuSolver(int size) {
        N = size;
        tablero = new int*[N]; // Reserva array de punteros
        
        for (int i = 0; i < N; ++i) {
            // A cada posición del array de punteros *(tablero + i), le asignamos una nueva fila
            *(tablero + i) = new int[N];

            // Inicializamos con 0
            for(int j = 0; j < N; j++) {
                *(*(tablero + i) + j) = 0;
            }
        }
    }

    // --- DESTRUCTOR ---
    ~SudokuSolver() {
        for (int i = 0; i < N; ++i) {
            // Liberamos la fila i-ésima
            delete[] *(tablero + i);
        }
        // Liberamos el array de punteros principal
        delete[] tablero;
        cout << "[Memoria liberada correctamente usando punteros]" << endl;
    }

    void cargarTablero(int datos[9][9]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Copiamos del array estático al dinámico usando punteros
                *(*(tablero + i) + j) = *(*(datos + i) + j); 
                // Nota: datos[i][j] también se puede escribir como *(*(datos + i) + j)
            }
        }
    }

    void resolver() {
        if (resolverRecursivo(0, 0)) {
            cout << "\n--- SUDOKU RESUELTO ---" << endl;
            imprimir();
        } else {
            cout << "No existe solucion." << endl;
        }
    }

    void imprimir() {
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0 && i != 0) cout << "---------------------" << endl;
            for (int j = 0; j < N; j++) {
                if (j % 3 == 0 && j != 0) cout << "| ";
                
                // Acceso para impresión
                cout << *(*(tablero + i) + j) << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    SudokuSolver juego(9);

    int datos[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    juego.cargarTablero(datos);

    cout << "--- Tablero Inicial ---" << endl;
    juego.imprimir();

    juego.resolver();

    return 0;
}