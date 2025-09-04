#include <bits/stdc++.h>
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


void ordenShell(int a[], int N) {
    int i, j, h;
    int v;


    for (h = 1; h <= N / 9; h = 3 * h + 1);

    for (; h > 0; h /= 3) {
        for (i = h; i < N; i++) {
            v = a[i];
            j = i;

            while (j >= h && a[j - h] > v) {
                a[j] = a[j - h];
                j -= h;
            }
            a[j] = v;
        }
    }
}

// Llenar vector con valores aleatorios
void fillRandom(vector<int>& v) {
    for (int& x : v)
        x = rand();
}

int main() {
    srand(time(NULL));

    for (int n = 100; n <= 1000; n += 10) {
        vector<int> arr(n);
        fillRandom(arr);

        int* rawArr = arr.data();  // Pasar el arreglo al estilo C

        startCounter();
        ordenShell(rawArr, n);
        double elapsed = getCounter();

        cout << "Tiempo de ordenacion con " << n
             << " elementos: " << fixed << setprecision(4) << elapsed << " ms" << endl;
    }

    return 0;
}