#ifndef ESTADO_HPP
#define ESTADO_HPP

struct Estado {
    int m; // Misioneros
    int c; // Canibales
    int b; // Bote (1: Izq, 0: Der)
};

bool esEstadoValido(int m, int c);

#endif