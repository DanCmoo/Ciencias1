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

void merge(int* arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;


    int *L, *R;
    L = new int[n1];
    R = new int[n2];


    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;


    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int left, int right){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
void iniciarArreglo(int *arr,int n) {
    for(int i = 0 ; i<n ; i++){
        arr[i] = n-i-1;
    }
}

int main(){
    for(int i = 10; i<=500 ; i+=10) {

        int *arr = new int[i];
        iniciarArreglo(arr,i);
        startCounter();
        mergeSort(arr, 0, i - 1);
        cout << getCounter() << endl;
    }

    return 0;
}
