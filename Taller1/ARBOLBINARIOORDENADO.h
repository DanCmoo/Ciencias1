//
// Created by Camacho Ospina on 7/06/2025.
//

#ifndef ARBOLBINARIOORDENADO_H
#define ARBOLBINARIOORDENADO_H
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <sstream>

struct Nodo {
    int clave;
    int id;
    int hijoIzquierdo;
    int hijoDerecho;

    Nodo() : clave(0), id(-1), hijoIzquierdo(-1), hijoDerecho(-1) {}
    Nodo(int c, int i) : clave(c), id(i), hijoIzquierdo(-1), hijoDerecho(-1) {}
};

struct ElementoCola {
    int clave;
    std::string informacion;

    ElementoCola(int c, const std::string& info) : clave(c), informacion(info) {}
};

class ArbolBinarioOrdenado {
private:
    Nodo* arreglo;
    int tamaño;
    int raiz;
    int primerLibre;
    std::string nombreArchivo;

    int encontrarPosicionLibre() {
        for (int i = 1; i < tamaño; i++) {
            if (arreglo[i].id == -1) {
                return i;
            }
        }
        return -1; // Arreglo lleno
    }

    void escribirEnArchivo(int id, const std::string& informacion) {
        std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out);
        if (!archivo) {
            archivo.open(nombreArchivo, std::ios::out);
        }

        archivo.seekp(0, std::ios::end);
        long posicion = archivo.tellp();

        // Ir a la posición específica del ID
        archivo.seekp(id * 100); // Cada registro ocupa 100 caracteres
        archivo << informacion;
        for (int i = informacion.length(); i < 99; i++) {
            archivo << " ";
        }
        archivo << "\n";
        archivo.close();
    }

    std::string leerDeArchivo(int id) {
        std::ifstream archivo(nombreArchivo);
        if (!archivo) return "";

        archivo.seekg(id * 100);
        std::string linea;
        std::getline(archivo, linea);
        archivo.close();

        // Remover espacios al final
        size_t fin = linea.find_last_not_of(" \t\n\r");
        if (fin != std::string::npos) {
            linea = linea.substr(0, fin + 1);
        }

        return linea;
    }

    void marcarComoEliminado(int id) {
        escribirEnArchivo(id, "[ELIMINADO]");
    }

    int encontrarMinimo(int nodo) {
        while (arreglo[nodo].hijoIzquierdo != -1) {
            nodo = arreglo[nodo].hijoIzquierdo;
        }
        return nodo;
    }

    int encontrarPadre(int nodo, int padre = -1) {
        if (padre == -1) {
            // Buscar desde la raíz
            if (nodo == raiz) return -1;

            int actual = raiz;
            while (actual != -1) {
                if (arreglo[actual].hijoIzquierdo == nodo || arreglo[actual].hijoDerecho == nodo) {
                    return actual;
                }
                if (arreglo[nodo].clave < arreglo[actual].clave) {
                    actual = arreglo[actual].hijoIzquierdo;
                } else {
                    actual = arreglo[actual].hijoDerecho;
                }
            }
            return -1;
        }
        return padre;
    }

public:
    ArbolBinarioOrdenado(int numElementos) {
        tamaño = numElementos + 1;
        arreglo = new Nodo[tamaño];
        raiz = -1;
        primerLibre = 1;
        nombreArchivo = "datos.txt";

        // Inicializar posición de control
        arreglo[0] = Nodo(-1, -1);

        // Crear archivo si no existe
        std::ofstream archivo(nombreArchivo, std::ios::app);
        archivo.close();
    }

    ~ArbolBinarioOrdenado() {
        delete[] arreglo;
    }

    bool insertar(int clave, const std::string& informacion) {
        int posicion = encontrarPosicionLibre();
        if (posicion == -1) {
            return false; // Arreglo lleno
        }

        // Crear nuevo nodo
        arreglo[posicion] = Nodo(clave, posicion);
        escribirEnArchivo(posicion, informacion);

        // Si es el primer nodo
        if (raiz == -1) {
            raiz = posicion;
            return true;
        }

        // Insertar en el árbol
        int actual = raiz;
        while (true) {
            if (clave < arreglo[actual].clave) {
                if (arreglo[actual].hijoIzquierdo == -1) {
                    arreglo[actual].hijoIzquierdo = posicion;
                    break;
                } else {
                    actual = arreglo[actual].hijoIzquierdo;
                }
            } else {
                if (arreglo[actual].hijoDerecho == -1) {
                    arreglo[actual].hijoDerecho = posicion;
                    break;
                } else {
                    actual = arreglo[actual].hijoDerecho;
                }
            }
        }

        return true;
    }

    std::string buscar(int clave) {
        int actual = raiz;

        while (actual != -1) {
            if (clave == arreglo[actual].clave) {
                return leerDeArchivo(arreglo[actual].id);
            } else if (clave < arreglo[actual].clave) {
                actual = arreglo[actual].hijoIzquierdo;
            } else {
                actual = arreglo[actual].hijoDerecho;
            }
        }

        return ""; // No encontrado
    }

    bool eliminar(int clave) {
        if (raiz == -1) return false;

        int actual = raiz;
        int padre = -1;

        // Buscar el nodo a eliminar
        while (actual != -1 && arreglo[actual].clave != clave) {
            padre = actual;
            if (clave < arreglo[actual].clave) {
                actual = arreglo[actual].hijoIzquierdo;
            } else {
                actual = arreglo[actual].hijoDerecho;
            }
        }

        if (actual == -1) return false; // No encontrado

        // Imprimir información antes de eliminar
        std::string info = leerDeArchivo(arreglo[actual].id);
        std::cout << "Eliminando nodo con clave " << clave << " e información: " << info << std::endl;

        // Marcar como eliminado en archivo
        marcarComoEliminado(arreglo[actual].id);

        // Caso 1: Nodo hoja
        if (arreglo[actual].hijoIzquierdo == -1 && arreglo[actual].hijoDerecho == -1) {
            if (padre == -1) {
                raiz = -1;
            } else if (arreglo[padre].hijoIzquierdo == actual) {
                arreglo[padre].hijoIzquierdo = -1;
            } else {
                arreglo[padre].hijoDerecho = -1;
            }
            arreglo[actual] = Nodo(); // Limpiar nodo
        }
        // Caso 2: Un hijo
        else if (arreglo[actual].hijoIzquierdo == -1 || arreglo[actual].hijoDerecho == -1) {
            int hijo = (arreglo[actual].hijoIzquierdo != -1) ?
                       arreglo[actual].hijoIzquierdo : arreglo[actual].hijoDerecho;

            if (padre == -1) {
                raiz = hijo;
            } else if (arreglo[padre].hijoIzquierdo == actual) {
                arreglo[padre].hijoIzquierdo = hijo;
            } else {
                arreglo[padre].hijoDerecho = hijo;
            }
            arreglo[actual] = Nodo(); // Limpiar nodo
        }
        // Caso 3: Dos hijos
        else {
            int sucesor = encontrarMinimo(arreglo[actual].hijoDerecho);
            int claveSuccesor = arreglo[sucesor].clave;
            int idSuccesor = arreglo[sucesor].id;

            eliminar(claveSuccesor); // Eliminar sucesor recursivamente

            // Reemplazar datos del nodo actual
            arreglo[actual].clave = claveSuccesor;
            arreglo[actual].id = idSuccesor;
        }

        return true;
    }

    std::queue<ElementoCola> recorridoInorden() {
        std::queue<ElementoCola> resultado;
        std::stack<int> pila;
        int actual = raiz;

        while (actual != -1 || !pila.empty()) {
            while (actual != -1) {
                pila.push(actual);
                actual = arreglo[actual].hijoIzquierdo;
            }

            actual = pila.top();
            pila.pop();

            std::string info = leerDeArchivo(arreglo[actual].id);
            resultado.push(ElementoCola(arreglo[actual].clave, info));

            actual = arreglo[actual].hijoDerecho;
        }

        return resultado;
    }

    std::queue<ElementoCola> recorridoPreorden() {
        std::queue<ElementoCola> resultado;
        if (raiz == -1) return resultado;

        std::stack<int> pila;
        pila.push(raiz);

        while (!pila.empty()) {
            int actual = pila.top();
            pila.pop();

            std::string info = leerDeArchivo(arreglo[actual].id);
            resultado.push(ElementoCola(arreglo[actual].clave, info));

            if (arreglo[actual].hijoDerecho != -1) {
                pila.push(arreglo[actual].hijoDerecho);
            }
            if (arreglo[actual].hijoIzquierdo != -1) {
                pila.push(arreglo[actual].hijoIzquierdo);
            }
        }

        return resultado;
    }

    std::queue<ElementoCola> recorridoPosorden() {
        std::queue<ElementoCola> resultado;
        if (raiz == -1) return resultado;

        std::stack<int> pila1, pila2;
        pila1.push(raiz);

        while (!pila1.empty()) {
            int actual = pila1.top();
            pila1.pop();
            pila2.push(actual);

            if (arreglo[actual].hijoIzquierdo != -1) {
                pila1.push(arreglo[actual].hijoIzquierdo);
            }
            if (arreglo[actual].hijoDerecho != -1) {
                pila1.push(arreglo[actual].hijoDerecho);
            }
        }

        while (!pila2.empty()) {
            int actual = pila2.top();
            pila2.pop();

            std::string info = leerDeArchivo(arreglo[actual].id);
            resultado.push(ElementoCola(arreglo[actual].clave, info));
        }

        return resultado;
    }

    std::queue<ElementoCola> recorridoPorNiveles() {
        std::queue<ElementoCola> resultado;
        if (raiz == -1) return resultado;

        std::queue<int> cola;
        cola.push(raiz);

        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();

            std::string info = leerDeArchivo(arreglo[actual].id);
            resultado.push(ElementoCola(arreglo[actual].clave, info));

            if (arreglo[actual].hijoIzquierdo != -1) {
                cola.push(arreglo[actual].hijoIzquierdo);
            }
            if (arreglo[actual].hijoDerecho != -1) {
                cola.push(arreglo[actual].hijoDerecho);
            }
        }

        return resultado;
    }

    void imprimirArreglo() {
        std::cout << "\nEstado del arreglo:" << std::endl;
        for (int i = 0; i < tamaño; i++) {
            std::cout << "Pos " << i << ": ";
            if (arreglo[i].id == -1) {
                std::cout << "[VACIO]";
            } else {
                std::cout << "Clave=" << arreglo[i].clave
                         << ", ID=" << arreglo[i].id
                         << ", HI=" << arreglo[i].hijoIzquierdo
                         << ", HD=" << arreglo[i].hijoDerecho;
            }
            std::cout << std::endl;
        }
    }
};
#endif //ARBOLBINARIOORDENADO_H
