#include <iostream>
#include "Solucionador.hpp"

int main() {

    Solucionador juego;
    
    juego.resolver();

    std::cout << "\nPresione Enter para salir...";
    std::cin.get();
    
    return 0;
}