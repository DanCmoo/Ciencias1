#include <windows.h>
#include <iostream>
#include <math.h>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter() {
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.00000;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


inline unsigned int bits(int x, int k, int j) {
    return (x>>k)&~(~0<<j);
}
void cambiarResiduos(int a[], int izq, int der, int b) {

    int i,j;

    if(der>izq && b>0) {

        i = izq;
        j = der;

        while(j!=i) {

            while(!bits(a[i],b,1) && i<j)i++;
            while(bits(a[j],b,1) && j>i)j--;
            swap(a[i],a[j]);
        }

        if(bits(a[i],b,1)) {
            cambiarResiduos(a,izq,j-1,b-1);
            cambiarResiduos(a,j,der,b-1);
        }
    }
}

void printArray(int arr[], int n){
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void iniciarArreglo(int *arr,int n) {
    for(int i = 0 ; i<n ; i++){
        arr[i] = n-i-1;
    }
}

int main() {

    for(int i = 10;i<=500;i+=10) {
        int *arr = new int[i];
        iniciarArreglo(arr,i);
        StartCounter();
        cambiarResiduos(arr,0,i-1,log2(i-1));
        cout << GetCounter() << endl;

    }
    return 0;
}