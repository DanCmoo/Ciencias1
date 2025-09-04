#include <iostream>
#include "RedBlackTree.h"

using namespace std;

void imprimirRecorrido(queue<pair<int, string>> cola, const string& nombre) {
    cout << "\n" << nombre << ":" << endl;
    if (cola.empty()) {
        cout << "Arbol vacio" << endl;
        return;
    }

    while (!cola.empty()) {
        pair<int, string> elemento = cola.front();
        cola.pop();
        cout << "Clave: " << elemento.first
             << ", Informacion: " << elemento.second << endl;
    }
}

void mostrarCasosDePrueba() {
    cout << "\n=== CASOS DE PRUEBA PARA ARBOL ROJINEGRO ===" << endl;
    cout << "Se insertaran claves que demuestren los 3 casos de ajuste:" << endl;
    cout << "Caso 1: Tio rojo - Recoloreo" << endl;
    cout << "Caso 2: Tio negro, k es hijo derecho - Rotacion izquierda + Caso 3" << endl;
    cout << "Caso 3: Tio negro, k es hijo izquierdo - Rotacion derecha" << endl;
}

int main() {
    ArbolRojiNegro arbol;

    cout << "=== IMPLEMENTACION DE ARBOL ROJINEGRO ===" << endl;
    mostrarCasosDePrueba();

    // FASE 1: Insertar claves que muestren los 3 casos de ajuste
    cout << "\n--- FASE 1: INSERCION CON CASOS DE AJUSTE ---" << endl;

    // Secuencia que genera los casos de ajuste
    cout << "Insertando 10..." << endl;
    arbol.insertar(10, "Raiz inicial - Negro");
    arbol.mostrarArbol();

    cout << "\nInsertando 5..." << endl;
    arbol.insertar(5, "Hijo izquierdo - Rojo");
    arbol.mostrarArbol();

    cout << "\nInsertando 15..." << endl;
    arbol.insertar(15, "Hijo derecho - Rojo");
    arbol.mostrarArbol();

    cout << "\nInsertando 3 (Caso 1: Tio rojo - Recoloreo)..." << endl;
    arbol.insertar(3, "Provoca recoloreo");
    arbol.mostrarArbol();

    cout << "\nInsertando 7..." << endl;
    arbol.insertar(7, "Hijo derecho de 5");
    arbol.mostrarArbol();

    cout << "\nInsertando 6 (Caso 2: k hijo derecho, luego Caso 3)..." << endl;
    arbol.insertar(6, "Provoca rotacion izquierda + derecha");
    arbol.mostrarArbol();

    cout << "\nInsertando 12..." << endl;
    arbol.insertar(12, "Hijo izquierdo de 15");
    arbol.mostrarArbol();

    cout << "\nInsertando 18..." << endl;
    arbol.insertar(18, "Hijo derecho de 15");
    arbol.mostrarArbol();

    // FASE 2: Mostrar primeros dos recorridos
    cout << "\n--- FASE 2: PRIMEROS RECORRIDOS ---" << endl;
    imprimirRecorrido(arbol.recorridoInorden(), "RECORRIDO INORDEN");
    imprimirRecorrido(arbol.recorridoPreorden(), "RECORRIDO PREORDEN");

    // FASE 3: Buscar clave
    cout << "\n--- FASE 3: BUSQUEDA ---" << endl;
    int claveBuscar;
    cout << "Ingrese una clave a buscar: ";
    cin >> claveBuscar;

    string resultado = arbol.buscar(claveBuscar);
    if (!resultado.empty()) {
        cout << "Informacion encontrada: " << resultado << endl;
    } else {
        cout << "Clave no encontrada." << endl;
    }

    // FASE 4: Eliminar claves que evidencien los 4 casos
    cout << "\n--- FASE 4: ELIMINACION CON CASOS DE AJUSTE ---" << endl;
    cout << "Los 4 casos de eliminacion son:" << endl;
    cout << "1. Nodo rojo hoja" << endl;
    cout << "2. Nodo negro con un hijo rojo" << endl;
    cout << "3. Nodo negro hoja (requiere ajuste)" << endl;
    cout << "4. Nodo con dos hijos" << endl;

    cout << "\nEliminando 18 (Caso 1: Nodo rojo hoja)..." << endl;
    arbol.eliminar(18);
    arbol.mostrarArbol();

    cout << "\nEliminando 3 (Caso 2: Puede tener un hijo)..." << endl;
    arbol.eliminar(3);
    arbol.mostrarArbol();

    cout << "\nEliminando 12 (Caso 3: Nodo que puede requerir ajuste)..." << endl;
    arbol.eliminar(12);
    arbol.mostrarArbol();

    cout << "\nEliminando 10 (Caso 4: Nodo con dos hijos)..." << endl;
    arbol.eliminar(10);
    arbol.mostrarArbol();

    // FASE 5: Mostrar ultimos dos recorridos
    cout << "\n--- FASE 5: RECORRIDOS FINALES ---" << endl;
    imprimirRecorrido(arbol.recorridoPosorden(), "RECORRIDO POSORDEN");
    imprimirRecorrido(arbol.recorridoPorNiveles(), "RECORRIDO POR NIVELES");

    // FASE 6: Demostrar modificacion
    cout << "\n--- FASE 6: MODIFICACION DE INFORMACION ---" << endl;
    cout << "Modificando informacion de la clave 7..." << endl;
    if (arbol.modificar(7, "Informacion modificada para clave 7")) {
        cout << "Informacion modificada exitosamente." << endl;
        cout << "Nueva informacion: " << arbol.buscar(7) << endl;
    } else {
        cout << "No se pudo modificar la informacion." << endl;
    }

    cout << "\n--- PROGRAMA FINALIZADO ---" << endl;
    return 0;
}