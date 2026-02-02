#include <iostream>
#include <iomanip> 
#include "Mochila.hpp"

using namespace std;

Mochila::Mochila(int capacidad, int n) {
    capacidadMax = capacidad;
    numObjetos = n;
    // 1. Crear arreglo de objetos
    listaObjetos = new Objeto[numObjetos];
    
    // 2. Crear la Matriz Dinámica (Filas = Objetos + 1, Cols = Capacidad + 1)
    tabla = new int*[numObjetos + 1];
    for (int i = 0; i <= numObjetos; i++) {
        tabla[i] = new int[capacidadMax + 1];
    }

    // Inicializar matriz en 0
    for (int i = 0; i <= numObjetos; i++) {
        for (int w = 0; w <= capacidadMax; w++) {
            tabla[i][w] = 0;
        }
    }
}

Mochila::~Mochila() {
    // Limpieza estricta de memoria
    delete[] listaObjetos;

    // Liberar matriz fila por fila
    for (int i = 0; i <= numObjetos; i++) {
        delete[] tabla[i];
    }
    delete[] tabla;
}

void Mochila::agregarObjeto(int indice, int peso, int valor) {
    // Ajustamos indice porque el usuario cuenta 0..N-1
    listaObjetos[indice].id = indice + 1;
    listaObjetos[indice].peso = peso;
    listaObjetos[indice].valor = valor;
}

// --- CORAZÓN DEL ALGORITMO (Iterativo Bottom-Up) ---
void Mochila::resolver() {
    // i: índice del objeto actual (del 1 al total)
    // w: capacidad actual que estamos analizando (de 0 a CapacidadMax)
    
    for (int i = 1; i <= numObjetos; i++) {
        // Obtenemos datos del objeto actual (ajuste de índice -1 para el array)
        int pesoObj = listaObjetos[i-1].peso;
        int valorObj = listaObjetos[i-1].valor;

        for (int w = 0; w <= capacidadMax; w++) {
            
            // Caso 1: El objeto pesa más que la capacidad actual 'w'.
            // No cabe. Nos quedamos con el valor que teníamos SIN este objeto (fila anterior).
            if (pesoObj > w) {
                tabla[i][w] = tabla[i-1][w];
            } 
            // Caso 2: El objeto SÍ cabe. Decidimos:
            // ¿Es mejor incluirlo o dejarlo?
            else {
                int valorSinIncluir = tabla[i-1][w]; // Valor de la fila de arriba
                
                // Valor incluyendo: Valor de este objeto + el mejor valor posible con el peso restante
                int valorIncluyendo = valorObj + tabla[i-1][w - pesoObj];
                
                // Maximo entre las dos opciones
                if (valorIncluyendo > valorSinIncluir) {
                    tabla[i][w] = valorIncluyendo;
                } else {
                    tabla[i][w] = valorSinIncluir;
                }
            }
        }
    }
}

void Mochila::mostrarResultado() {
    cout << "=== RESULTADOS DE LA MOCHILA ===" << endl;
    cout << "Valor Maximo posible: $" << tabla[numObjetos][capacidadMax] << endl;
    cout << "\n--- Objetos Seleccionados (Reconstruccion) ---" << endl;

    int w = capacidadMax;
    int pesoTotal = 0;

    // Recorremos la tabla hacia atrás (desde el último objeto al primero)
    // para ver qué decisiones tomamos.
    for (int i = numObjetos; i > 0; i--) {
        // Si el valor viene de la fila de arriba (tabla[i] == tabla[i-1]),
        // significa que NO incluimos este objeto.
        // Si es diferente, significa que SÍ lo incluimos.
        
        if (tabla[i][w] != tabla[i-1][w]) {
            Objeto obj = listaObjetos[i-1];
            cout << "-> Objeto #" << obj.id 
                 << " (Peso: " << obj.peso << "kg, Valor: $" << obj.valor << ")" << endl;
            
            pesoTotal += obj.peso;
            w = w - obj.peso; // Restamos el peso para seguir buscando
        }
    }
    
    cout << "--------------------------------" << endl;
    cout << "Peso Total utilizado: " << pesoTotal << " / " << capacidadMax << " kg" << endl;
}