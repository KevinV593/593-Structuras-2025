#include "Validacion.hpp"
#include <iostream>
#include <conio.h> 
#include <cstdlib> 
#include <cctype> 

using std::cout;
using std::cin;
using std::string;
using std::endl;

// Valida que la cadena no esté vacía y sea un número válido
bool Validacion::validarEntero(string numero) {
    if (numero.empty()) return false;
    if (numero == "-") return false;
    if (numero == "+") return false; // El signo solo no es número
    return true;
}

int Validacion::ingresarEntero(string mensaje) {
    string numero;
    bool valido = false;
    
    cout << mensaje; // Mostramos el mensaje (ej: "Ingrese fila: ")

    while (!valido) {
        try {
            char c;
            while (true) {
                c = _getch(); // Captura tecla sin imprimirla automáticamente
                
                // 1. Si es ENTER (\r) termina la entrada
                if (c == '\r') {
                    cout << endl;
                    break;
                }
                // 2. Si es BACKSPACE (\b) borra el último caracter
                else if (c == '\b') {
                    if (!numero.empty()) {
                        numero.pop_back();
                        cout << "\b \b"; // Borrado visual en consola
                    }
                }
                // 3. Aceptar dígitos
                else if (isdigit(c)) {
                    numero += c;
                    cout << c;
                }
                // 4. Aceptar signo negativo (-) SOLO al inicio
                else if (c == '-' && numero.empty()) {
                    numero += c;
                    cout << c;
                }
                // Cualquier otra tecla es ignorada
            }

            valido = validarEntero(numero);
            
            if (!valido) {
                throw numero;
            }
        }
        catch (string e) {
            cout << ">> Entrada invalida. Intente de nuevo: ";
            numero.clear();
            valido = false;
        }
    }
    return atoi(numero.c_str());
}
