#include <iostream>
using namespace std;

struct nodo {
    int x, y;
    nodo *s;
};

int calcularMemoria(int N) {
    int size = 0; // Inicializamos size
    nodo ***a, *Aux;
    int i,j,k;
    size += sizeof(Aux); // Tamañao de la direccion de memoria del nodo auxiliar
    size += sizeof(N); // Entero N
    a = new nodo **[N];
    size += sizeof(a); // Tamaño de la direccion de memoria del arreglo de punteros
    size += sizeof(*a) * N; // Tamaño del arreglo de punteros dobles

    for (i = 0; i < N; i++) {
        a[i] = new nodo *[N];
        size += sizeof(**a) * N; // Tamaño del arreglo de punteros
        for (int j = 0; j < N; j++)
            a[i][j] = NULL;
    }
    size += sizeof(i); // Entero i
    size += sizeof(j); // Entero j
    size += sizeof(k); // Entero k

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++) {
                Aux = new nodo;
                size += sizeof(*Aux); // Tamaño de cada nodo creado
                Aux->x = j * k;
                Aux->y = i + k;
                Aux->s = a[i][j];
                a[i][j] = Aux;
            }

    // Liberar memoria correctamente
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            Aux = a[i][j];
            while (Aux != NULL) {
                nodo *temp = Aux;
                Aux = Aux->s;
                delete temp;
            }
        }
        delete[] a[i]; // Liberar el arreglo de punteros
    }
    delete[] a;

    return size; // Devuelve el total de memoria usada
}

int main() {
    cout << "Calculando memoria para N de 10 a 500 en pasos de 10...\n";
    for (int N = 10; N <= 500; N += 10) {
        int memoria = calcularMemoria(N);
        cout << "N = " << N << " -> Memoria: " << memoria << " bytes" << endl;
    }

    return 0;
}