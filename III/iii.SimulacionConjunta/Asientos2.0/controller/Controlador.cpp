#include "Controlador.hpp"

Controlador::Controlador() {}

void Controlador::inicializarLista(int cantidad) {
    for (int i = 1; i <= cantidad; ++i) {
        listaAsientos.insertar(Asiento(i));
    }
}

void Controlador::inicializarListaAlternada(int cantidad) {
    // Patrón de alternancia estricta: 1-0-1-0-1-0...
    // Usamos aritmética básica: (i-1) % 2 para obtener 0 y 1 alternadamente
    for (int i = 1; i <= cantidad; ++i) {
        Asiento nuevoAsiento(i);
        int estadoAlternado = (i - 1) % 2; // 0 si i es impar, 1 si i es par
        nuevoAsiento.setEstado(estadoAlternado);
        listaAsientos.insertar(nuevoAsiento);
    }
}

void Controlador::encerarAsientos() {
    vista.mostrarMensaje("Iniciando algoritmo de encerado (Fuerza Bruta)...");

    // EXPRESIÓN LAMBDA: Define la lógica atómica de "encerar"
    // El 'auto& asiento' captura el objeto por referencia para modificarlo
    auto lambdaEncerar = [](Asiento& asiento) {
        asiento.setEstado(0); // 0 = Libre/Encerado
    };

    // Delegamos a la lista la ejecución recursiva
    listaAsientos.ejecutarEnTodos(lambdaEncerar);
    
    vista.mostrarMensaje("Todos los asientos han sido encerados exitosamente.");
}

void Controlador::mostrarEstadoActual() {
    vista.mostrarMensaje("\n--- Estado Actual de la Sala ---");
    
    // EXPRESIÓN LAMBDA: Captura 'this' para usar métodos de la vista dentro del callback
    auto lambdaMostrar = [this](Asiento& asiento) {
        this->vista.mostrarEstadoAsiento(asiento.getId(), asiento.getEstado());
    };

    listaAsientos.ejecutarEnTodos(lambdaMostrar);
    vista.mostrarMensaje("\n--------------------------------");
}

void Controlador::crearPatronAlternado() {
    vista.mostrarMensaje("\n--- Crear Patron de Alternancia Estricta (1-0-1-0) ---");
    int cantidad = vista.pedirEntero("Ingresar cantidad de asientos");
    
    if (cantidad <= 0) {
        vista.mostrarMensaje("Error: Ingrese una cantidad valida (mayor a 0)");
        return;
    }
    
    // Limpiar la lista anterior si existe
    listaAsientos = ListaCircular<Asiento>();
    
    // Crear nuevos asientos con patrón alternado
    inicializarListaAlternada(cantidad);
    
    vista.mostrarMensaje("Patron alternado creado exitosamente.");
    vista.mostrarMensaje("\n--- Estado Inicial de la Sala ---");
    mostrarEstadoActual();
}

void Controlador::reservarAsiento() {
    vista.mostrarMensaje("\n--- Reservar Asiento ---");
    int idAsiento = vista.pedirEntero("Ingresar numero de asiento a reservar");
    
    // Buscar el asiento por ID usando lambda
    Asiento* asiento = listaAsientos.buscarPor([idAsiento](const Asiento& a) {
        return a.getId() == idAsiento;
    });
    
    if (!asiento) {
        vista.mostrarMensaje("Error: Asiento no encontrado");
        return;
    }
    
    // Verificar si está ocupado
    if (asiento->getEstado() == 1) {
        vista.mostrarMensaje("Error: El asiento ya esta OCUPADO. No puede ser reservado.");
        return;
    }
    
    // Reservar el asiento (cambiar estado a 1)
    asiento->setEstado(1);
    vista.mostrarMensaje("Exito: El asiento fue reservado exitosamente.");
}

void Controlador::iniciar() {
    int n = vista.pedirEntero("Ingresar numero de asientos (Creacion Estructura)");
    inicializarLista(n);

    bool salir = false;
    while (!salir) {
        vista.mostrarMensaje("\n1. Encerar Asientos (Reset Force Brute)");
        vista.mostrarMensaje("2. Mostrar Sala");
        vista.mostrarMensaje("3. Crear Patron de Alternancia Estricta (1-0-1-0)");
        vista.mostrarMensaje("4. Reservar Asiento");
        vista.mostrarMensaje("5. Salir");
        
        int opcion = vista.pedirEntero("Seleccione opcion");

        switch (opcion) {
            case 1: encerarAsientos(); break;
            case 2: mostrarEstadoActual(); break;
            case 3: crearPatronAlternado(); break;
            case 4: reservarAsiento(); break;
            case 5: salir = true; break;
        }
    }
}