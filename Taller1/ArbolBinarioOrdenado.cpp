#include <iostream>
#include <string>
#include "ArbolBinarioOrdenado.h"

void imprimirRecorrido(std::queue<ElementoCola> cola, const std::string& nombre) {
    std::cout << "\n" << nombre << ":" << std::endl;
    if (cola.empty()) {
        std::cout << "Árbol vacío" << std::endl;
        return;
    }
    
    while (!cola.empty()) {
        ElementoCola elemento = cola.front();
        cola.pop();
        std::cout << "Clave: " << elemento.clave 
                 << ", Información: " << elemento.informacion << std::endl;
    }
}

void imprimirTodosLosRecorridos(ArbolBinarioOrdenado& arbol) {
    std::cout << "\n=== RECORRIDOS DEL ÁRBOL ===" << std::endl;
    imprimirRecorrido(arbol.recorridoInorden(), "RECORRIDO INORDEN");
    imprimirRecorrido(arbol.recorridoPreorden(), "RECORRIDO PREORDEN");
    imprimirRecorrido(arbol.recorridoPosorden(), "RECORRIDO POSORDEN");
    imprimirRecorrido(arbol.recorridoPorNiveles(), "RECORRIDO POR NIVELES");
}

int main() {
    int tamaño;
    std::cout << "Ingrese el número máximo de elementos del árbol: ";
    std::cin >> tamaño;
    
    ArbolBinarioOrdenado arbol(tamaño);
    
    // Fase de inserción
    std::cout << "\n=== FASE DE INSERCIÓN ===" << std::endl;
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int clave;
        std::string informacion;
        
        std::cout << "Ingrese la clave: ";
        std::cin >> clave;
        std::cin.ignore(); // Limpiar buffer
        
        std::cout << "Ingrese la información asociada: ";
        std::getline(std::cin, informacion);
        
        if (arbol.insertar(clave, informacion)) {
            std::cout << "Elemento insertado correctamente." << std::endl;
        } else {
            std::cout << "Error: El árbol está lleno." << std::endl;
        }
        
        std::cout << "¿Desea insertar otro elemento? (s/n): ";
        std::cin >> continuar;
    }
    
    // Imprimir todos los recorridos
    imprimirTodosLosRecorridos(arbol);
    
    // Fase de operaciones
    std::cout << "\n=== FASE DE OPERACIONES ===" << std::endl;
    int opcion;
    do {
        std::cout << "\nOpciones:" << std::endl;
        std::cout << "1. Buscar elemento" << std::endl;
        std::cout << "2. Eliminar elemento" << std::endl;
        std::cout << "3. Mostrar recorridos" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1: {
                int claveBuscar;
                std::cout << "Ingrese la clave a buscar: ";
                std::cin >> claveBuscar;
                
                std::string resultado = arbol.buscar(claveBuscar);
                if (!resultado.empty()) {
                    std::cout << "Información encontrada: " << resultado << std::endl;
                } else {
                    std::cout << "Clave no encontrada." << std::endl;
                }
                break;
            }
            case 2: {
                int claveEliminar;
                std::cout << "Ingrese la clave a eliminar: ";
                std::cin >> claveEliminar;
                
                if (arbol.eliminar(claveEliminar)) {
                    std::cout << "Elemento eliminado correctamente." << std::endl;
                    std::cout << "\nRecorridos después de la eliminación:" << std::endl;
                    imprimirTodosLosRecorridos(arbol);
                } else {
                    std::cout << "Error: Clave no encontrada." << std::endl;
                }
                break;
            }
            case 3: {
                imprimirTodosLosRecorridos(arbol);
                break;
            }
            case 4: {
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            }
            default: {
                std::cout << "Opción inválida." << std::endl;
                break;
            }
        }
    } while (opcion != 4);
    
    return 0;
}