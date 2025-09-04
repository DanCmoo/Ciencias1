#ifndef LISTA_H
#define LISTA_H

template<class T, class S> struct nodo {
    T dato1;
    S dato2;
    nodo<T, S> *sig;
};

template<class T, class S> class Lista {
private:
    int numElementos;
    nodo<T, S> *cab;

public:
    Lista() {
        numElementos = 0;
        cab = NULL;
    }

    ~Lista() {
        while (!listaVacia()) {
            borrar(0);
        }
    }

    bool listaVacia() {
        return cab == NULL;
    }

    void insertarInicio(T info1, S info2);
    nodo<T,S>* buscar(int pos);
    void insertarFinal(T info1, S info2);
    void insertar(T info1, S info2, int pos);
    bool borrar(int pos);
    bool modificar(T info1, S info2, int pos);
    int getNumElementos() { return numElementos; }
};

template<class T, class S> void Lista<T, S>::insertarInicio(T info1, S info2) {
    nodo<T, S> *nuevo = new nodo<T, S>;

    nuevo->dato1 = info1;
    nuevo->dato2 = info2;
    nuevo->sig = NULL;

    nuevo->sig = cab;
    cab = nuevo;

    numElementos++;
}
template<class T, class S> nodo<T, S>* Lista<T, S>::buscar(int pos) {
    if (pos < 0 || pos >= numElementos || listaVacia()) {
        return NULL; // Posicion invalida o lista vacia
    }

    nodo<T, S> *aux = cab;
    for (int i = 0; i < pos; i++) {
        aux = aux->sig;
    }

    return aux;
}

template<class T, class S> void Lista<T, S>::insertarFinal(T info1, S info2) {
    nodo<T, S> *nuevo = new nodo<T, S>;

    nuevo->dato1 = info1;
    nuevo->dato2 = info2;
    nuevo->sig = NULL;

    if (cab == NULL) {
        cab = nuevo;
    } else {
        nodo<T, S> *aux = cab;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    numElementos++;
}

template<class T, class S> void Lista<T, S>::insertar(T info1, S info2, int pos) {
    if (pos < 0 || pos > numElementos) {
        return; // Posicion invalida
    }

    if (pos == 0) {
        insertarInicio(info1, info2);
        return;
    }

    if (pos == numElementos) {
        insertarFinal(info1, info2);
        return;
    }

    nodo<T, S> *nuevo = new nodo<T, S>;
    nuevo->dato1 = info1;
    nuevo->dato2 = info2;
    nuevo->sig = NULL;

    nodo<T, S> *aux = buscar(pos);

    nuevo->sig = aux->sig;
    aux->sig = nuevo;

    numElementos++;
}

template<class T, class S> bool Lista<T, S>::borrar(int pos) {
    if (pos < 0 || pos >= numElementos || listaVacia()) {
        return false; // Posición inválida o lista vacía
    }

    nodo<T, S> *aux = cab;

    if (pos == 0) {
        cab = cab->sig;
        delete aux;
        numElementos--;
        return true;
    }

    nodo<T, S> *ant = NULL;
    for (int i = 0; i < pos; i++) {
        ant = aux;
        aux = aux->sig;
    }

    ant->sig = aux->sig;
    delete aux;
    numElementos--;

    return true;
}

template<class T, class S> bool Lista<T, S>::modificar(T info1, S info2, int pos) {
    if (pos < 0 || pos >= numElementos || listaVacia()) {
        return false; // Posición inválida o lista vacía
    }

    nodo<T, S> *aux = cab;
    for (int i = 0; i < pos; i++) {
        aux = aux->sig;
    }

    aux->dato1 = info1;
    aux->dato2 = info2;

    return true;
}

#endif //LISTA_H
