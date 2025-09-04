#include <iostream>
#include <string>
#include "MULTILISTA.h"

using namespace std;

void mostrarMenuPrincipal() {
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1.  Insertar nueva persona" << endl;
    cout << "2.  Mostrar por nombre (A-Z)" << endl;
    cout << "3.  Mostrar por edad (mayor a menor)" << endl;
    cout << "4.  Mostrar carrera especifica" << endl;
    cout << "5.  Mostrar actividad especifica" << endl;
    cout << "6.  Mostrar todas las carreras" << endl;
    cout << "7.  Mostrar todas las actividades" << endl;
    cout << "8.  Mostrar estructura completa" << endl;
    cout << "9. Buscar persona" << endl;
    cout << "10. Eliminar persona" << endl;
    cout << "0.  Salir" << endl;
    cout << "=======================" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarMenuCarreras() {
    cout << "\n=== CARRERAS DISPONIBLES ===" << endl;
    cout << "1. Sistemas" << endl;
    cout << "2. Electrica" << endl;
    cout << "3. Electronica" << endl;
    cout << "4. Catastral" << endl;
    cout << "5. Industrial" << endl;
    cout << "Seleccione: ";
}

void mostrarMenuActividades() {
    cout << "\n=== ACTIVIDADES DISPONIBLES ===" << endl;
    cout << "1. Danza" << endl;
    cout << "2. Beisbol" << endl;
    cout << "3. Basquet" << endl;
    cout << "4. Natacion" << endl;
    cout << "Seleccione: ";
}

void insertarPersonaManual(Multilista& multilista) {
    string nombre, carrera, actividad;
    int edad;
    
    cout << "\n=== INSERTAR NUEVA PERSONA ===" << endl;
    
    cout << "Nombre completo: ";
    getline(cin, nombre);
    
    cout << "Carrera (Sistemas/Electrica/Electronica/Catastral/Industrial): ";
    getline(cin, carrera);
    
    cout << "Actividad (Danza/Beisbol/Basquet/Natacion): ";
    getline(cin, actividad);
    
    cout << "Edad: ";
    cin >> edad;
    
    if (multilista.insertarPersona(nombre, carrera, actividad, edad)) {
        cout << "\nPersona registrada exitosamente!" << endl;
    } else {
        cout << "\nError al registrar la persona." << endl;
    }
}

void buscarPersonaManual(Multilista& multilista) {
    string nombre;

    cout << "\n=== BUSCAR PERSONA ===" << endl;
    cout << "Nombre completo a buscar: ";
    getline(cin, nombre);

    if (nombre.empty()) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    multilista.mostrarResultadoBusqueda(nombre);
}

void eliminarPersonaManual(Multilista& multilista) {
    if (multilista.estaVacia()) {
        cout << "No hay personas registradas para eliminar." << endl;
        return;
    }

    string nombre;
    char confirmacion;

    cout << "\n=== ELIMINAR PERSONA ===" << endl;
    cout << "Nombre completo a eliminar: ";
    getline(cin, nombre);

    if (nombre.empty()) {
        cout << "Error: Debe ingresar un nombre." << endl;
        return;
    }

    // Mostrar datos de la persona antes de eliminar
    if (multilista.buscarPersona(nombre)) {
        multilista.mostrarResultadoBusqueda(nombre);

        cout << "\n¿Esta seguro de eliminar esta persona? (s/n): ";
        cin >> confirmacion;
        cin.ignore(); // Limpiar buffer

        if (confirmacion == 's' || confirmacion == 'S') {
            if (multilista.eliminarPersona(nombre)) {
                cout << "Total de personas restantes: " << multilista.getNumElementos() << endl;
            }
        } else {
            cout << "Eliminacion cancelada." << endl;
        }
    } else {
        cout << "La persona \"" << nombre << "\" no existe." << endl;
    }
}

void gestionarCarreras(Multilista& multilista) {
    int opcion;
    mostrarMenuCarreras();
    cin >> opcion;
    
    switch(opcion) {
        case 1: multilista.mostrarCarreraSistemas(); break;
        case 2: multilista.mostrarCarreraElectrica(); break;
        case 3: multilista.mostrarCarreraElectronica(); break;
        case 4: multilista.mostrarCarreraCatastral(); break;
        case 5: multilista.mostrarCarreraIndustrial(); break;
        default: 
            cout << "\nOpcion no valida" << endl;
            multilista.mostrarCarrerasDisponibles();
    }
}

void gestionarActividades(Multilista& multilista) {
    int opcion;
    mostrarMenuActividades();
    cin >> opcion;
    
    switch(opcion) {
        case 1: multilista.mostrarActividadDanza(); break;
        case 2: multilista.mostrarActividadBeisbol(); break;
        case 3: multilista.mostrarActividadBasquet(); break;
        case 4: multilista.mostrarActividadNatacion(); break;
        default: 
            cout << "\nOpcion no valida" << endl;
            multilista.mostrarActividadesDisponibles();
    }
}


int main() {
    Multilista multilista;
    cout << "Cargando datos desde archivo..." << endl;
    if (multilista.cargarDesdeArchivo()) {  // Si no funciona, agrega la ruta al parametro de la funcion
        cout << "Datos cargados exitosamente (" << multilista.getNumElementos() << " personas)" << endl;
    } else {
        cout << "No se encontro archivo previo. Iniciando sistema vacio." << endl;
    }
    int opcion;
    cout << "Nombre (orden alfabetico)" << endl;
    cout << "Carrera (5 ingenierias)" << endl;
    cout << "Actividad (4 actividades)" << endl;
    cout << "Edad (de mayor a menor)" << endl;
    
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer
        
        switch (opcion) {
            case 1:
                insertarPersonaManual(multilista);
                break;
                
            case 2:
                multilista.mostrarPorNombre();
                break;
                
            case 3:
                multilista.mostrarPorEdad();
                break;
                
            case 4:
                gestionarCarreras(multilista);
                break;
                
            case 5:
                gestionarActividades(multilista);
                break;
                
            case 6:
                multilista.mostrarTodasLasCarreras();
                break;
                
            case 7:
                multilista.mostrarTodasLasActividades();
                break;
                
            case 8:
                multilista.mostrarEstructuraCompleta();
                break;

            case 9:
                buscarPersonaManual(multilista);
                break;

            case 10:
                eliminarPersonaManual(multilista);
                break;
                
            case 0:
                break;
                
            default:
                cout << "\nOpcion no valida. Intente nuevamente." << endl;
        }

        
    } while (opcion != 0);
    cout << "\nGuardando datos en archivo..." << endl;
    if (multilista.guardarEnArchivo()) { // Si no funciona ,agrega la ruta del archivo al parametro de la funcion
        cout << "Datos guardados exitosamente!" << endl;
    } else {
        cout << "Error al guardar datos." << endl;
    }
    return 0;
}