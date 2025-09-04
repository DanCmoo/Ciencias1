#include <iostream>
#include <windows.h>
#include <cstdlib>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

void insertionSort(int arr[], int n){
    for (int i = 1; i < n; ++i) {

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n){
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}
void iniciarArreglo(int *arr,int n) {
    srand(time(0));
    for(int i = 0 ; i<n ; i++){
        arr[i] = rand();
    }
}



int main(){
    for(int n = 10 ; n<=500 ;n+=10) {
        int *arr = new int[n];
        iniciarArreglo(arr,n);

        StartCounter();
        insertionSort(arr,n);
        cout << GetCounter()<< endl;
    }
    return 0;
}