#include <iostream>
#include <string>
#include <sstream>
#include <cmath>  
#include "LL.hpp" 
#include "TreeNode.hpp" 

using namespace std;

int obtenerPrioridad(string op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool esOperador(string token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

bool validarParentesis(string expresion) {
    LL<char> pila; 
    
    for (char c : expresion) {
        if (c == '(') {
            pila.push(c);
        } else if (c == ')') {
            // Si intentamos cerrar y la pila está vacía (size == 0), está mal
            if (pila.isEmpty()) return false;
            pila.pop();
        }
    }
    // Si al final el size es 0, todo está balanceado
    return pila.isEmpty();
}

// ==========================================
// 3. CONVERSIÓN: INFIJA -> RPN (Shunting-yard)
// ==========================================
string convertirA_RPN(string infija) {
    LL<string> pilaOperadores; // Pila de strings para operadores
    string salida = "";
    stringstream ss(infija);
    string token;

    while (ss >> token) {
        // CASO A: Es un número (o variable)
        if (isdigit(token[0])) {
            salida += token + " ";
        }
        // CASO B: Paréntesis de apertura
        else if (token == "(") {
            pilaOperadores.push(token);
        }
        // CASO C: Paréntesis de cierre
        else if (token == ")") {
            // Sacar todo hasta encontrar el "("
            while (!pilaOperadores.isEmpty() && pilaOperadores.peek() != "(") {
                salida += pilaOperadores.pop() + " ";
            }
            if (!pilaOperadores.isEmpty()) {
                pilaOperadores.pop(); // Eliminar el "("
            }
        }
        // CASO D: Operador (+, -, *, /)
        else if (esOperador(token)) {
            while (!pilaOperadores.isEmpty() && 
                   obtenerPrioridad(pilaOperadores.peek()) >= obtenerPrioridad(token)) {
                salida += pilaOperadores.pop() + " ";
            }
            pilaOperadores.push(token);
        }
    }

    // Vaciar lo que quede en la pila
    while (!pilaOperadores.isEmpty()) {
        salida += pilaOperadores.pop() + " ";
    }

    return salida;
}

double evaluarArbol(TreeNode* raiz) {
    // Caso base: Si es una hoja (no tiene hijos), es un número
    if (raiz->left == nullptr && raiz->right == nullptr) {
        return stod(raiz->valor);
    }

    // Paso recursivo: Evaluar izquierda y derecha
    double valIzq = evaluarArbol(raiz->left);
    double valDer = evaluarArbol(raiz->right);

    // Aplicar operación
    if (raiz->valor == "+") return valIzq + valDer;
    if (raiz->valor == "-") return valIzq - valDer;
    if (raiz->valor == "*") return valIzq * valDer;
    if (raiz->valor == "/") return valIzq / valDer;
    if (raiz->valor == "^") return pow(valIzq, valDer);
    
    return 0;
}

TreeNode* construirArbolExpresion(string rpn) {
    LL<TreeNode*> pilaNodos; // Usamos tu lista como pila de punteros
    stringstream ss(rpn);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            // Es un número: Crear hoja y empujar
            pilaNodos.push(new TreeNode(token));
        } 
        else if (esOperador(token)) {
            // Es operador: Crear nodo padre con dos hijos
            TreeNode* derecha = pilaNodos.pop();
            TreeNode* izquierda = pilaNodos.pop();

            TreeNode* nuevoPadre = new TreeNode(token);
            nuevoPadre->left = izquierda;
            nuevoPadre->right = derecha;

            pilaNodos.push(nuevoPadre);
        }
    }
    // El último nodo que queda es la RAÍZ del árbol
    return pilaNodos.pop();
}

// Función auxiliar para imprimir espacios
void imprimirEspacios(int count) {
    for (int i = 0; i < count; i++)
        cout << " ";
}

// Imprime el árbol girado 90 grados
// 'espacio' indica la indentación actual
void imprimirArbol(TreeNode* raiz, int espacio = 0) {
    // Distancia entre niveles
    int COUNT = 5;

    // Caso base
    if (raiz == nullptr)
        return;

    // 1. Ir primero a la DERECHA
    espacio += COUNT;
    imprimirArbol(raiz->right, espacio);

    // 2. Imprimir el nodo actual
    cout << endl;
    imprimirEspacios(espacio - COUNT);
    cout << raiz->valor << "\n";

    // 3. Ir a la IZQUIERDA
    imprimirArbol(raiz->left, espacio);
}

int main() {
    string entradaUsuario;


    cout << "=========================================" << endl;
    cout << "   CALCULADORA DE ARBOL DE EXPRESION     " << endl;
    cout << "=========================================" << endl;
    cout << "Instrucciones:" << endl;
    cout << " - Separa TODO con espacios. Ej: 3 + ( 4 * 5 )" << endl;
    cout << " - Soportado: +, -, *, /, ^" << endl;
    cout << "Ingresa tu operacion: ";
    
    getline(cin, entradaUsuario);


    if (!validarParentesis(entradaUsuario)) {
        cerr << "\n[ERROR] Los parentesis no estan balanceados." << endl;
        return 1;
    }

    string rpn = convertirA_RPN(entradaUsuario);
    cout << "\n[1] Notacion Polaca Inversa (RPN): " << rpn << endl;

    TreeNode* raiz = construirArbolExpresion(rpn);
    cout << "[2] Arbol construido en memoria." << endl;
    
    cout << "\n--- VISUALIZACION DEL ARBOL ---" << endl;
    cout << "(Miralo inclinando la cabeza a la izquierda)" << endl;
    imprimirArbol(raiz);
    cout << "-------------------------------" << endl;


    try {
        double resultado = evaluarArbol(raiz);
        cout << "\n[3] RESULTADO FINAL: " << resultado << endl;
    } catch (...) {
        cerr << "[ERROR] Division por cero o error matematico." << endl;
    }

    return 0;
}