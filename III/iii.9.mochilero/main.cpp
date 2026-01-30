#include <iostream>
#include "Mochila.hpp"

using namespace std;

int main() {
    // Configuración del Problema
    int capacidadMochila = 5; // Ejemplo: Mochila aguanta 5kg
    int cantidadObjetos = 3;

    // Crear instancia en el Heap (opcional, podría ser stack, pero usamos punteros por consistencia)
    Mochila* miMochila = new Mochila(capacidadMochila, cantidadObjetos);

    cout << "Cargando datos del problema..." << endl;
    // Definimos los objetos del ejemplo que te di antes:
    // Indice, Peso, Valor
    miMochila->agregarObjeto(0, 2, 30); // Objeto A
    miMochila->agregarObjeto(1, 3, 40); // Objeto B
    miMochila->agregarObjeto(2, 4, 60); // Objeto C

    cout << "Calculando la mejor combinacion..." << endl;
    miMochila->resolver();

    miMochila->mostrarResultado();

    // Liberar memoria
    delete miMochila;

    // Pausa para visualizar
    cin.get();

    return 0;
}