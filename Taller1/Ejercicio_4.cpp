#include <iostream>

using namespace std;

struct nodo {
    int x,y;
    nodo *sig;
};

int main(int argc, char** argv) {
    int *tamanos = new int[50];
    for(int contador = 0;contador<50;contador++) {
        nodo **arr, *Aux;
        int size = 0;
        int M, tam, j, i;
        size+= sizeof(Aux); // Direccion del nodo auxiliar
        M = (contador+1)*10;
        size+= sizeof(M); // Entero m

        tam = M;
        size+= sizeof(tam); // Entero tam

        arr= new nodo *[M];
        size+= sizeof(arr); // Puntero del arreglo de punteros
        size+= M * sizeof(*arr); // Punteros contenidos en el arreglo
        for(i=0; i<M; i++) {
            arr[i]=NULL;
        }
        size+= sizeof(i); // Entero i

        for(i=0; i<M; i++){
            for(j=1; j<=tam; j++){
                Aux = new nodo;
                Aux->x=j;
                Aux->y=M+j*i;
                Aux->sig = arr[i];
                arr[i]= Aux;
                size+= sizeof(*arr[i]); // Nodo almacenado
            }
        }
        size+= sizeof(j); // Entero j

        for(i=0; i<M; i++){
            for(Aux=arr[i]->sig; Aux!=NULL; Aux=Aux->sig){
                delete arr[i];
                arr[i]=Aux;
            }
            delete arr[i];
        }
        delete []arr;
        tamanos[contador] = size;
    }
    for (int i = 0; i < 50; ++i) {
        cout<<"N = "<<(i+1)*10<<" -> Memoria: " << tamanos[i] << " bytes"<< endl;
    }

    return 0;
}
