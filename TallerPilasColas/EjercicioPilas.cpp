#include <iostream>
#include "PILA_ENTEROS.h"
// Daniel Camacho - Juliana Puerto
using namespace std;

// Función para combinar dos pilas en una tercera en orden descendente
void combinarPilasOrdenadas(PilaEnteros& pilaAscendente, PilaEnteros& pilaDescendente, PilaEnteros& pilaResultado) {
    if(pilaAscendente.estaVacia()){
        while(!pilaDescendente.estaVacia()) {
            pilaAscendente.push(pilaDescendente.pop());
        }
        while (!pilaAscendente.estaVacia()) {
            pilaResultado.push(pilaAscendente.pop());
        }
    }
    if(pilaDescendente.estaVacia()) {
        while (!pilaAscendente.estaVacia()) {
            pilaResultado.push(pilaAscendente.pop());
        }
    }

    // Comparamos los topes de ambas pilas y tomamos el mayor
    while (!pilaDescendente.estaVacia() || !pilaAscendente.estaVacia()) {
        int descendente = pilaDescendente.pop();

        while(!pilaAscendente.estaVacia()) {
            int ascendente = pilaAscendente.pop();
            if(descendente>=ascendente) {
                pilaResultado.push(ascendente);
                if(pilaAscendente.estaVacia()) {
                    pilaResultado.push(descendente);
                    break;
                }
            }else{
                pilaResultado.push(descendente);
                pilaResultado.push(ascendente);
                break;
            }


        }
        if(pilaDescendente.estaVacia()) {
            while (!pilaAscendente.estaVacia()) {
                pilaResultado.push(pilaAscendente.pop());
            }

            break;
        }
        while (!pilaResultado.estaVacia()) {
            pilaAscendente.push(pilaResultado.pop());
        }





    }
}

int main() {
    PilaEnteros pilaAscendente;
    PilaEnteros pilaDescendente;
    PilaEnteros pilaResultado;




    pilaAscendente.push(5);

    pilaDescendente.push(4);
    pilaDescendente.push(5);
    pilaDescendente.push(6);
    pilaDescendente.push(7);
    pilaDescendente.push(8);
    pilaDescendente.push(9);

    // Combinar las pilas en una tercera pila ordenada descendentemente
    combinarPilasOrdenadas(pilaAscendente, pilaDescendente, pilaResultado);

    std::cout << "\nContenido de la pila resultante:" << std::endl;
    std::cout << "Pila Resultado (descendente desde el tope): ";

    while (!pilaResultado.estaVacia()) {
        std::cout << pilaResultado.pop() << " ";
    }
    std::cout << std::endl;

    return 0;
}