#include "Vista.hpp"
#include <iostream>

void Vista::mostrarMensaje(const char* mensaje) {
    std::cout << mensaje << std::endl;
}

int Vista::pedirEntero(const char* mensaje) {
    int valor;
    std::cout << mensaje << ": ";
    std::cin >> valor;
    return valor;
}

void Vista::mostrarEstadoAsiento(int id, int estado) {
    std::cout << "[Asiento " << id << ": " << (estado ? "OCUPADO" : "LIBRE") << "] ";
}