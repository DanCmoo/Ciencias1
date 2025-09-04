#include <iostream>
#include <windows.h>
using namespace std;

// Variables para medir el tiempo
double PCFreq = 0.0;
__int64 CounterStart = 0;

void startCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double getCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
}

void radixsort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    const int TAM_MAX = 1024;
    int arreglo[TAM_MAX];

    // Llenar el arreglo desde 1023 hacia atrás
    for (int i = 0; i < TAM_MAX; i++) {
        arreglo[i] = 1023 - i;
    }

    // Ejecutar para n de 10 en 10 hasta 500
    for (int n = 10; n <= 500; n += 10) {
        int* subArr = new int[n];
        for (int i = 0; i < n; i++) {
            subArr[i] = arreglo[i];
        }

        startCounter();
        radixsort(subArr, n);
        double elapsed = getCounter();

        cout << "n = " << n << ", tiempo (ms): " << elapsed << endl;
      

        delete[] subArr;
    }

    return 0;
}