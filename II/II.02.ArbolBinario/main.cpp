#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

#include "Nodo.hpp"

void insertarNodo(Nodo *&arbol, int n, Nodo *padre) {
    if(arbol == nullptr) {
        Nodo *nuevo = new Nodo(n, padre);
        arbol = nuevo;

        cout << "Elemento " << n << " insertado correctamente." << endl;    
    } else {
        int valorRaiz = arbol->dato;

        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n, arbol);
        } else {
            insertarNodo(arbol->der, n, arbol);
        }
    }
};

void mostrarArbol(Nodo *&arbol, int cont) {
    if (arbol == nullptr) {
        return;
    } else {
        mostrarArbol(arbol->der, cont+1);
        for(int i = 0; i < cont; i++) {
            cout<<"\t";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq, cont+1);
    }
};

bool busqueda(Nodo *&arbol, int n) {
    if (arbol == nullptr) {
        return false;
    }
    else if (arbol->dato == n){
        return true;
    }
    else if (n < arbol->dato) {
        return busqueda(arbol->izq, n);
    }
    else {
        return busqueda(arbol->der, n);
    }
};

void prefijoOrden(Nodo *&arbol) {
    if (arbol == nullptr) {
        return;
    } else {
        cout<<arbol->dato<<" - ";
        prefijoOrden(arbol->izq);
        prefijoOrden(arbol->der);
    }
};

void infijoOrden(Nodo *&arbol) {
    if (arbol == nullptr) {
        return;
    } else {
        infijoOrden(arbol->izq);
        cout<<arbol->dato<<" - ";
        infijoOrden(arbol->der);
    }
};

void postfijoOrden(Nodo *&arbol) {
    if (arbol == nullptr) {
        return;
    } else {
        postfijoOrden(arbol->izq);
        postfijoOrden(arbol->der);
        cout<<arbol->dato<<" - ";
    }
};

Nodo *minimo(Nodo *arbol) {
    if(arbol==nullptr) {
        return nullptr;
    } 

    if(arbol->izq){
        return minimo(arbol->izq);
    }
    
    return arbol;
};

void reemplazar(Nodo *&arbol, Nodo *&nuevo) {
    if(arbol->padre) {
        if (arbol->dato == arbol->padre->izq->dato) {
            arbol->padre->izq = nuevo;
        }
        else if (arbol->dato == arbol->padre->der->dato) {
            arbol->padre->der = nuevo;
        }
    }
    if(nuevo){
        nuevo->padre = arbol->padre;
    }
};

void destruir(Nodo *&arbol) {
    arbol->izq = nullptr;
    arbol->der = nullptr;
    delete arbol;
};

void eliminarNodo(Nodo *&nodoAEliminar) {
    //SI TIENE DOS HIJOS (hijo & nieto)
    if(nodoAEliminar->izq && nodoAEliminar->der){
        Nodo *menor = minimo(nodoAEliminar->der);
        nodoAEliminar->dato=menor->dato;
        eliminarNodo(menor);
    }
    
    //SI TIENE UN HIJO IZQ O DER
    else if(nodoAEliminar->izq) {
        reemplazar(nodoAEliminar, nodoAEliminar->izq);
        destruir(nodoAEliminar);
    } else if (nodoAEliminar->der) {
        reemplazar(nodoAEliminar, nodoAEliminar->der);
        destruir(nodoAEliminar);
    }

    else {
        Nodo* temp = nullptr;
        reemplazar(nodoAEliminar, temp);
        destruir(nodoAEliminar);
    }
};

void elementoAEliminar(Nodo *arbol, int n) {
    if (arbol == nullptr) {
        return;
    } else if (n < arbol->dato) {
        elementoAEliminar(arbol->izq, n);
    } else if(n > arbol->dato) {
        elementoAEliminar(arbol->der, n);
    } else {
        eliminarNodo(arbol);
    }
};

void menu(Nodo *&arbol) {
    int dato = 0, opcion = 0, contador = 0;

    do{
        cout<<"\t| |    ARBOL BINARIO    | |"<<endl;
        cout<<"\t1. Insertar un nuevo nodo."<<endl;
        cout<<"\t2. Mostrar arbol."<<endl;
        cout<<"\t3. Buscar elemento."<<endl;
        cout<<"\t4. Orden Prefijo."<<endl;
        cout<<"\t5. Orden Infijo."<<endl;
        cout<<"\t6. Orden Postfijo."<<endl;
        cout<<"\t7. Eliminar Nodo."<<endl;
        cout<<"\t8. Salir."<<endl;
        cout<<"Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: cout<<"Digite un numero: ";
                    cin >> dato;
                    insertarNodo(arbol, dato, nullptr);
                    cout<<"\n";
                    system("pause");
                    break;

            case 2: cout << "Grafico girado a la izquierda:" << endl;
                    mostrarArbol(arbol, contador);
                    system("pause");
                    break;

            case 3: cout<<"Digite el elemento a buscar: ";
                    cin >> dato;
                    if(busqueda(arbol, dato) == true) {
                        cout<<"Elemento "<< dato <<" ha sido encontrado.\n";
                    } else {
                        cout<<"Elemento no encontrado.\n";
                    }
                    system("pause");
                    break;

            case 4: cout << "Arbol en Orden Prefijo:" << endl;
                    prefijoOrden(arbol);
                    system("pause");
                    break;

            case 5: cout << "Arbol en Orden Infijo:" << endl;
                    infijoOrden(arbol);
                    system("pause");
                    break;

            case 6: cout << "Arbol en Orden Postfijo:" << endl;
                    postfijoOrden(arbol);
                    system("pause");
                    break;

            case 7: cout<<"Digite el elemento a eliminar: ";
                    cin >> dato;
                    if(busqueda(arbol, dato) == true) {
                        elementoAEliminar(arbol, dato);
                        cout<<"Elemento "<< dato <<" ha sido eliminado.\n";
                    } else {
                        cout<<"Elemento no existente.\n";
                    }
                    system("pause");
                    break;
            case 8: cout << "Gracias por usar el sistema :)" << endl;
                    system("pause");
                    break;

            default:    cout << "Opcion no valida" << endl;
                        system("pause");
                        break;
        }
        system("cls");
    } while(opcion != 8);
};

int main() {
    Nodo *arbol = nullptr;

    menu(arbol);

    return 0;
};