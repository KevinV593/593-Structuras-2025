#include <iostream>
#include "Laberinto.hpp"

int main() {
    Laberinto* juego = new Laberinto(5, 5);
    
    std::cout << "Cargando laberinto..." << std::endl;
    juego->configurarTablero();
    
    std::cout << "Resolviendo usando Pila (Backtracking)..." << std::endl;
    bool resuelto = juego->resolver();
    
    if (resuelto) {
        std::cout << "SOLUCION ENCONTRADA!" << std::endl;
        juego->imprimir();
    } else {
        std::cout << "El laberinto no tiene solucion." << std::endl;
    }
    
    delete juego;
    
    std::cin.get();
    
    return 0;
}