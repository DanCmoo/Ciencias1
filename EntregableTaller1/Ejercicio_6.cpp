#include <iostream>
using namespace std;

struct nodo {
    int a;
    float b;
};

int main() {
    cout << "Calculando memoria para N de 10 a 500 en pasos de 10...\n";

    for (int N = 10; N <= 500; N += 10) {
        int size = 0; // Inicializamos el tamaño total de memoria utilizada
        nodo **a;
        int i,j;
        size += sizeof(N); // Entero N
        // Asignar memoria para el arreglo de punteros
        a = new nodo *[N];
        size += sizeof(a); // Tamaño del puntero al arreglo de punteros
        size += sizeof(*a) * N; // Tamaño del arreglo de punteros

        for (i = 0; i < N; i++) {
            // Asignar memoria para cada fila
            a[i] = new nodo[N];
            size += sizeof(*a[i]) * N; // Tamaño del nodo almacenado
        }
        size += sizeof(i); // Entero i
        size += sizeof(j); // Entero j
        // Inicializar valores
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                a[i][j].a = j * i;
                a[i][j].b = j + i;
            }
        }

        // Liberar memoria correctamente
        for (i = 0; i < N; i++) {
            delete[] a[i];
        }
        delete[] a;

        // Imprimir la memoria total utilizada para el valor de N actual
        cout << "N = " << N << " -> Memoria: " << size << " bytes" << endl;
    }
    return 0;
}