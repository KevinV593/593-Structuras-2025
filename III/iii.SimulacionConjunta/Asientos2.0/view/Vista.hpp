#ifndef VISTA_HPP
#define VISTA_HPP

class Vista {
public:
    void mostrarMensaje(const char* mensaje);
    int pedirEntero(const char* mensaje);
    void mostrarEstadoAsiento(int id, int estado);
};

#endif