#include <iostream>

using namespace std;

class CuadroMagico {
private:
    int** tablero;
    bool* usados; // Array para controlar qué números ya pusimos (1 a N^2)
    int N;
    int constanteMagica;

    // --- MÉTODOS PRIVADOS ---

    // Calcula si colocar 'num' en (fila, col) rompe las reglas matemáticas
    // Esta es la parte de "Poda" para que el algoritmo sea rápido.
    bool esPrometedor(int fila, int col, int num) {
        
        // 1. CHEQUEO DE FILA
        int sumaFila = 0;
        for(int j = 0; j < col; j++) {
            sumaFila += *(*(tablero + fila) + j);
        }
        sumaFila += num; // Sumamos el candidato

        // Si la suma actual ya se pasó de la constante, no sirve
        if (sumaFila > constanteMagica) return false;
        
        // Si estamos al final de la fila, la suma debe ser EXACTA
        if (col == N - 1 && sumaFila != constanteMagica) return false;

        // 2. CHEQUEO DE COLUMNA
        int sumaCol = 0;
        for(int i = 0; i < fila; i++) {
            sumaCol += *(*(tablero + i) + col);
        }
        sumaCol += num;

        if (sumaCol > constanteMagica) return false;
        if (fila == N - 1 && sumaCol != constanteMagica) return false;

        // 3. CHEQUEO DIAGONAL PRINCIPAL (Top-Left -> Bottom-Right)
        if (fila == col) {
            int sumaDiag = 0;
            for(int i = 0; i < fila; i++) {
                sumaDiag += *(*(tablero + i) + i);
            }
            sumaDiag += num;
            if (sumaDiag > constanteMagica) return false;
            if (fila == N - 1 && col == N - 1 && sumaDiag != constanteMagica) return false;
        }

        // 4. CHEQUEO DIAGONAL SECUNDARIA (Top-Right -> Bottom-Left)
        if (fila + col == N - 1) {
            int sumaDiagSec = 0;
            for(int i = 0; i < fila; i++) {
                // Lógica de puntero para diagonal secundaria: (i, N-1-i)
                sumaDiagSec += *(*(tablero + i) + (N - 1 - i));
            }
            sumaDiagSec += num;
            if (sumaDiagSec > constanteMagica) return false;
            if (fila == N - 1 && col == 0 && sumaDiagSec != constanteMagica) return false;
        }

        return true;
    }

    // Backtracking recursivo
    bool resolverRecursivo(int fila, int col) {
        // Caso Base: Si llenamos todas las filas
        if (fila == N) return true;

        // Siguientes coordenadas
        int sigFila = fila;
        int sigCol = col + 1;
        if (sigCol == N) {
            sigFila = fila + 1;
            sigCol = 0;
        }

        // Probamos números del 1 al N^2
        int maxNum = N * N;
        for (int num = 1; num <= maxNum; num++) {
            
            // Usamos aritmética de punteros para verificar si el numero ya se usó
            // *(usados + num) accede al booleano en el índice 'num'
            if (!*(usados + num)) { 
                
                if (esPrometedor(fila, col, num)) {
                    
                    // 1. Marcar
                    *(*(tablero + fila) + col) = num;
                    *(usados + num) = true;

                    // 2. Recursión
                    if (resolverRecursivo(sigFila, sigCol)) {
                        return true;
                    }

                    // 3. Backtracking (Desmarcar)
                    *(*(tablero + fila) + col) = 0;
                    *(usados + num) = false;
                }
            }
        }
        return false;
    }

public:
    // --- CONSTRUCTOR ---
    CuadroMagico(int n) {
        N = n;
        // Fórmula de la Constante Mágica: M = n(n^2 + 1) / 2
        constanteMagica = (N * (N * N + 1)) / 2;

        // Reserva Matriz (Tablero)
        tablero = new int*[N];
        for (int i = 0; i < N; ++i) {
            *(tablero + i) = new int[N];
            for(int j = 0; j < N; j++) *(*(tablero + i) + j) = 0;
        }

        // Reserva Array de Usados (Tamaño N*N + 1 para usar índices 1-based cómodamente)
        usados = new bool[N * N + 1];
        for(int k = 0; k <= N*N; k++) *(usados + k) = false;
    }

    // --- DESTRUCTOR ---
    ~CuadroMagico() {
        // Liberar tablero
        for (int i = 0; i < N; ++i) delete[] *(tablero + i);
        delete[] tablero;
        
        // Liberar array de usados
        delete[] usados;
        
        cout << "[Memoria liberada]" << endl;
    }

    void resolver() {
        cout << "Buscando solucion para N=" << N << " (Constante Magica: " << constanteMagica << ")..." << endl;
        
        // Optimización: El 5 siempre va al centro en un 3x3, pero dejemos que la IA lo descubra sola.
        if (resolverRecursivo(0, 0)) {
            cout << "\n--- CUADRO MAGICO ENCONTRADO ---" << endl;
            imprimir();
        } else {
            cout << "No se encontro solucion." << endl;
        }
    }

    void imprimir() {
        for (int i = 0; i < N; i++) {
            if (i == 0) cout << "---------------------" << endl;
            for (int j = 0; j < N; j++) {
                cout << "|\t" << *(*(tablero + i) + j) << "\t";
            }
            cout << "|" << endl;
            cout << "---------------------" << endl;
        }
    }
};

int main() {
    // ADVERTENCIA: Backtracking puro es lento para N > 3.
    // N=3 es instantáneo. N=4 puede tardar minutos u horas sin heurísticas avanzadas.
    
    int n;
    n = 3;

    CuadroMagico* magic = new CuadroMagico(n);
    magic->resolver();
    delete magic; // Invoca al destructor

    return 0;
}