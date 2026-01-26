#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {

    int n;
    cout<<"Ingresa la dimnesion";
    cin>>n;
    int** matriz = new int*[n];

    for (int i = 0; i < n; i++) {
        *(matriz + i) = new int[n];
        for (int j = 0; j < n; j++) {
            *(*(matriz + i) + j) = i + j;
        }
    }

    auto procesar = [](auto self, int **matriz, int f, int c) -> int {
        if (f == n) {
            return 0; }
        if (c == n) {
            return self(self, matriz, f+1,0);
        }
        return *(*(matriz + f) + c) + self(self, matriz, f, c+1);
    };

    cout<<"Suma total en la matriz: "<<procesar(procesar, matriz, 0, 0);
}