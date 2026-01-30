#include "controller/Controlador.hpp"

int main() {
    // Instanciación única del controlador
    Controlador sistema;
    
    // Ejecución del ciclo de vida
    sistema.iniciar();

    return 0;
}