#ifndef NODO_HPP
#define NODO_HPP

template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

public:
    Nodo(T dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}

    // Aritmética de punteros para acceso y modificación
    T& getDato() { return dato; }
    
    Nodo<T>* getSiguiente() const { return siguiente; }
    void setSiguiente(Nodo<T>* nodo) { siguiente = nodo; }

    Nodo<T>* getAnterior() const { return anterior; }
    void setAnterior(Nodo<T>* nodo) { anterior = nodo; }
};

#endif