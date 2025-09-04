#ifndef PILA1_H
#define PILA1_H
#include "estructura1.h"



class pila{nodo *cab;
public: pila(){cab= new nodo;
    cab->dato=' ';
    cab->sig=NULL;}
    void Push( char v);
    char Pop();
    bool PilaVacia();
    ~pila();
};

void pila::Push(char v){
    nodo *t = new nodo;
    t->dato=v;
    t->sig=cab->sig;
    cab->sig= t;
}

char pila::Pop(){
    char x;
    nodo *t= cab->sig;
    cab->sig= t->sig;
    x=t->dato;
    delete t;
    return x;
}

bool pila::PilaVacia(){
    return cab->sig== NULL;
}

pila::~pila(){
    nodo *t=cab;
    while (t!=NULL){
        cab=t;
        t=t->sig;
        delete cab;
    }
}


#endif
