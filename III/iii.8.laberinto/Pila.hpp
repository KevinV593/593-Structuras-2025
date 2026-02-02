#ifndef PILA_HPP
#define PILA_HPP

#include "Coordenada.hpp"

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