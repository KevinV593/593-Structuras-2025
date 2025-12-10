struct Nodo {
    int dato;
    Nodo *izq;
    Nodo *der;
    Nodo *padre;

    Nodo() : dato(0), 
    izq(nullptr), der(nullptr), 
    padre(nullptr) {}

    Nodo(int num, Nodo *padre) : dato(num), 
    izq(nullptr), der(nullptr),
    padre(padre) {}
};