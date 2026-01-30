#ifndef MOCHILA_H
#define MOCHILA_H

// Debe coincidir exactamente con el nombre de tu otro archivo.
#include "Objeto.hpp" 
// ------------------------------

class Mochila {
private:
    int capacidadMax;
    int numObjetos;
    
    // Aquí es donde te daba el error. Ahora ya sabe qué es "Objeto"
    Objeto* listaObjetos; 
    
    int** tabla; 

public:
    Mochila(int capacidad, int n);
    ~Mochila();
    void agregarObjeto(int indice, int peso, int valor);
    void resolver();
    void mostrarResultado();
};

#endif