#include <iostream>
#include "pila1.h"
using namespace std;

//Ejercicio 1
//De: Juliana Puerto y Daniel Camacho

// Función plantilla Reemplazar
template <typename T>
void Reemplazar(pila& p, T viejo, T nuevo) {
    pila aux;

    while (!p.PilaVacia()) {
        T val = p.Pop();
        if (val == viejo)
            aux.Push(nuevo);
        else
            aux.Push(val);
    }

    while (!aux.PilaVacia()) {
        p.Push(aux.Pop());
    }
}

int main() {
    pila p;
    int n;
    char valor, viejo, nuevo;

    cout << "Cuantos elementos quieres ingresar a la pila? ";
    cin >> n;

    cout << "Ingresa " << n << " caracteres (uno por uno):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Elemento #" << (i + 1) << ": ";
        cin >> valor;
        p.Push(valor);
    }

    cout << "\nIngrese el valor que desea reemplazar: ";
    cin >> viejo;
    cout << "Ingrese el nuevo valor: ";
    cin >> nuevo;

    Reemplazar<char>(p, viejo, nuevo);

    cout << "\nContenido final de la pila (de arriba hacia abajo):\n";
    while (!p.PilaVacia()) {
        cout << p.Pop() << " ";
    }
    cout << endl;

    return 0;
}
