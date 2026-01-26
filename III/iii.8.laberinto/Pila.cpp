#include <iostream>
#include "Pila.hpp"

using namespace std;

Pila::Pila() {
    tope = nullptr;
}

Pila::~Pila() {
    while(!estaVacia()) {
        pop();
    }
}

void Pila::push(int f, int c) {
    NodoPila* nuevo = new NodoPila;
    nuevo->dato = {f, c};
    nuevo->siguiente = tope;
    tope = nuevo;
}

void Pila::pop() {
    if (!estaVacia()) {
        NodoPila* temp = tope;
        tope = tope->siguiente;
        delete temp;
    }
}

Coordenada Pila::peek() {
    if (!estaVacia()) return tope->dato;
    return {-1, -1}; // Valor de error
}

bool Pila::estaVacia() {
    return tope == nullptr;
}

bool Pila::contiene(int f, int c) {
    NodoPila* actual = tope;
    while (actual != nullptr) {
        if (actual->dato.fila == f && actual->dato.col == c) return true;
        actual = actual->siguiente;
    }
    return false;
}

// Función auxiliar recursiva para imprimir en orden (Base -> Tope)
void Pila::imprimirCaminoInverso(NodoPila* n) {
    if (n == nullptr) return;
    imprimirCaminoInverso(n->siguiente);
    cout << "(" << n->dato.fila << "," << n->dato.col << ") -> ";
}

void Pila::mostrarCamino() {
    if (estaVacia()) {
        cout << "No hay camino." << endl;
    } else {
        cout << "Camino encontrado: ";
        imprimirCaminoInverso(tope);
        cout << "META" << endl;
    }
}