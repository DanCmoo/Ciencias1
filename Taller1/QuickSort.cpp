#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

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

int partition(int *arr, int low, int high) {
    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j <= high-1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }


    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(int *arr, int low, int high) {
    if (low < high) {


        int pi = partition(arr, low, high);


        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void iniciarArreglo(int *arr,int n) {
    for(int i = 0 ; i<n ; i++){
        arr[i] = n-i-1;
    }
}

int main() {
    for(int n = 10 ; n<=500;n+=10) {
        int *arr = new int[n];
        iniciarArreglo(arr,n);
        startCounter();
        quickSort(arr, 0, n - 1);
        cout << getCounter()<< endl;

    }

    return 0;
}
