#include <windows.h>
#include <iostream>
#include <cstdlib>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.00000;

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

int binarySearch(int arr[], int low, int high, int x){
    while (low <= high) {
        int mid = low + (high - low) / 2;


        if (arr[mid] == x)
            return mid;


        if (arr[mid] < x)
            low = mid + 1;


        else
            high = mid - 1;
    }


    return -1;
}
void iniciarArreglo(int *arr,int n) {
    srand(time(0));
    for(int i = 0 ; i<n ; i++){
        arr[i] = rand();
    }
}

int main(){
    for(int n = 100;n <= 1000;n+=10) {

        int *arr = new int[n];

        iniciarArreglo(arr,n);

        insertionSort(arr,n);
        StartCounter();
        binarySearch(arr,0,n-1,-1);
        cout << GetCounter() << endl;
    }

}