#ifndef LISTACIRCULAR_HPP
#define LISTACIRCULAR_HPP

#include "Nodo.hpp"
#include <functional> // Necesario solo para el tipo std::function del lambda

template <typename T>
class ListaCircular {
private:
    Nodo<T>* cabeza;
    int tamano;

    // Helper recursivo privado para recorrido exhaustivo
    void recorridoRecursivo(Nodo<T>* actual, Nodo<T>* inicio, std::function<void(T&)> accion);

public:
    ListaCircular();
    ~ListaCircular();

    void insertar(T dato);
    
    // Método que acepta una expresión lambda para aplicar lógica a cada nodo
    void ejecutarEnTodos(std::function<void(T&)> accion);
    
    // Método para buscar y retornar un elemento por predicado
    T* buscarPor(std::function<bool(const T&)> predicado);
    
    bool estaVacia() const;
    int getTamano() const;
};

// Inclusión de la implementación de templates
#include "ListaCircular.tpp"

#endif