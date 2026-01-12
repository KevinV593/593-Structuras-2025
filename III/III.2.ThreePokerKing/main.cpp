#include <iostream>
#include <time.h>
#include "Validacion.hpp"
using std::cout;
using std::cin;

void jugar3Cartas(int &dinero, int &apuesta) {    
    int suposicion;
    char *mazo = new char[3];
    *(mazo + 0) = 'J';
    *(mazo + 1) = 'Q';
    *(mazo + 2) = 'K';
    
    cout<<"Las posiciones (1,2,3) son: "<<*(mazo + 0)<<", "<<*(mazo + 1)<<", "<<*(mazo + 2)<<"\n";

    for (int i = 0; i <= 10; ++i) {
        int x = rand()%3;
        int y = rand()%3;

        int temp = *(mazo + x);
        *(mazo + x)=*(mazo + y);
        *(mazo + y)=temp;
    }

    cout<<"Ya esta barajeada.\n";
    cout<<"En que posicion (1,2,3) esta el rey?: ";
    cin>>suposicion;
    --suposicion;

    cout<<"Las posiciones eran: "<<*(mazo + 0)<<*(mazo + 1)<<*(mazo + 2)<<"\n";

    if(*(mazo+suposicion)=='K') {
        dinero += 2*apuesta;
        cout<<"Ganaste! Ahora tienes un total de: "<<dinero<< " latas.";
    } else {
        cout<< "Perdiste! Tienes un total de: "<<dinero<<" latas.";
    }
    delete[] mazo;
}

int main () {
    srand(time(NULL));

    int dinero = 10;
    int apuesta;
    cout<< "Bienvenido al Casino! \n";
    cout<< "Comienzas con un total de " << dinero << " latas.";
    do {
        apuesta = Validacion::ingresarEntero("Cuanto vas a apostar?: ");
        
        if (apuesta <= 0|| apuesta > dinero ) {
            cout<<"No puedes apostar esa cantidad.\n";
        } else {         
            dinero -= apuesta;
            jugar3Cartas(dinero, apuesta);
        }

    } while ( dinero > 0);

    cout<< "Te quedaste sin plata. ADIOS!";
    system("pause");
    
    return 0;
}