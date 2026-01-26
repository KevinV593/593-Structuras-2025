#ifndef COORDENADA_HPP
#define COORDENADA_HPP

struct Coordenada {
    int fila;
    int col;
    
    // Sobrecarga para comparar si dos coordenadas son iguales
    bool operator==(const Coordenada& otra) const {
        return fila == otra.fila && col == otra.col;
    }
};

#endif