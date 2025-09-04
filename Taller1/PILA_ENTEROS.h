#ifndef PILA_ENTEROS_H
#define PILA_ENTEROS_H

#include <stdexcept>

// Estructura de nodo para la pila
struct Nodo {
    int dato;
    Nodo* sig;

    // Constructor para facilitar la creación de nodos
    Nodo(int valor, Nodo* siguiente = nullptr) : dato(valor), sig(siguiente) {}
};

class PilaEnteros {
private:
    Nodo* tope;  // Puntero al tope de la pila
    int tamanoActual;  // Contador para el número de elementos

public:
    // Constructor y destructor
    PilaEnteros();
    ~PilaEnteros();

    // Métodos básicos de la pila
    void push(int elemento);
    int pop();
    int top() const;
    bool estaVacia() const;
    int tamano() const;

    // Evitar copia de la pila
    PilaEnteros(const PilaEnteros&) = delete;
    PilaEnteros& operator=(const PilaEnteros&) = delete;
};

// Implementación inline de los métodos

inline PilaEnteros::PilaEnteros() : tope(nullptr), tamanoActual(0) {
}

inline PilaEnteros::~PilaEnteros() {
    while (!estaVacia()) {
        pop();
    }
}

inline void PilaEnteros::push(int elemento) {
    Nodo* nuevo = new Nodo(elemento, tope);
    tope = nuevo;
    tamanoActual++;
}

inline int PilaEnteros::pop() {
    if (estaVacia()) {
        throw std::runtime_error("Error: La pila está vacía");
    }

    int valor = tope->dato;
    Nodo* temp = tope;
    tope = tope->sig;
    delete temp;
    tamanoActual--;

    return valor;
}

inline int PilaEnteros::top() const {
    if (estaVacia()) {
        throw std::runtime_error("Error: La pila está vacía");
    }
    return tope->dato;
}

inline bool PilaEnteros::estaVacia() const {
    return tope == nullptr;
}

inline int PilaEnteros::tamano() const {
    return tamanoActual;
}


#endif // PILA_ENTEROS_H