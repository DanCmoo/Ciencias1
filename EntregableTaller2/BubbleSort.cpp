#include <bits/stdc++.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void startCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;  // Frecuencia en milisegundos

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;  // Devuelve tiempo en milisegundos
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }


        if (!swapped)
            break;
    }
}

void print(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void fill(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = std::rand() % 100;
    }
}


int main() {
    for (int n=10; n<=500; n+=10){

        vector<int> arr(n);
        fill(arr, n);
        print(arr);

        // Medir el tiempo de ordenación (Burbuja)
        startCounter();
        bubbleSort(arr);
        cout << "Tiempo de ordenacion (Burbuja) con  " << n << ": "<<getCounter() << " ms." << endl;
    }
    return 0;
}