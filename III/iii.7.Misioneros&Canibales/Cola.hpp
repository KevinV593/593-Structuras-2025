#ifndef COLA_HPP
#define COLA_HPP

#include "Nodo.hpp"

class Cola {
private:
    Nodo* frente;
    Nodo* final;

public:
    Cola();  
    ~Cola();
    
    bool estaVacia();
    void encolar(Nodo* n);
    Nodo* desencolar();
};

#endif