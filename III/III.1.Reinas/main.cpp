#include <iostream>
#include <math.h>
#include "Validacion.hpp"

using std::cin;
using std::cout;
using std::abs;
int x = 0;

bool esSeguro(int *reinas, int p) {
    for (int i = 0; i < p; i++) {
        if( *(reinas + i) == *(reinas + p) 
        || abs(i - p) == abs(*(reinas + i) - *(reinas + p))) {
            return false;
        }
    }
    return true;
}

void imprimirTablero(int *reinas, int n) {
    cout<<"\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ( *(reinas + i) == j) {
                cout<< " Q ";
            } else {
                cout << " . ";
            }
        }
    cout<<"\n";
    }
}

void Nreinas (int *reinas, int n, int p) {
    if (p==n) {
        x++;
        cout<<"Sol No."<<x<<":\t";
        for (int i = 0; i < n; i++) {
            cout<<*(reinas + i)<<"| ";
        }
        cout<<"\n";
        imprimirTablero(reinas, n);
    }
    else {
        for(*(reinas + p) = 0; *(reinas + p) < n; (*(reinas + p))++) {
            if(esSeguro(reinas, p)) {
                Nreinas(reinas, n, p+1);
            }
        }
    }
}

int main () {
    int p = 0;
    int n;
    n = Validacion::ingresarEntero("Ingrese la cantidad de reinas: ");

    int *reinas = new int[n];

    Nreinas(reinas, n, p);
    
    return 0;
}