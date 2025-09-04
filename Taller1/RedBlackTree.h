#ifndef ARBOL_ROJINEGRO_H
#define ARBOL_ROJINEGRO_H

#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Estructura del nodo segun especificacion
struct nodo {
    int clave;
    nodo *izq, *der;
    bool color;  // true = ROJO, false = NEGRO
    string informacion;  // Informacion asociada

    nodo(int k, const string& info)
        : clave(k), izq(nullptr), der(nullptr), color(true), informacion(info) {}
};

class ArbolRojiNegro {
private:
    nodo* raiz;

    // Funciones auxiliares para rotaciones
    void rotacionIzquierda(nodo*& x);
    void rotacionDerecha(nodo*& x);

    // Funciones de ajuste
    void ajustarInsercion(nodo*& k);
    void ajustarEliminacion(nodo*& x);

    // Funciones auxiliares
    void trasplantar(nodo* u, nodo* v);
    nodo* minimo(nodo* node) const;
    nodo* buscarNodo(int clave) const;
    nodo* buscarPadre(nodo* hijo) const;
    void eliminarNodo(nodo* z);

    // Liberacion de memoria
    void limpiar(nodo* node);

public:
    ArbolRojiNegro();
    ~ArbolRojiNegro();

    // Funciones principales
    bool insertar(int clave, const string& informacion);
    bool eliminar(int clave);
    string buscar(int clave);
    bool modificar(int clave, const string& nuevaInformacion);

    // Recorridos iterativos
    queue<pair<int, string>> recorridoInorden();
    queue<pair<int, string>> recorridoPreorden();
    queue<pair<int, string>> recorridoPosorden();
    queue<pair<int, string>> recorridoPorNiveles();

    // Funcion para mostrar arbol con colores
    void mostrarArbol();
    void mostrarArbolHelper(nodo* node, int nivel = 0) const;
};

// CONSTRUCTOR Y DESTRUCTOR
ArbolRojiNegro::ArbolRojiNegro() {
    raiz = nullptr;
}

ArbolRojiNegro::~ArbolRojiNegro() {
    limpiar(raiz);
}

void ArbolRojiNegro::limpiar(nodo* node) {
    if (!node) return;
    limpiar(node->izq);
    limpiar(node->der);
    delete node;
}

// ROTACIONES
void ArbolRojiNegro::rotacionIzquierda(nodo*& x) {
    nodo* y = x->der;
    x->der = y->izq;

    // Actualizar padre de la raiz
    if (x == raiz) {
        raiz = y;
    }

    y->izq = x;
    x = y;
}

void ArbolRojiNegro::rotacionDerecha(nodo*& x) {
    nodo* y = x->izq;
    x->izq = y->der;

    // Actualizar padre de la raiz
    if (x == raiz) {
        raiz = y;
    }

    y->der = x;
    x = y;
}

// INSERCION
bool ArbolRojiNegro::insertar(int clave, const string& informacion) {
    // Verificar si la clave ya existe
    if (buscarNodo(clave) != nullptr) {
        return false;
    }

    nodo* nuevo = new nodo(clave, informacion);

    // Insercion BST estandar
    if (raiz == nullptr) {
        raiz = nuevo;
        nuevo->color = false; // La raiz siempre es negra
        return true;
    }

    nodo* actual = raiz;
    nodo* padre = nullptr;

    while (actual != nullptr) {
        padre = actual;
        if (clave < actual->clave) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }

    if (clave < padre->clave) {
        padre->izq = nuevo;
    } else {
        padre->der = nuevo;
    }

    nuevo->color = true; // Nuevo nodo es rojo

    // Ajustar arbol para mantener propiedades rojo-negro
    ajustarInsercion(nuevo);

    return true;
}

void ArbolRojiNegro::ajustarInsercion(nodo*& k) {
    while (k != raiz && buscarPadre(k) && buscarPadre(k)->color == true) {
        nodo* padre = buscarPadre(k);
        nodo* abuelo = buscarPadre(padre);

        if (!abuelo) break;

        if (padre == abuelo->izq) {
            nodo* tio = abuelo->der;

            // Caso 1: Tio es rojo
            if (tio && tio->color == true) {
                padre->color = false;
                tio->color = false;
                abuelo->color = true;
                k = abuelo;
            } else {
                // Caso 2: k es hijo derecho
                if (k == padre->der) {
                    k = padre;
                    rotacionIzquierda(padre);
                    padre = buscarPadre(k);
                    abuelo = buscarPadre(padre);
                }
                // Caso 3: k es hijo izquierdo
                if (padre && abuelo) {
                    padre->color = false;
                    abuelo->color = true;
                    rotacionDerecha(abuelo);
                }
            }
        } else {
            nodo* tio = abuelo->izq;

            // Caso 1: Tio es rojo
            if (tio && tio->color == true) {
                padre->color = false;
                tio->color = false;
                abuelo->color = true;
                k = abuelo;
            } else {
                // Caso 2: k es hijo izquierdo
                if (k == padre->izq) {
                    k = padre;
                    rotacionDerecha(padre);
                    padre = buscarPadre(k);
                    abuelo = buscarPadre(padre);
                }
                // Caso 3: k es hijo derecho
                if (padre && abuelo) {
                    padre->color = false;
                    abuelo->color = true;
                    rotacionIzquierda(abuelo);
                }
            }
        }
    }
    raiz->color = false; // La raiz siempre es negra
}

// ELIMINACION
bool ArbolRojiNegro::eliminar(int clave) {
    nodo* node = buscarNodo(clave);
    if (node == nullptr) {
        return false;
    }

    cout << "Eliminando nodo con clave " << clave << " e informacion: " << node->informacion << endl;
    eliminarNodo(node);
    return true;
}

void ArbolRojiNegro::eliminarNodo(nodo* z) {
    nodo* y = z;
    nodo* x;
    bool colorOriginalY = y->color;

    if (z->izq == nullptr) {
        x = z->der;
        trasplantar(z, z->der);
    } else if (z->der == nullptr) {
        x = z->izq;
        trasplantar(z, z->izq);
    } else {
        y = minimo(z->der);
        colorOriginalY = y->color;
        x = y->der;

        if (buscarPadre(y) == z) {
            // x puede ser nullptr, pero no importa para el ajuste
        } else {
            trasplantar(y, y->der);
            y->der = z->der;
        }

        trasplantar(z, y);
        y->izq = z->izq;
        y->color = z->color;
    }

    delete z;

    if (colorOriginalY == false && x) {
        ajustarEliminacion(x);
    }
}

void ArbolRojiNegro::ajustarEliminacion(nodo*& x) {
    while (x != raiz && x->color == false) {
        nodo* padre = buscarPadre(x);
        if (!padre) break;

        if (x == padre->izq) {
            nodo* w = padre->der;
            if (!w) break;

            if (w->color == true) {
                w->color = false;
                padre->color = true;
                rotacionIzquierda(padre);
                w = padre->der;
            }

            if ((!w->izq || w->izq->color == false) &&
                (!w->der || w->der->color == false)) {
                w->color = true;
                x = padre;
            } else {
                if (!w->der || w->der->color == false) {
                    if (w->izq) w->izq->color = false;
                    w->color = true;
                    rotacionDerecha(w);
                    w = padre->der;
                }
                w->color = padre->color;
                padre->color = false;
                if (w->der) w->der->color = false;
                rotacionIzquierda(padre);
                x = raiz;
            }
        } else {
            nodo* w = padre->izq;
            if (!w) break;

            if (w->color == true) {
                w->color = false;
                padre->color = true;
                rotacionDerecha(padre);
                w = padre->izq;
            }

            if ((!w->der || w->der->color == false) &&
                (!w->izq || w->izq->color == false)) {
                w->color = true;
                x = padre;
            } else {
                if (!w->izq || w->izq->color == false) {
                    if (w->der) w->der->color = false;
                    w->color = true;
                    rotacionIzquierda(w);
                    w = padre->izq;
                }
                w->color = padre->color;
                padre->color = false;
                if (w->izq) w->izq->color = false;
                rotacionDerecha(padre);
                x = raiz;
            }
        }
    }
    if (x) x->color = false;
}

// FUNCIONES AUXILIARES
void ArbolRojiNegro::trasplantar(nodo* u, nodo* v) {
    nodo* padreU = buscarPadre(u);
    if (padreU == nullptr) {
        raiz = v;
    } else if (u == padreU->izq) {
        padreU->izq = v;
    } else {
        padreU->der = v;
    }
}

nodo* ArbolRojiNegro::minimo(nodo* node) const {
    while (node && node->izq != nullptr) {
        node = node->izq;
    }
    return node;
}

nodo* ArbolRojiNegro::buscarNodo(int clave) const {
    nodo* actual = raiz;
    while (actual != nullptr) {
        if (clave == actual->clave) {
            return actual;
        } else if (clave < actual->clave) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    return nullptr;
}

nodo* ArbolRojiNegro::buscarPadre(nodo* hijo) const {
    if (hijo == raiz || hijo == nullptr) return nullptr;

    nodo* actual = raiz;
    while (actual != nullptr) {
        if ((actual->izq == hijo) || (actual->der == hijo)) {
            return actual;
        }
        if (hijo->clave < actual->clave) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    return nullptr;
}

// BUSQUEDA Y MODIFICACION
string ArbolRojiNegro::buscar(int clave) {
    nodo* node = buscarNodo(clave);
    if (node != nullptr) {
        return node->informacion;
    }
    return "";
}

bool ArbolRojiNegro::modificar(int clave, const string& nuevaInformacion) {
    nodo* node = buscarNodo(clave);
    if (node != nullptr) {
        node->informacion = nuevaInformacion;
        return true;
    }
    return false;
}

// RECORRIDOS ITERATIVOS
queue<pair<int, string>> ArbolRojiNegro::recorridoInorden() {
    queue<pair<int, string>> resultado;
    stack<nodo*> pila;
    nodo* actual = raiz;

    while (actual != nullptr || !pila.empty()) {
        while (actual != nullptr) {
            pila.push(actual);
            actual = actual->izq;
        }

        actual = pila.top();
        pila.pop();

        resultado.push(make_pair(actual->clave, actual->informacion));
        actual = actual->der;
    }

    return resultado;
}

queue<pair<int, string>> ArbolRojiNegro::recorridoPreorden() {
    queue<pair<int, string>> resultado;
    if (raiz == nullptr) return resultado;

    stack<nodo*> pila;
    pila.push(raiz);

    while (!pila.empty()) {
        nodo* actual = pila.top();
        pila.pop();

        resultado.push(make_pair(actual->clave, actual->informacion));

        if (actual->der != nullptr) {
            pila.push(actual->der);
        }
        if (actual->izq != nullptr) {
            pila.push(actual->izq);
        }
    }

    return resultado;
}

queue<pair<int, string>> ArbolRojiNegro::recorridoPosorden() {
    queue<pair<int, string>> resultado;
    if (raiz == nullptr) return resultado;

    stack<nodo*> pila1, pila2;
    pila1.push(raiz);

    while (!pila1.empty()) {
        nodo* actual = pila1.top();
        pila1.pop();
        pila2.push(actual);

        if (actual->izq != nullptr) {
            pila1.push(actual->izq);
        }
        if (actual->der != nullptr) {
            pila1.push(actual->der);
        }
    }

    while (!pila2.empty()) {
        nodo* actual = pila2.top();
        pila2.pop();
        resultado.push(make_pair(actual->clave, actual->informacion));
    }

    return resultado;
}

queue<pair<int, string>> ArbolRojiNegro::recorridoPorNiveles() {
    queue<pair<int, string>> resultado;
    if (raiz == nullptr) return resultado;

    queue<nodo*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        nodo* actual = cola.front();
        cola.pop();

        resultado.push(make_pair(actual->clave, actual->informacion));

        if (actual->izq != nullptr) {
            cola.push(actual->izq);
        }
        if (actual->der != nullptr) {
            cola.push(actual->der);
        }
    }

    return resultado;
}

// MOSTRAR ARBOL
void ArbolRojiNegro::mostrarArbol() {
    cout << "\nEstructura del arbol (R=Rojo, N=Negro):" << endl;
    mostrarArbolHelper(raiz, 0);
}

void ArbolRojiNegro::mostrarArbolHelper(nodo* node, int nivel) const {
    if (node == nullptr) return;

    mostrarArbolHelper(node->der, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }
    cout << node->clave << "(" << (node->color ? "R" : "N") << ")" << endl;

    mostrarArbolHelper(node->izq, nivel + 1);
}

#endif // ARBOL_ROJINEGRO_H