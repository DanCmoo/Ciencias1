#include <cstdlib>
#include <iostream>
#include "estructura1.h"

#ifndef COLA1_H
#define COLA1_H

using namespace std;

class cola{nodo *cab,*fin;
public: cola(){cab=fin=NULL;}
  void InsCola(char i);
  char AtenderCola();
  void ImprimirCola();
  bool ColaVacia();
  ~cola();
};

void cola::InsCola(char i){
  nodo *nuevo;
  nuevo= new nodo;
  nuevo->dato=i;
  nuevo->sig= NULL;
  if (cab==NULL)
  {cab=nuevo;}
  else {fin->sig = nuevo;}
  fin=nuevo;
}



char cola::AtenderCola()
{   char x;
  nodo *aux = cab;
  cab=aux->sig;
  x=aux->dato;
  delete aux;
  return x;
}

void cola::ImprimirCola(){
  nodo *aux;
  aux=cab;
  while(aux!=NULL){
    cout<<aux->dato<<" ";
    aux=aux->sig;}
}

bool cola::ColaVacia(){
  return (cab==NULL);
}

cola::~cola(){
  nodo *aux;
  while(cab!=NULL)
  {aux= cab;
    cab=aux->sig;
    delete aux;}
  delete cab;
}

#endif
