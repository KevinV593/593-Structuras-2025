#include <math.h>
#include <stdlib.h>
#include <time.h>

// Definimos la macro para exportar funciones en Windows
#define EXPORT __declspec(dllexport)

extern "C" {

    // Función que simula una tarea logarítmica O(log n)
    // Usamos notación de punteros (*n_inputs, *results)
    EXPORT void calculate_execution_times(double* input_sizes, double* execution_times, int total_tests) {
        
        // Iteramos a través de cada tamaño de prueba solicitado
        for (int i = 0; i < total_tests; i++) {
            
            // 1. Uso de punteros para leer el tamaño de entrada actual (N)
            // *(input_sizes + i) es aritmética de punteros equivalente a input_sizes[i]
            int n = (int)*(input_sizes + i);
            
            // 2. Uso de Memoria Dinámica: Creamos un arreglo de tamaño N
            // Esto es solo para demostrar la asignación dinámica como pediste
            int* dynamic_array = new int[n];

            // Rellenamos el arreglo (operación lineal, pero necesaria para configurar)
            // Para no afectar la medición logarítmica, asumimos que el arreglo ya existe,
            // pero aquí lo llenamos rápido.
            for(int j = 0; j < n; j++) {
                *(dynamic_array + j) = j;
            }

            // --- INICIO MEDICIÓN ALGORITMO LOGARÍTMICO ---
            // Simularemos una Búsqueda Binaria (que es O(log n))
            
            // Variable para contar "pasos" o tiempo simulado
            double steps = 0;
            int target = -1; // Buscamos un número que no existe para el peor caso
            int left = 0;
            int right = n - 1;

            while (left <= right) {
                steps++; // Contamos este paso
                int mid = left + (right - left) / 2;
                
                if (*(dynamic_array + mid) == target) {
                    break;
                }
                if (*(dynamic_array + mid) < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            // --- FIN MEDICIÓN ---

            // Guardamos el resultado (pasos o tiempo) en el arreglo de salida usando punteros
            *(execution_times + i) = steps;

            // 3. Liberar la memoria dinámica (¡Muy importante!)
            delete[] dynamic_array;
        }
    }
}