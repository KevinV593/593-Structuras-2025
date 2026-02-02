#ifndef LL_HPP
#define LL_HPP

#include <iostream>

template <typename T>
class LL {
private:
    class Node {
        public:
        T value;
        Node* next;

        Node(T val) : value(val), next(nullptr) {}
        Node(T val, Node* nextNode) : value(val), next(nextNode) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LL() : head(nullptr), tail(nullptr), size(0) {}

    ~LL() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
// Fragmento necesario dentro de public: en LL.hpp

    // Insertar (Push) - Aumenta Size
    void push(T val) {
        Node* newNode = new Node(val, head);
        head = newNode;
        if (tail == nullptr) tail = head;
        size++; 
    }

    // Sacar (Pop) - Disminuye Size
    T pop() {
        if (isEmpty()) {
            // Manejo de error simple o throw exception
             throw std::runtime_error("Pila vacia");
        }
        Node* temp = head;
        T val = temp->value;
        head = head->next;
        delete temp;
        size--; 
        return val;
    }

    // Ver el tope (Peek/Top) - NECESARIO para conversión RPN
    T peek() {
        if (isEmpty()) throw std::runtime_error("Pila vacia");
        return head->value;
    }

    // Tu versión solicitada de isEmpty
    bool isEmpty() {
        return size == 0;
    }
    
    void display() {
        Node* auxiliar = head;
        if (auxiliar == nullptr) {
            std::cout << "Lista vacía" << std::endl;
            return;
        }
        while (auxiliar != nullptr) {
            std::cout << auxiliar->value << " -> ";
            auxiliar = auxiliar->next;
        }
        std::cout << "END" << std::endl;
    }

    void sizeList() {
        std::cout<< "Size: " << size << std::endl;
    }
};

#endif