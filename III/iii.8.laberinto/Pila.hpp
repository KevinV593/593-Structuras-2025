#ifndef PILA_H
#define PILA_H

#include "Coordenada.hpp"

// Nodo para la lista enlazada interna de la pila
struct NodoPila {
    Coordenada dato;
    NodoPila* siguiente;
};

class Pila {
private:
    NodoPila* tope;

public:
    Pila();
    ~Pila();
    void push(int f, int c);
    void pop();
    Coordenada peek(); 
    bool estaVacia();
    
    void imprimirCaminoInverso(NodoPila* n);
    void mostrarCamino();
    
    bool contiene(int f, int c);
};

#endif