#include <iostream>
#include "DOUBLELIST.h"
using namespace std;

// Función para imprimir de inicio a fin
template <class T>
void imprimirListaInicioAFinal(DoubleList<T>& lista) {
    nodo<T>* aux = lista.getHead()->next; // Inicio de la lista
    cout << "Lista (inicio -> final):" << endl;
    while (aux != lista.getHead()) {
        cout << aux->ID << ": " << aux->info << endl;
        aux = aux->next;
    }
}

// Función para imprimir de fin a inicio
template <class T>
void imprimirListaFinalAInicio(DoubleList<T>& lista) {
    nodo<T>* aux = lista.getHead()->prev; // Fin de la lista
    cout << "Lista (final -> inicio):" << endl;
    while (aux != lista.getHead()) {
        cout << aux->ID << ": " << aux->info << endl;
        aux = aux->prev;
    }
}

template <typename T>
void probarLista(DoubleList<T>& lista, T idExistente, T idInexistente, T idModificar, const string& nuevaInfo, T idEliminar) {
    cout << "Insertando elementos..." << endl;
    int contador = 0;
    for (int i = 0; contador < 5; i++) {
        T id;
        if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value) {
            id = idExistente + static_cast<T>(i);
            if (id == idModificar || id == idEliminar || id == idInexistente)
                continue;
        } else if constexpr (std::is_same<T, std::string>::value) {
            id = idExistente + to_string(i);
            if (id == idModificar || id == idEliminar || id == idInexistente)
                continue;
        }

        lista.insert(id, "Elemento " + to_string(contador + 1));
        contador++;
    }

    lista.insert(idModificar, "Elemento a Modificar");
    lista.insert(idEliminar, "Elemento a Eliminar");

    imprimirListaInicioAFinal(lista);

    // Intentar modificar
    cout << "\nIntentando modificar elemento con ID " << idModificar << "..." << endl;
    if (lista.modify(idModificar, nuevaInfo)) {
        cout << "Modificado exitosamente.\n";

        // Buscar e imprimir el elemento modificado
        nodo<T>* modificado = lista.find(idModificar);
        if (modificado != nullptr) {
            cout << "Elemento modificado encontrado: " << modificado->ID << ": " << modificado->info << endl;
        } else {
            cout << "No se encontró el elemento modificado (esto no debería pasar).\n";
        }
    } else {
        cout << "No se encontró para modificar.\n";
    }
    imprimirListaInicioAFinal(lista);

    // Buscar ID existente
    cout << "\nBuscando ID " << idExistente << "..." << endl;
    nodo<T>* buscado = lista.find(idExistente);
    if (buscado != lista.getHead()) {
        cout << "Encontrado: " << buscado->info << endl;
    } else {
        cout << "No encontrado.\n";
    }

    // Buscar ID inexistente
    cout << "\nBuscando ID " << idInexistente << "..." << endl;
    nodo<T>* noEncontrado = lista.find(idInexistente);
    if (noEncontrado != lista.getHead()) {
        cout << "Encontrado (esto no debería pasar): " << noEncontrado->info << endl;
    } else {
        cout << "No encontrado.\n";
    }

    // Eliminar ID
    cout << "\nEliminando ID " << idEliminar << "..." << endl;
    if (lista.erase(idEliminar)) {
        cout << "Eliminado.\n";
    } else {
        cout << "No encontrado para eliminar.\n";
    }

    // Mostrar la lista en orden ascendente
    cout << "\nMostrar en orden ascendente:\n";
    imprimirListaInicioAFinal(lista);

    // Mostrar la lista en orden descendente
    cout << "\nMostrar en orden descendente:\n";
    imprimirListaFinalAInicio(lista);

    // Tamaño de la lista
    cout << "Tamano de la lista: " << lista.getSize() << "\n\n";
}

int main() {
    // Lista de enteros
    cout << "----- Lista de Enteros -----" << endl;
    DoubleList<int> listaEnteros;
    probarLista(listaEnteros, 10, 999, 20, "Modificado Entero", 30);
    cout << string(50, '-') << "\n\n";

    // Lista de Flotantes
    cout << "----- Lista de Flotantes -----" << endl;
    DoubleList<float> listaFloats;
    probarLista(listaFloats, 1.5f, 9.9f, 2.5f, "Modificado Float", 3.3f);
    cout << string(50, '-') << "\n\n";


    // Lista de cadenas
    cout << "----- Lista de Cadenas -----" << endl;
    DoubleList<string> listaStrings;
    probarLista(listaStrings,
            string("abc"),
            string("zzz"),
            string("mno"),
            "Modificado String", // este está bien porque es string en el parámetro de info
            string("xyz"));

    return 0;
}
