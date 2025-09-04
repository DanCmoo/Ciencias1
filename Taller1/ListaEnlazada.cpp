#include <iostream>
#include "LISTA.h"

using namespace std;

// Función para imprimir lista
template<class T, class S>
void imprimirLista(Lista<T, S>& lista) {
    for (int i = 0; i < lista.getNumElementos(); i++) {
        nodo<T, S>* n = lista.buscar(i);
        if (n != nullptr) {
            cout << "Posicion " << i << ": " << n->dato1 << " , " << n->dato2 << endl;
        }
    }
    cout << "Total elementos: " << lista.getNumElementos() << "\n" << endl;
}

int main() {
    // --- Lista 1: int y float ---
    cout << "--- Lista 1: int y float ---" << endl;
    Lista<int, float> lista1;
    cout << "Lista vacia al inicio?: " << (lista1.listaVacia() ? "Si" : "No") << endl;

    // Insertar elementos
    lista1.insertarInicio(-2, -2.2);
    lista1.insertarInicio(-1, -1.1);
    lista1.insertarInicio(0, 0.0);

    lista1.insertar(1, 1.1, 2);
    lista1.insertar(2, 2.2, 4);
    lista1.insertar(4, 3.3, 5);
    lista1.insertar(3, 4.4, 6);


    // Insertar los del final
    lista1.insertarFinal(10, 10.1);
    lista1.insertarFinal(20, 20.2);
    lista1.insertarFinal(30, 30.3);

    imprimirLista(lista1);
    cout << "Lista vacia despues de insertar?: " << (lista1.listaVacia() ? "Si" : "No") << endl;

    // Modificar
    lista1.modificar(100, 100.5, 3);
    lista1.modificar(200, 200.5, 7);
    cout << "\nLista despues de modificaciones:" << endl;
    imprimirLista(lista1);

    // Borrar algunos
    lista1.borrar(0);
    lista1.borrar(4);
    lista1.borrar(lista1.getNumElementos() - 1);
    cout << "\nLista despues de borrar elementos:" << endl;
    imprimirLista(lista1);

    // Borrar la lista
    while (!lista1.listaVacia()) {
        lista1.borrar(0);
    }
    cout << "Lista vacia despues de borrar todo?: " << (lista1.listaVacia() ? "Si" : "No") << endl;
    cout << "\n\n";

    //  Lista 2: int y string ---
    cout << "---Lista 2: int y string ---" << endl;
    Lista<int, string> lista2;
    cout << "Lista vacia al inicio?: " << (lista2.listaVacia() ? "Si" : "No") << endl;

    lista2.insertarInicio(0, "cero");
    lista2.insertarInicio(-1, "menos uno");
    lista2.insertarInicio(-2, "menos dos");

    lista2.insertar(1, "uno", 2);
    lista2.insertar(2, "dos", 4);
    lista2.insertar(3, "tres", 5);
    lista2.insertar(4, "cuatro", 6);

    lista2.insertarFinal(100, "cien");
    lista2.insertarFinal(200, "doscientos");
    lista2.insertarFinal(300, "trescientos");
    imprimirLista(lista2);
    cout << "Lista vacia despues de insertar?: " << (lista2.listaVacia() ? "Si" : "No") << endl;

    lista2.modificar(999, "modificado", 3);
    lista2.modificar(888, "otro modificado", 7);
    cout << "\nLista despues de modificaciones:" << endl;
    imprimirLista(lista2);

    lista2.borrar(0);
    lista2.borrar(4);
    lista2.borrar(lista2.getNumElementos() - 1);
    cout << "\nLista despues de borrar elementos:" << endl;
    imprimirLista(lista2);

    while (!lista2.listaVacia()) {
        lista2.borrar(0);
    }
    cout << "Lista vacia despues de borrar todo?: " << (lista2.listaVacia() ? "Si" : "No") << endl;
    cout << "\n\n";

    // === Lista 3: char y string ===
    cout << "--- Lista 3: char y string ---" << endl;
    Lista<char, string> lista3;
    cout << "Lista vacia al inicio?: " << (lista3.listaVacia() ? "Si" : "No") << endl;

    lista3.insertarInicio('X', "Letra X");
    lista3.insertarInicio('Y', "Letra Y");
    lista3.insertarInicio('Z', "Letra Z");

    lista3.insertar('M', "Letra M", 2);
    lista3.insertar('N', "Letra N", 4);
    lista3.insertar('P', "Letra O", 5);
    lista3.insertar('O', "Letra P", 6);

    lista3.insertarFinal('A', "Letra A");
    lista3.insertarFinal('B', "Letra B");
    lista3.insertarFinal('C', "Letra C");

    imprimirLista(lista3);
    cout << "Lista vacia despues de insertar?: " << (lista3.listaVacia() ? "Si" : "No") << endl;

    lista3.modificar('Q', "Modificado Q", 3);
    lista3.modificar('R', "Modificado R", 7);
    lista3.modificar('R', "Modificado R", 7);
    cout << "\nLista despues de modificaciones:" << endl;


    imprimirLista(lista3);

    lista3.borrar(0);
    lista3.borrar(4);
    lista3.borrar(lista3.getNumElementos() - 1);
    cout << "\nLista despues de borrar elementos:" << endl;

    imprimirLista(lista3);

    while (!lista3.listaVacia()) {
        lista3.borrar(0);
    }
    cout << "Lista vacia despues de borrar todo?: " << (lista3.listaVacia() ? "Si" : "No") << endl;

    return 0;
}
