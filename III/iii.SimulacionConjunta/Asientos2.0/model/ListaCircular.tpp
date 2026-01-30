#ifndef LISTACIRCULAR_TPP
#define LISTACIRCULAR_TPP

template <typename T>
ListaCircular<T>::ListaCircular() : cabeza(nullptr), tamano(0) {}

template <typename T>
ListaCircular<T>::~ListaCircular() {
    // Lógica de destrucción manual omitida por brevedad, pero necesaria en prod
}

template <typename T>
void ListaCircular<T>::insertar(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    } else {
        Nodo<T>* ultimo = cabeza->getAnterior();
        
        // Aritmética de punteros para re-enlazar
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
    tamano++;
}

// Implementación de RECURSIVIDAD y FUERZA BRUTA (Recorrido exhaustivo)
template <typename T>
void ListaCircular<T>::recorridoRecursivo(Nodo<T>* actual, Nodo<T>* inicio, std::function<void(T&)> accion) {
    if (!actual) return;

    // Ejecutar la lambda sobre el dato actual
    accion(actual->getDato());

    // Condición de parada: Si el siguiente es la cabeza, hemos completado el ciclo
    if (actual->getSiguiente() != inicio) {
        // Llamada recursiva avanzando el puntero
        recorridoRecursivo(actual->getSiguiente(), inicio, accion);
    }
}

template <typename T>
void ListaCircular<T>::ejecutarEnTodos(std::function<void(T&)> accion) {
    if (cabeza) {
        recorridoRecursivo(cabeza, cabeza, accion);
    }
}

template <typename T>
T* ListaCircular<T>::buscarPor(std::function<bool(const T&)> predicado) {
    if (!cabeza) return nullptr;
    
    Nodo<T>* actual = cabeza;
    do {
        if (predicado(actual->getDato())) {
            return &(actual->getDato());
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    
    return nullptr;
}

#endif