#ifndef LISTA_H
#define LISTA_H

// Estructura de nodo simplificada
template<class T>
struct nodo {
    T dato;
    nodo<T> *sig;

    // Constructor por defecto
    nodo() : dato(T()), sig(nullptr) {}

    // Constructor con parámetros
    nodo(T d) : dato(d), sig(nullptr) {}
};

template<class T>
class Lista {
private:
    int numElementos;
    nodo<T> *cab;

public:
    // Constructor
    Lista() : numElementos(0), cab(nullptr) {}

    // Destructor
    ~Lista() {
        while (!listaVacia()) {
            borrar(0);
        }
    }

    // Métodos básicos
    bool listaVacia() {
        return cab == nullptr;
    }

    int getNumElementos() {
        return numElementos;
    }

    // Buscar nodo por posición
    nodo<T>* buscar(int pos);

    // Inserción básica
    void insertarInicio(T info);
    void insertarFinal(T info);
    void insertar(T info, int pos);

    // Eliminación
    bool borrar(int pos);

    // Modificación
    bool modificar(T info, int pos);
};

// Implementación de métodos

template<class T>
nodo<T>* Lista<T>::buscar(int pos) {
    if (pos < 0 || pos >= numElementos || listaVacia()) {
        return nullptr;
    }

    nodo<T> *aux = cab;
    for (int i = 0; i < pos; i++) {
        aux = aux->sig;
    }

    return aux;
}

template<class T>
void Lista<T>::insertarInicio(T info) {
    nodo<T> *nuevo = new nodo<T>(info);
    nuevo->sig = cab;
    cab = nuevo;
    numElementos++;
}

template<class T>
void Lista<T>::insertarFinal(T info) {
    nodo<T> *nuevo = new nodo<T>(info);

    if (cab == nullptr) {
        cab = nuevo;
    } else {
        nodo<T> *aux = cab;
        while (aux->sig != nullptr) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    numElementos++;
}

template<class T>
void Lista<T>::insertar(T info, int pos) {
    if (pos < 0 || pos > numElementos) {
        return;
    }

    if (pos == 0) {
        insertarInicio(info);
        return;
    }

    if (pos == numElementos) {
        insertarFinal(info);
        return;
    }

    nodo<T> *nuevo = new nodo<T>(info);
    nodo<T> *aux = buscar(pos - 1);

    nuevo->sig = aux->sig;
    aux->sig = nuevo;
    numElementos++;
}

template<class T>
bool Lista<T>::borrar(int pos) {
    if (pos < 0 || pos >= numElementos || listaVacia()) {
        return false;
    }

    nodo<T> *aux = cab;

    if (pos == 0) {
        cab = cab->sig;
        delete aux;
        numElementos--;
        return true;
    }

    nodo<T> *ant = nullptr;
    for (int i = 0; i < pos; i++) {
        ant = aux;
        aux = aux->sig;
    }

    ant->sig = aux->sig;
    delete aux;
    numElementos--;

    return true;
}

template<class T>
bool Lista<T>::modificar(T info, int pos) {
    if (pos < 0 || pos >= numElementos || listaVacia()) {
        return false;
    }

    nodo<T> *aux = buscar(pos);
    if (aux != nullptr) {
        aux->dato = info;
        return true;
    }
    return false;
}

#endif //LISTA_H