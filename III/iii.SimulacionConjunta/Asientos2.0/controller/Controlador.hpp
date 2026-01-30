#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include "../model/ListaCircular.hpp"
#include "../model/Asiento.hpp"
#include "../view/Vista.hpp"

class Controlador {
private:
    ListaCircular<Asiento> listaAsientos;
    Vista vista;

    void inicializarLista(int cantidad);
    void inicializarListaAlternada(int cantidad);

public:
    Controlador();
    void iniciar();
    void encerarAsientos();
    void mostrarEstadoActual();
    void crearPatronAlternado();
    void reservarAsiento();
};

#endif