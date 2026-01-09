#include <iostream>
#include <math.h>
using std::cin;
using std::cout;
using std::abs;
int x = 0;

bool esSeguro(int *reinas, int n, int k) {
    for (int i = 0; i < k; i++) {
        if( *(reinas + i) == *(reinas + k) 
        || abs(i - k) == abs(*(reinas + i) - *(reinas + k))) {
            return false;
        }
    }
    return true;
}

void Nreinas (int *reinas, int n, int k) {
    if (k==n) {
        x++;
        cout<<"Solucion No."<<x<<": ";
        for (int i = 0; i < n; i++) {
            cout<<*(reinas + i)<<", ";
        }
        cout<<"\n";
    }
    else {
        for(*(reinas + k) = 0; *(reinas + k) < n; (*(reinas + k))++) {
            if(esSeguro(reinas, n, k)) {
                Nreinas(reinas, n, k+1);
            }
        }
    }
}

int main () {
    int p = 0;
    int n;

    cout<<"Ingrese la cantidad de reinas: ";
    cin>>n;

    int *reinas = new int[n];

    Nreinas(reinas, n, p);
    
    return 0;
}