#include <iostream>
#include <algorithm> // Solo para std::max y std::min
#include <cmath>     // Para std::abs

using namespace std;

long long* mi_lower_bound(long long* limiteInf, long long* limiteSup, long long valor) {
    // Si no encontramos nada, devolvemos el límite superior (fuera del rango válido)
    long long* respuesta = limiteSup; 
    
    // Calculamos la cantidad total de elementos usando aritmética de punteros
    int totalElementos = limiteSup - limiteInf; 
    
    // Definimos la "ventana" de índices donde buscamos
    int minimoPosible = 0;
    int maximoPosible = totalElementos - 1;

    while (minimoPosible <= maximoPosible) {
        // Calculamos el índice de la mitad
        int indiceMedio = minimoPosible + (maximoPosible - minimoPosible) / 2;
        
        // Convertimos el índice numérico a una dirección de memoria real
        long long* punteroAlMedio = limiteInf + indiceMedio;

        // ¿El valor en el medio es mayor o igual a lo que busco?
        if (*punteroAlMedio >= valor) {
            // SÍ: Es un candidato válido. Guardamos la respuesta.
            respuesta = punteroAlMedio;
            maximoPosible = indiceMedio - 1;
        } else {
          
            minimoPosible = indiceMedio + 1;
        }
    }
    
    return respuesta;
}

/**
 * Función principal de la lógica.
 * Recibe punteros por referencia.
 */
void calcularRadioMinimo(long long*& ciudades, int& n, long long*& torres, int& m) {
    long long radioMaximo = 0;

    for (int i = 0; i < n; ++i) {
        long long ciudadActual = *(ciudades + i);
        
        // Inicializamos con un valor muy grande
        long long distMinimaLocal = 20000000000LL; 

        // LLAMADA A NUESTRA FUNCIÓN PERSONALIZADA
        // limiteInf: inicio del arreglo 'torres'
        // limiteSup: final del arreglo 'torres + m'
        long long* ptrTorreDer = mi_lower_bound(torres, torres + m, ciudadActual);

        // Lógica para calcular distancia con la torre de la derecha (si existe)
        if (ptrTorreDer != (torres + m)) {
            long long distDer = *ptrTorreDer - ciudadActual;
            distMinimaLocal = min(distMinimaLocal, distDer);
        }

        // Lógica para calcular distancia con la torre de la izquierda (si existe)
        // Si lower_bound encontró una torre, la anterior es la inmediata menor a la ciudad.
        // Si lower_bound devolvió 'fin' (no encontró nada >=), la última torre del arreglo es la de la izquierda.
        if (ptrTorreDer != torres) {
            long long* ptrTorreIzq = ptrTorreDer - 1; // Retrocedemos una posición de memoria
            long long distIzq = ciudadActual - *ptrTorreIzq;
            distMinimaLocal = min(distMinimaLocal, distIzq);
        }

        // El radio final debe ser capaz de cubrir la peor situación encontrada (el máximo de los mínimos)
        radioMaximo = max(radioMaximo, distMinimaLocal);
    }

    cout << radioMaximo << endl;
}

int main() {
    // Optimización de entrada/salida para C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    
    // Lectura de tamaños
    if (cin >> n >> m) {
        // Asignación de memoria dinámica
        long long* ciudades = new long long[n];
        long long* torres = new long long[m];

        // Lectura de ciudades
        for (int i = 0; i < n; ++i) {
            cin >> *(ciudades + i);
        }

        // Lectura de torres
        for (int i = 0; i < m; ++i) {
            cin >> *(torres + i);
        }

        // Proceso
        calcularRadioMinimo(ciudades, n, torres, m);

        // Limpieza de memoria
        delete[] ciudades;
        delete[] torres;
    }

    return 0;
}