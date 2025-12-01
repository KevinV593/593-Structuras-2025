#include <iostream>
#include <algorithm> // Para std::sort y std::max

using namespace std;

// Estructura para representar un intervalo [inicio, fin]
struct Intervalo {
    long long inicio;
    long long fin;
};

// Función de comparación para ordenar intervalos (necesaria para la lógica Greedy)
bool compararIntervalos(Intervalo a, Intervalo b) {
    return a.inicio < b.inicio;
}

/**
 * Función de verificación 'check'.
 * Determina si es posible colocar 'n' vacas con una separación mínima de 'dist'.
 * Usa aritmética de punteros para recorrer el arreglo de intervalos.
 */
bool esPosible(long long dist, int n, int m, Intervalo*& intervalos) {
    int vacasColocadas = 1;
    
    // Accedemos al inicio del primer intervalo usando punteros
    long long posActual = (intervalos + 0)->inicio;
    
    // Índice para recorrer los intervalos
    int idxIntervalo = 0;

    while (vacasColocadas < n) {
        long long siguienteObjetivo = posActual + dist;

        // Búsqueda lineal del siguiente intervalo válido usando punteros.
        // Mientras el intervalo actual termine ANTES de nuestro objetivo, avanzamos el puntero (índice).
        while (idxIntervalo < m && (intervalos + idxIntervalo)->fin < siguienteObjetivo) {
            idxIntervalo++;
        }

        // Si el índice supera o iguala a m, se acabaron los intervalos y no cupieron las vacas.
        if (idxIntervalo >= m) {
            return false;
        }

        // Determinamos la posición real donde cae la vaca.
        // Opción A: El objetivo cae DENTRO del intervalo actual -> Usamos siguienteObjetivo.
        // Opción B: El objetivo cae ANTES del intervalo (saltamos un hueco) -> Usamos (intervalos + idx)->inicio.
        posActual = max(siguienteObjetivo, (intervalos + idxIntervalo)->inicio);
        
        vacasColocadas++;
    }
    
    // Si salimos del bucle, logramos colocar todas las vacas
    return true;
}

/**
 * Función personalizada que busca la RESPUESTA ÓPTIMA.
 * Aplica la lógica de "lower_bound" pero sobre el rango de respuestas posibles (1 a 10^18).
 */
void buscarDistanciaMaxima(int n, int m, Intervalo*& intervalos) {
    // Definimos la "ventana" de búsqueda para la distancia D.
    // El mínimo teórico es 1.
    // El máximo teórico es el final del último intervalo (aunque seguro es menos, esto cubre todo).
    long long minimoPosible = 1;
    long long maximoPosible = (intervalos + m - 1)->fin;
    
    long long respuesta = 0;

    while (minimoPosible <= maximoPosible) {
        // Calculamos la distancia candidata (punto medio)
        long long distanciaCandidata = minimoPosible + (maximoPosible - minimoPosible) / 2;

        // Verificamos si esta distancia es viable
        if (esPosible(distanciaCandidata, n, m, intervalos)) {
            // SÍ es posible:
            // 1. Guardamos esta distancia como la mejor encontrada hasta ahora.
            respuesta = distanciaCandidata;
            // 2. Intentamos ser más ambiciosos: buscamos en la mitad superior.
            //    Movemos el "piso" hacia arriba.
            minimoPosible = distanciaCandidata + 1;
        } else {
            // NO es posible:
            // La distancia era muy grande, las vacas no caben.
            // Buscamos en la mitad inferior. Movemos el "techo" hacia abajo.
            maximoPosible = distanciaCandidata - 1;
        }
    }

    cout << respuesta << endl;
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    // Lectura de N y M [cite: 36]
    if (cin >> n >> m) {
        // Asignación de memoria dinámica (Sin vectores)
        Intervalo* intervalos = new Intervalo[m];

        // Lectura de los intervalos usando notación de punteros
        for (int i = 0; i < m; ++i) {
            cin >> (intervalos + i)->inicio >> (intervalos + i)->fin;
        }

        // Ordenamos los intervalos por su inicio. 
        // Es fundamental para que la estrategia greedy funcione correctamente.
        sort(intervalos, intervalos + m, compararIntervalos);

        // Llamamos a nuestra función de búsqueda binaria
        buscarDistanciaMaxima(n, m, intervalos);

        // Liberamos la memoria dinámica
        delete[] intervalos;
    }

    return 0;
}