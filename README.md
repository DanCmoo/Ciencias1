# Ciencias de la Computación 1 - Algoritmos y Estructuras de Datos

Este repositorio contiene implementaciones de diversos algoritmos de ordenamiento, búsqueda y estructuras de datos desarrollados para la materia **Ciencias de la Computación 1**. El proyecto incluye implementaciones completas de algoritmos fundamentales y estructuras de datos avanzadas como listas enlazadas dobles, multilistas, pilas, colas, árboles binarios y árboles roji-negro, con planes de expansión hacia árboles AVL y árboles B/B+.

Todas las implementaciones están escritas en C++ y están organizadas por talleres y entregas académicas.

## 📚 Contenido del Repositorio

### 🔄 Algoritmos de Ordenamiento

- **Bubble Sort** - Algoritmo de ordenamiento burbuja
  - `EntregableTaller2/BubbleSort.cpp`
  - `Taller1/BubbleSort.cpp`

- **Insertion Sort** - Algoritmo de ordenamiento por inserción
  - `EntregableTaller2/InsertionSort.cpp`
  - `Taller1/InsertionSort.cpp`

- **Selection Sort** - Algoritmo de ordenamiento por selección
  - `EntregableTaller2/SelectionSort.cpp`
  - `Taller1/SelectionSort.cpp`

- **Shell Sort** - Algoritmo de ordenamiento Shell
  - `EntregableTaller3/ShellSort.cpp`
  - `Taller1/ShellSort.cpp`

- **Quick Sort** - Algoritmo de ordenamiento rápido
  - `EntregableTaller5/QuickSort.cpp`
  - `Taller1/QuickSort.cpp`

- **Merge Sort** - Algoritmo de ordenamiento por mezcla
  - `EntregableTaller5/MergeSort.cpp`
  - `Taller1/MergeSort.cpp`

### 🔍 Algoritmos de Búsqueda

- **Binary Search** - Búsqueda binaria
  - `EntregableTaller3/BinarySearch.cpp`
  - `Taller1/BinarySearch.cpp`

### 🗃️ Estructuras de Datos

#### Listas Enlazadas
- **Lista Enlazada Simple**
  - `TallerLibreria/ListaEnlazada.cpp`
  - `TallerLibreria/LISTA.h`
  - `Taller1/ListaEnlazada.cpp`
  - `Taller1/LISTA.h`

- **Lista Doblemente Enlazada Circular Ordenada**
  - `ListaDoblementeEnlazadaCircularOrdenada/DoubleList.cpp`
  - `ListaDoblementeEnlazadaCircularOrdenada/DOUBLELIST.h`
  - `Taller1/DoubleList.cpp`
  - `Taller1/DOUBLELIST.h`

#### Multilistas
- **Multilista de Personas**
  - `TallerMultilistas/MultilistaPersonas.cpp`
  - `TallerMultilistas/MULTILISTA.h`
  - `Taller1/MultilistaPersonas.cpp`
  - `Taller1/MULTILISTA.h`

#### Pilas y Colas
- **Pilas (Stacks)**
  - `TallerPilasColas/EjercicioPilas.cpp`
  - `TallerPilasColas/pila1.h`
  - `TallerPilasColas/PILA_ENTEROS.h`
  - `Taller1/EjercicioPilas.cpp`
  - `Taller1/PILA_ENTEROS.h`

- **Colas (Queues)**
  - `TallerPilasColas/cola1.h`
  - `TallerPilasColas/main.cpp`

#### Árboles
- **Árboles Binarios Ordenados**
  - `Taller1/ArbolBinarioOrdenado.cpp`
  - `Taller1/ARBOLBINARIOORDENADO.h`

- **Árboles Roji-Negro (Red-Black Trees)**
  - `Taller1/Rojinegro.cpp`
  - `Taller1/RedBlackTree.h`

> **Nota**: Las implementaciones de Árboles AVL y Árboles B/B+ están planificadas para futuras entregas del curso.

## 📁 Estructura del Repositorio

```
Ciencias1/
├── EntregableTaller1/          # Ejercicios básicos
├── EntregableTaller2/          # Algoritmos de ordenamiento básicos
├── EntregableTaller3/          # Shell Sort y Binary Search
├── EntregableTaller5/          # Algoritmos de ordenamiento avanzados
├── TallerLibreria/             # Implementación de listas enlazadas
├── TallerMultilistas/          # Implementación de multilistas
├── TallerPilasColas/          # Implementación de pilas y colas
├── ListaDoblementeEnlazadaCircularOrdenada/  # Listas dobles
├── Taller1/                   # Colección completa de implementaciones
├── ProyectoFinal-CC1/         # Proyecto final
└── *.rar                      # Archivos comprimidos de entregas
```

## 🚀 Compilación y Ejecución

### Requisitos
- Compilador C++ (g++, clang++, etc.)
- Estándar C++11 o superior
- **Nota importante**: Algunos archivos requieren Windows debido al uso de `windows.h` para medición de tiempo

### Compilación Individual

#### En Windows:
```bash
g++ -o programa archivo.cpp
```

#### En Linux/macOS:
Para archivos que usan `windows.h`, será necesario modificar o comentar las secciones de medición de tiempo que dependen de Windows.

Ejemplo:
```bash
g++ -o bubblesort EntregableTaller2/BubbleSort.cpp
./bubblesort
```

### Uso de CMake (para Taller1)
El directorio `Taller1` incluye un archivo `CMakeLists.txt` para facilitar la compilación:

```bash
cd Taller1
mkdir build
cd build
cmake ..
make
```

## 📖 Descripción de Algoritmos

### Algoritmos de Ordenamiento

- **Bubble Sort**: O(n²) - Compara elementos adyacentes y los intercambia si están en orden incorrecto
- **Insertion Sort**: O(n²) - Construye el array ordenado insertando elementos uno a la vez
- **Selection Sort**: O(n²) - Selecciona repetidamente el elemento mínimo y lo coloca en su posición
- **Shell Sort**: O(n log n) a O(n²) - Mejora del insertion sort usando gaps decrecientes
- **Quick Sort**: O(n log n) promedio - Divide y vencerás usando un elemento pivote
- **Merge Sort**: O(n log n) - Divide el array y luego merge las partes ordenadas

### Estructuras de Datos

- **Listas Enlazadas**: Estructura lineal con nodos enlazados dinámicamente
- **Listas Dobles**: Nodos con enlaces bidireccionales para navegación eficiente
- **Multilistas**: Estructura que permite múltiples organizaciones de los mismos datos
- **Pilas**: LIFO (Last In, First Out) - push, pop, top
- **Colas**: FIFO (First In, First Out) - enqueue, dequeue, front
- **Árboles Binarios**: Estructura jerárquica con máximo dos hijos por nodo
- **Árboles Roji-Negro**: Árbol binario balanceado con propiedades de coloreo

## 👥 Autores

- **Daniel Esteban Camacho Ospina** - 20231020046
- **Erika Juliana Puerto Corchuelo** - 20232020136

## 📝 Datos de Prueba

El repositorio incluye archivos de datos de prueba:
- `estudiantes.txt` - Datos de estudiantes para las multilistas
- Varios archivos de Excel con especificaciones de talleres

## 📄 Licencia

Este proyecto está licenciado bajo la GNU General Public License v3.0 - ver el archivo [LICENSE](LICENSE) para más detalles.

## 🎯 Propósito Académico

Este repositorio fue desarrollado como parte del curso **Ciencias de la Computación 1** y tiene propósitos educativos. Las implementaciones cubren conceptos fundamentales de:

- Análisis de algoritmos y complejidad computacional
- Estructuras de datos dinámicas
- Técnicas de ordenamiento y búsqueda
- Programación orientada a objetos en C++
- Manejo de memoria dinámica

## 🔧 Notas Técnicas

- Todas las implementaciones incluyen medición de tiempos de ejecución
- **Dependencia de Windows**: Muchos archivos utilizan `windows.h` para funciones de alto rendimiento de medición de tiempo (`QueryPerformanceCounter`)
- Las estructuras de datos implementan destructores para manejo adecuado de memoria
- Se incluyen plantillas (templates) para reutilización de código
- Los algoritmos están optimizados para datos de prueba específicos del curso
- Manejo de memoria dinámica con `new` y `delete`

## 💡 Ejemplos de Uso

### Ejemplo de Lista Enlazada
```cpp
#include "LISTA.h"

Lista<string, int> lista;
lista.insertar("Juan", 25, 0);
lista.insertar("María", 30, 1);
lista.mostrar();
```

### Ejemplo de Árbol Binario
```cpp
#include "ARBOLBINARIOORDENADO.h"

ArbolBinarioOrdenado arbol;
arbol.insertar(50, "Nodo raíz");
arbol.insertar(30, "Hijo izquierdo");
arbol.insertar(70, "Hijo derecho");
arbol.mostrarInorden();
```

### Ejemplo de Multilista
```cpp
#include "MULTILISTA.h"

MultiLista multilista;
multilista.cargarDesdeArchivo("estudiantes.txt");
multilista.mostrarPorCarrera("Ingeniería");
multilista.mostrarPorActividad("Deportes");
```

## 📞 Contacto

Para preguntas o comentarios sobre las implementaciones, contactar a los autores a través de sus códigos estudiantiles mencionados arriba.