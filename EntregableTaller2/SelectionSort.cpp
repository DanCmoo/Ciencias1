#include <bits/stdc++.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;  // Frecuencia en milisegundos

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;  // Devuelve tiempo en milisegundos
}

void seleccion(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

void imprimir(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void llenar(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = std::rand() % 100;
    }
}


int main() {
    for (int n=10; n<=500; n+=10){

        vector<int> arr(n);

        llenar(arr, n);
        imprimir(arr);

        // Medir el tiempo de ordenación (Seleccion)
        StartCounter();
        seleccion(arr);
        cout << "Tiempo de ordenacion (Seleccion) con  " << n << ": "<<GetCounter() << " ms." << endl;
    }
    return 0;
}