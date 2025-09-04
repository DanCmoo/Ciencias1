#ifndef MULTILISTA_H
#define MULTILISTA_H

#include "lista.h"
#include <string>
#include <iostream>
#include <utility>
#include <sstream>
#include <fstream>

using namespace std;

// Estructura para almacenar los datos de una persona
struct Persona {
    string nombre;
    string carrera;
    string actividad;
    int edad;

    Persona() : nombre(""), carrera(""), actividad(""), edad(0) {}
    Persona(string n, string c, string a, int e) : nombre(std::move(n)), carrera(std::move(c)), actividad(std::move(a)), edad(e) {}

    // Operadores para comparación (necesarios para ordenamiento)
    bool operator<(const Persona& otra) const {
        return nombre < otra.nombre;
    }

    bool operator>(const Persona& otra) const {
        return edad > otra.edad; // Para ordenar por edad de mayor a menor
    }

    // Operador de igualdad
    bool operator==(const Persona& otra) const {
        return nombre == otra.nombre && carrera == otra.carrera &&
               actividad == otra.actividad && edad == otra.edad;
    }
};

class Multilista {
private:
    // Lista para ordenamiento por nombre (A-Z)
    Lista<Persona> listaNombre;

    // Listas independientes para cada carrera (5 listas)
    Lista<Persona> listaSistemas;
    Lista<Persona> listaElectrica;
    Lista<Persona> listaElectronica;
    Lista<Persona> listaCatastral;
    Lista<Persona> listaIndustrial;

    // Listas independientes para cada actividad (4 listas)
    Lista<Persona> listaDanza;
    Lista<Persona> listaBeisbol;
    Lista<Persona> listaBasquet;
    Lista<Persona> listaNatacion;

    // Lista para ordenamiento por edad (mayor a menor)
    Lista<Persona> listaEdad;

    // Datos válidos actualizados
    string carreras[5] = {"Sistemas", "Electrica", "Electronica", "Catastral", "Industrial"};
    string actividades[4] = {"Danza", "Beisbol", "Basquet", "Natacion"};

    // Métodos privados para obtener la lista correspondiente
    inline Lista<Persona>* getListaPorCarrera(const string& carrera);
    inline Lista<Persona>* getListaPorActividad(const string& actividad);

    // Métodos de inserción específicos
    inline void insertarEnListaNombre(const Persona& persona);
    inline void insertarEnListaCarrera(const Persona& persona);
    inline void insertarEnListaActividad(const Persona& persona);
    inline void insertarEnListaEdad(const Persona& persona);

    inline Persona parsearLineaArchivo(const string& linea);
    inline string formatearPersonaParaArchivo(const Persona& persona);

    // Métodos auxiliares para eliminación
    inline void eliminarDeListaNombre(const string& nombre);
    inline void eliminarDeListaCarrera(const string& nombre, const string& carrera);
    inline void eliminarDeListaActividad(const string& nombre, const string& actividad);
    inline void eliminarDeListaEdad(const string& nombre);

public:
    Multilista() = default;

    ~Multilista() = default;

    // Validaciones
    inline bool validarCarrera(const string& carrera);
    inline bool validarActividad(const string& actividad);

    // Inserción principal
    inline bool insertarPersona(const string& nombre, const string& carrera, const string& actividad, int edad);

    // Funciones de búsqueda
    inline bool buscarPersona(const string& nombre);
    inline Persona* obtenerPersona(const string& nombre);
    inline void mostrarResultadoBusqueda(const string& nombre);

    // Funciones de eliminación
    inline bool eliminarPersona(const string& nombre);
    inline bool eliminarPorIndice(int indice);

    // Función para verificar si la multilista está llena (opcional)
    inline bool estaLlena(int limite = 1000) { return getNumElementos() >= limite; }

    // Visualización general
    inline void mostrarPorNombre();
    inline void mostrarPorEdad();

    // Visualización por carrera específica
    inline void mostrarCarreraSistemas();
    inline void mostrarCarreraElectrica();
    inline void mostrarCarreraElectronica();
    inline void mostrarCarreraCatastral();
    inline void mostrarCarreraIndustrial();
    inline void mostrarTodasLasCarreras();

    // Visualización por actividad específica
    inline void mostrarActividadDanza();
    inline void mostrarActividadBeisbol();
    inline void mostrarActividadBasquet();
    inline void mostrarActividadNatacion();
    inline void mostrarTodasLasActividades();

    inline void mostrarCarrerasDisponibles();
    inline void mostrarActividadesDisponibles();
    inline void mostrarEstructuraCompleta();

    inline bool cargarDesdeArchivo(const string& nombreArchivo = "estudiantes.txt");
    inline bool guardarEnArchivo(const string& nombreArchivo = "estudiantes.txt");

    // Getters
    int getNumElementos() { return listaNombre.getNumElementos(); }
    bool estaVacia() { return listaNombre.listaVacia(); }
};

// Implementación de métodos auxiliares
// ================================
// FUNCIONES DE BÚSQUEDA
// ================================

bool Multilista::buscarPersona(const string& nombre) {
    if (listaNombre.listaVacia()) {
        return false;
    }

    for (int i = 0; i < listaNombre.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNombre.buscar(i);
        if (nodoActual && nodoActual->dato.nombre == nombre) {
            return true;
        }
    }
    return false;
}

Persona* Multilista::obtenerPersona(const string& nombre) {
    if (listaNombre.listaVacia()) {
        return nullptr;
    }

    for (int i = 0; i < listaNombre.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNombre.buscar(i);
        if (nodoActual && nodoActual->dato.nombre == nombre) {
            return &(nodoActual->dato);
        }
    }
    return nullptr;
}

void Multilista::mostrarResultadoBusqueda(const string& nombre) {
    cout << "\n=== RESULTADO DE BÚSQUEDA ===" << endl;
    cout << "Buscando: \"" << nombre << "\"" << endl;

    Persona* persona = obtenerPersona(nombre);
    if (persona != nullptr) {
        cout << "✓ ENCONTRADA:" << endl;
        cout << "  Nombre: " << persona->nombre << endl;
        cout << "  Carrera: " << persona->carrera << endl;
        cout << "  Actividad: " << persona->actividad << endl;
        cout << "  Edad: " << persona->edad << " años" << endl;
    } else {
        cout << "✗ NO ENCONTRADA" << endl;
        cout << "La persona \"" << nombre << "\" no está registrada." << endl;
    }
}

// ================================
// FUNCIONES DE ELIMINACIÓN
// ================================

bool Multilista::eliminarPersona(const string& nombre) {
    // Verificar si la persona existe
    if (!buscarPersona(nombre)) {
        cout << "Error: La persona \"" << nombre << "\" no existe." << endl;
        return false;
    }

    // Obtener datos de la persona antes de eliminar
    Persona* persona = obtenerPersona(nombre);
    if (persona == nullptr) {
        return false;
    }

    string carrera = persona->carrera;
    string actividad = persona->actividad;

    // Eliminar de todas las listas
    eliminarDeListaNombre(nombre);
    eliminarDeListaCarrera(nombre, carrera);
    eliminarDeListaActividad(nombre, actividad);
    eliminarDeListaEdad(nombre);

    cout << "✓ Persona \"" << nombre << "\" eliminada exitosamente de todas las listas." << endl;
    return true;
}

bool Multilista::eliminarPorIndice(int indice) {
    if (indice < 0 || indice >= listaNombre.getNumElementos()) {
        cout << "Error: Índice fuera de rango." << endl;
        return false;
    }

    nodo<Persona>* nodoActual = listaNombre.buscar(indice);
    if (nodoActual) {
        string nombre = nodoActual->dato.nombre;
        return eliminarPersona(nombre);
    }
    return false;
}

// ================================
// MÉTODOS AUXILIARES DE ELIMINACIÓN
// ================================

void Multilista::eliminarDeListaNombre(const string& nombre) {
    for (int i = 0; i < listaNombre.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNombre.buscar(i);
        if (nodoActual && nodoActual->dato.nombre == nombre) {
            listaNombre.borrar(i);
            break;
        }
    }
}

void Multilista::eliminarDeListaCarrera(const string& nombre, const string& carrera) {
    Lista<Persona>* lista = getListaPorCarrera(carrera);
    if (lista == nullptr) return;

    for (int i = 0; i < lista->getNumElementos(); i++) {
        nodo<Persona>* nodoActual = lista->buscar(i);
        if (nodoActual && nodoActual->dato.nombre == nombre) {
            lista->borrar(i);
            break;
        }
    }
}

void Multilista::eliminarDeListaActividad(const string& nombre, const string& actividad) {
    Lista<Persona>* lista = getListaPorActividad(actividad);
    if (lista == nullptr) return;

    for (int i = 0; i < lista->getNumElementos(); i++) {
        nodo<Persona>* nodoActual = lista->buscar(i);
        if (nodoActual && nodoActual->dato.nombre == nombre) {
            lista->borrar(i);
            break;
        }
    }
}

void Multilista::eliminarDeListaEdad(const string& nombre) {
    for (int i = 0; i < listaEdad.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaEdad.buscar(i);
        if (nodoActual && nodoActual->dato.nombre == nombre) {
            listaEdad.borrar(i);
            break;
        }
    }
}
bool Multilista::cargarDesdeArchivo(const string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false; // Archivo no existe (primera ejecución)
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            Persona persona = parsearLineaArchivo(linea);
            if (!persona.nombre.empty()) {
                // Usar la función existente sin cout para evitar spam
                if (validarCarrera(persona.carrera) && validarActividad(persona.actividad)) {
                    Persona nuevaPersona(persona.nombre, persona.carrera, persona.actividad, persona.edad);
                    insertarEnListaNombre(nuevaPersona);
                    insertarEnListaCarrera(nuevaPersona);
                    insertarEnListaActividad(nuevaPersona);
                    insertarEnListaEdad(nuevaPersona);
                }
            }
        }
    }
    archivo.close();
    return true;
}

bool Multilista::guardarEnArchivo(const string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    // Guardar usando la lista de nombres (que tiene todos los elementos)
    for (int i = 0; i < listaNombre.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNombre.buscar(i);
        if (nodoActual) {
            archivo << formatearPersonaParaArchivo(nodoActual->dato) << endl;
        }
    }
    archivo.close();
    return true;
}

// Agregar en la sección private:

Persona Multilista::parsearLineaArchivo(const string& linea) {
    // Formato esperado: "Nombre|Carrera|Actividad|Edad"
    std::stringstream ss(linea);
    string nombre, carrera, actividad, edadStr;

    if (getline(ss, nombre, '|') &&
        getline(ss, carrera, '|') &&
        getline(ss, actividad, '|') &&
        getline(ss, edadStr)) {
        try {
            int edad = std::stoi(edadStr);
            return Persona(nombre, carrera, actividad, edad);
        } catch (const std::exception& e) {
            return Persona(); // Error al convertir edad
        }
    }
    return Persona(); // Retorna persona vacía si hay error
}

string Multilista::formatearPersonaParaArchivo(const Persona& persona) {
    return persona.nombre + "|" + persona.carrera + "|" +
           persona.actividad + "|" + std::to_string(persona.edad);
}

Lista<Persona>* Multilista::getListaPorCarrera(const string& carrera) {
    if (carrera == "Sistemas") return &listaSistemas;
    if (carrera == "Electrica") return &listaElectrica;
    if (carrera == "Electronica") return &listaElectronica;
    if (carrera == "Catastral") return &listaCatastral;
    if (carrera == "Industrial") return &listaIndustrial;
    return nullptr;
}

Lista<Persona>* Multilista::getListaPorActividad(const string& actividad) {
    if (actividad == "Danza") return &listaDanza;
    if (actividad == "Beisbol") return &listaBeisbol;
    if (actividad == "Basquet") return &listaBasquet;
    if (actividad == "Natacion") return &listaNatacion;
    return nullptr;
}

// Implementación de métodos principales

bool Multilista::validarCarrera(const string& carrera) {
    for (const auto & i : carreras) {
        if (i == carrera) return true;
    }
    return false;
}

bool Multilista::validarActividad(const string& actividad) {
    for (const auto & actividade : actividades) {
        if (actividade == actividad) return true;
    }
    return false;
}

bool Multilista::insertarPersona(const string& nombre, const string& carrera, const string& actividad, int edad) {
    // Validar datos
    if (nombre.empty() || edad <= 0) {
        cout << "Error: Nombre vacío o edad inválida" << endl;
        return false;
    }

    if (!validarCarrera(carrera)) {
        cout << "Error: Carrera no válida." << endl;
        mostrarCarrerasDisponibles();
        return false;
    }

    if (!validarActividad(actividad)) {
        cout << "Error: Actividad no válida." << endl;
        mostrarActividadesDisponibles();
        return false;
    }

    // Crear objeto persona
    Persona nuevaPersona(nombre, carrera, actividad, edad);

    // Insertar en todas las listas usando Lista.h
    insertarEnListaNombre(nuevaPersona);
    insertarEnListaCarrera(nuevaPersona);
    insertarEnListaActividad(nuevaPersona);
    insertarEnListaEdad(nuevaPersona);

    cout << "Persona insertada exitosamente en todas las listas" << endl;
    return true;
}

void Multilista::insertarEnListaNombre(const Persona& persona) {
    // Insertar ordenado lexicográficamente (A-Z) usando Lista.h
    if (listaNombre.listaVacia()) {
        listaNombre.insertarInicio(persona);
        return;
    }

    // Buscar posición correcta para mantener orden alfabético
    bool insertado = false;
    for (int i = 0; i < listaNombre.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNombre.buscar(i);
        if (nodoActual && persona.nombre < nodoActual->dato.nombre) {
            listaNombre.insertar(persona, i);
            insertado = true;
            break;
        }
    }

    if (!insertado) {
        listaNombre.insertarFinal(persona);
    }
}

void Multilista::insertarEnListaCarrera(const Persona& persona) {
    // Obtener la lista correspondiente a la carrera
    Lista<Persona>* lista = getListaPorCarrera(persona.carrera);
    if (lista != nullptr) {
        // Insertar al final para esta carrera
        lista->insertarFinal(persona);
    }
}

void Multilista::insertarEnListaActividad(const Persona& persona) {
    // Obtener la lista correspondiente a la actividad
    Lista<Persona>* lista = getListaPorActividad(persona.actividad);
    if (lista != nullptr) {
        // Insertar al inicio para esta actividad
        lista->insertarInicio(persona);
    }
}

void Multilista::insertarEnListaEdad(const Persona& persona) {
    // Insertar ordenado por edad (mayor a menor) usando Lista.h
    if (listaEdad.listaVacia()) {
        listaEdad.insertarInicio(persona);
        return;
    }

    // Buscar posición correcta para mantener orden por edad (mayor a menor)
    bool insertado = false;
    for (int i = 0; i < listaEdad.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaEdad.buscar(i);
        if (nodoActual && persona.edad > nodoActual->dato.edad) {
            listaEdad.insertar(persona, i);
            insertado = true;
            break;
        }
    }

    if (!insertado) {
        listaEdad.insertarFinal(persona);
    }
}

void Multilista::mostrarPorNombre() {
    cout << "\n=== LISTA ORDENADA POR NOMBRE (A-Z) ===" << endl;
    if (listaNombre.listaVacia()) {
        cout << "Lista vacia" << endl;
        return;
    }

    for (int i = 0; i < listaNombre.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNombre.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.carrera << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarPorEdad() {
    cout << "\n=== LISTA ORDENADA POR EDAD (Mayor a menor) ===" << endl;
    if (listaEdad.listaVacia()) {
        cout << "Lista vacia" << endl;
        return;
    }

    for (int i = 0; i < listaEdad.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaEdad.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.carrera << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

// Métodos para mostrar carreras específicas

void Multilista::mostrarCarreraSistemas() {
    cout << "\n=== ESTUDIANTES DE SISTEMAS ===" << endl;
    if (listaSistemas.listaVacia()) {
        cout << "No hay estudiantes de Sistemas" << endl;
        return;
    }

    for (int i = 0; i < listaSistemas.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaSistemas.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarCarreraElectrica() {
    cout << "\n=== ESTUDIANTES DE ELECTRICA ===" << endl;
    if (listaElectrica.listaVacia()) {
        cout << "No hay estudiantes de Electrica" << endl;
        return;
    }

    for (int i = 0; i < listaElectrica.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaElectrica.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarCarreraElectronica() {
    cout << "\n=== ESTUDIANTES DE ELECTRONICA ===" << endl;
    if (listaElectronica.listaVacia()) {
        cout << "No hay estudiantes de Electronica" << endl;
        return;
    }

    for (int i = 0; i < listaElectronica.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaElectronica.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarCarreraCatastral() {
    cout << "\n=== ESTUDIANTES DE CATASTRAL ===" << endl;
    if (listaCatastral.listaVacia()) {
        cout << "No hay estudiantes de Catastral" << endl;
        return;
    }

    for (int i = 0; i < listaCatastral.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaCatastral.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarCarreraIndustrial() {
    cout << "\n=== ESTUDIANTES DE INDUSTRIAL ===" << endl;
    if (listaIndustrial.listaVacia()) {
        cout << "No hay estudiantes de Industrial" << endl;
        return;
    }

    for (int i = 0; i < listaIndustrial.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaIndustrial.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.actividad << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

// Métodos para mostrar actividades específicas

void Multilista::mostrarActividadDanza() {
    cout << "\n=== PERSONAS QUE PRACTICAN DANZA ===" << endl;
    if (listaDanza.listaVacia()) {
        cout << "No hay personas que practiquen Danza" << endl;
        return;
    }

    for (int i = 0; i < listaDanza.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaDanza.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.carrera << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarActividadBeisbol() {
    cout << "\n=== PERSONAS QUE PRACTICAN BEISBOL ===" << endl;
    if (listaBeisbol.listaVacia()) {
        cout << "No hay personas que practiquen Beisbol" << endl;
        return;
    }

    for (int i = 0; i < listaBeisbol.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaBeisbol.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.carrera << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarActividadBasquet() {
    cout << "\n=== PERSONAS QUE PRACTICAN BASQUET ===" << endl;
    if (listaBasquet.listaVacia()) {
        cout << "No hay personas que practiquen Basquet" << endl;
        return;
    }

    for (int i = 0; i < listaBasquet.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaBasquet.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.carrera << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarActividadNatacion() {
    cout << "\n=== PERSONAS QUE PRACTICAN NATACION ===" << endl;
    if (listaNatacion.listaVacia()) {
        cout << "No hay personas que practiquen Natacion" << endl;
        return;
    }

    for (int i = 0; i < listaNatacion.getNumElementos(); i++) {
        nodo<Persona>* nodoActual = listaNatacion.buscar(i);
        if (nodoActual) {
            cout << (i+1) << ". " << nodoActual->dato.nombre << " | "
                 << nodoActual->dato.carrera << " | "
                 << nodoActual->dato.edad << " anos" << endl;
        }
    }
}

void Multilista::mostrarTodasLasCarreras() {
    cout << "\n=== TODAS LAS CARRERAS ===" << endl;
    mostrarCarreraSistemas();
    mostrarCarreraElectrica();
    mostrarCarreraElectronica();
    mostrarCarreraCatastral();
    mostrarCarreraIndustrial();
}

void Multilista::mostrarTodasLasActividades() {
    cout << "\n=== TODAS LAS ACTIVIDADES ===" << endl;
    mostrarActividadDanza();
    mostrarActividadBeisbol();
    mostrarActividadBasquet();
    mostrarActividadNatacion();
}

void Multilista::mostrarCarrerasDisponibles() {
    cout << "Carreras disponibles:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << (i+1) << ". " << carreras[i] << endl;
    }
}

void Multilista::mostrarActividadesDisponibles() {
    cout << "Actividades disponibles:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << (i+1) << ". " << actividades[i] << endl;
    }
}

void Multilista::mostrarEstructuraCompleta() {
    cout << "\n=== ESTRUCTURA COMPLETA DE LA MULTILISTA ===" << endl;
    cout << "Numero total de elementos: " << getNumElementos() << endl;

    cout << "\n--- ESTADISTICAS POR LISTA ---" << endl;
    cout << "Lista por Nombre: " << listaNombre.getNumElementos() << " estudiantes" << endl;
    cout << "Lista por Edad: " << listaEdad.getNumElementos() << " estudiantes" << endl;

    cout << "\n--- ESTADISTICAS POR CARRERA ---" << endl;
    cout << "Sistemas: " << listaSistemas.getNumElementos() << " estudiantes" << endl;
    cout << "Electrica: " << listaElectrica.getNumElementos() << " estudiantes" << endl;
    cout << "Electronica: " << listaElectronica.getNumElementos() << " estudiantes" << endl;
    cout << "Catastral: " << listaCatastral.getNumElementos() << " estudiantes" << endl;
    cout << "Industrial: " << listaIndustrial.getNumElementos() << " estudiantes" << endl;

    cout << "\n--- ESTADISTICAS POR ACTIVIDAD ---" << endl;
    cout << "Danza: " << listaDanza.getNumElementos() << " estudiantes" << endl;
    cout << "Beisbol: " << listaBeisbol.getNumElementos() << " estudiantes" << endl;
    cout << "Basquet: " << listaBasquet.getNumElementos() << " estudiantes" << endl;
    cout << "Natacion: " << listaNatacion.getNumElementos() << " estudiantes" << endl;
}

#endif // MULTILISTA_H