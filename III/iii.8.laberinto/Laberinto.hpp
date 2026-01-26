#ifndef LABERINTO_HPP
#define LABERINTO_HPP

#include "Pila.hpp"

class Laberinto {
private:
    int** tablero;      // Matriz dinámica 2D
    bool** visitados;   // Matriz auxiliar para no repetir casillas
    int filas;
    int cols;
    
    Coordenada inicio;
    Coordenada fin;
    
    Pila* camino;       // Nuestra pila de backtracking

public:
    Laberinto(int f, int c);
    ~Laberinto();
    
    void configurarTablero(); // Carga un mapa predefinido
    bool resolver();          // El algoritmo DFS
    void imprimir();          // Dibuja el laberinto en consola
};

#endif