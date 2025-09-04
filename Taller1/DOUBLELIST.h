#ifndef DOUBLELIST_H
#define DOUBLELIST_H
    // Daniel Camacho Juliana Puerto
#include <string>
using namespace std;

template<class T> struct nodo{
    T ID;
    string info;
    nodo<T> *prev, *next;
};

template<class T> class DoubleList{
    private:
        nodo<T> *head;
        int size;
    public:
        DoubleList(){
            head = new nodo<T>;
            head->next = head;
            head->prev = head;
            size = 0;
        }

        bool insert(T ID, string info);
        bool erase(T ID);
        bool empty();
        bool modify(T ID, string info);

        nodo<T> *getHead();

        nodo<T> *find(T ID);
        int getSize(){
            return size;
        }
        ~DoubleList();
};

template<class T>
nodo<T>* DoubleList<T>::getHead() {
    return head;
}

template<class T>
nodo<T>* DoubleList<T>::find(T ID){
    if(size == 0){
        return head;
    }
    nodo<T> *aux = head->next;
    while(aux != head){
        if(aux->ID == ID){
            return aux; // Encontrado
        }
        if(aux->ID > ID){
            return head; // No encontrado (pasamos el punto donde debería estar)
        }
        aux = aux->next;
    }
    return head; // No encontrado después de recorrer toda la lista
}

template<class T>
bool DoubleList<T>::insert(T ID, string info){
    // Verificar si el ID ya existe
    nodo<T> *found = find(ID);
    if(found != head && found->ID == ID){
        return false; // ID ya existe
    }

    // Crear nuevo nodo
    nodo<T> *newNode = new nodo<T>;
    newNode->ID = ID;
    newNode->info = info;

    // Encontrar posición para insertar (ordenado por ID)
    nodo<T> *current = head->next;
    while(current != head && current->ID < ID){
        current = current->next;
    }

    // Insertar antes de current
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;

    size++;
    return true;
}

template<class T>
bool DoubleList<T>::erase(T ID){
    nodo<T> *nodeToDelete = find(ID);
    if(nodeToDelete == head || nodeToDelete->ID != ID){
        return false; // Nodo no encontrado
    }

    // Actualizar enlaces
    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;

    // Liberar memoria
    delete nodeToDelete;

    size--;
    return true;
}

template<class T>
bool DoubleList<T>::empty(){
    return (size == 0);
}

template<class T>
bool DoubleList<T>::modify(T ID, string info){
    nodo<T> *nodeToModify = find(ID);
    if(nodeToModify == head || nodeToModify->ID != ID){
        return false; // Nodo no encontrado
    }

    nodeToModify->info = info;
    return true;
}

template<class T>
DoubleList<T>::~DoubleList(){
    // Eliminar todos los nodos excepto head
    nodo<T> *current = head->next;
    while(current != head){
        nodo<T> *temp = current;
        current = current->next;
        delete temp;
    }

    // Eliminar head
    delete head;
}

#endif //DOUBLELIST_H