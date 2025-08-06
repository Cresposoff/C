#include <iostream>
#include <string>
#include <limits> // Para numeric_limits

using namespace std;

// Estructura para los empleados (lista simplemente enlazada)
struct Empleado {
    int codigo;
    string nombre;
    Empleado* siguiente;

    Empleado(int cod, string nom) : codigo(cod), nombre(nom), siguiente(nullptr) {}
};

// Estructura para las oficinas (lista circular doblemente enlazada con cabeza y cola)
struct Oficina {
    int codigo;
    string nombre;
    Oficina* siguiente;
    Oficina* anterior;
    Empleado* empleados; // Puntero al primer empleado de la oficina

    Oficina(int cod, string nom) : codigo(cod), nombre(nom), siguiente(nullptr), anterior(nullptr), empleados(nullptr) {}
};

// Estructura para la lista de oficinas
struct ListaOficinas {
    Oficina* cabeza;
    Oficina* cola;

    ListaOficinas() : cabeza(nullptr), cola(nullptr) {}

    bool estaVacia() {
        return cabeza == nullptr;
    }

    // Insertar una oficina al final de la lista
    void insertarOficina(Oficina* nuevaOficina) {
        if (estaVacia()) {
            cabeza = nuevaOficina;
            cola = nuevaOficina;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            nuevaOficina->anterior = cola;
            nuevaOficina->siguiente = cabeza;
            cola->siguiente = nuevaOficina;
            cabeza->anterior = nuevaOficina;
            cola = nuevaOficina;
        }
    }

    // Buscar una oficina por codigo
    Oficina* buscarOficina(int codigo) {
        if (estaVacia()) {
            return nullptr;
        }
        Oficina* actual = cabeza;
        do {
            if (actual->codigo == codigo) {
                return actual;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        return nullptr;
    }

    // Modificar una oficina
    bool modificarOficina(int codigo, string nuevoNombre) {
        Oficina* oficina = buscarOficina(codigo);
        if (oficina) {
            oficina->nombre = nuevoNombre;
            return true;
        }
        return false;
    }

    // Eliminar una oficina
    bool eliminarOficina(int codigo) {
        Oficina* oficinaAEliminar = buscarOficina(codigo);
        if (!oficinaAEliminar) {
            cout << "La oficina con codigo " << codigo << " no existe." << endl;
            return false;
        }

        if (oficinaAEliminar->empleados != nullptr) {
            cout << "No se puede eliminar la oficina con codigo " << codigo << " porque tiene empleados asignados." << endl;
            return false;
        }

        if (oficinaAEliminar == cabeza && oficinaAEliminar == cola) {
            cabeza = nullptr;
            cola = nullptr;
        } else if (oficinaAEliminar == cabeza) {
            cabeza = cabeza->siguiente;
            cabeza->anterior = cola;
            cola->siguiente = cabeza;
        } else if (oficinaAEliminar == cola) {
            cola = cola->anterior;
            cola->siguiente = cabeza;
            cabeza->anterior = cola;
        } else {
            oficinaAEliminar->anterior->siguiente = oficinaAEliminar->siguiente;
            oficinaAEliminar->siguiente->anterior = oficinaAEliminar->anterior;
        }
        delete oficinaAEliminar;
        cout << "Oficina con codigo " << codigo << " eliminada." << endl;
        return true;
    }

    // Listar oficinas ascendentemente por codigo
    void listarOficinasAscendente() {
        if (estaVacia()) {
            cout << "No hay oficinas creadas." << endl;
            return;
        }
        cout << "\nListado de oficinas (ascendente por codigo):\n";
        Oficina* actual = cabeza;
        do {
            cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Listar oficinas descendentemente por codigo
    void listarOficinasDescendente() {
        if (estaVacia()) {
            cout << "No hay oficinas creadas." << endl;
            return;
        }
        cout << "\nListado de oficinas (descendente por codigo):\n";
        Oficina* actual = cola;
        do {
            cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << endl;
            actual = actual->anterior;
        } while (actual != cola->anterior);
        cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << endl; // Imprimir el ultimo elemento
    }
};

// Funciones para la gestion de empleados dentro de una oficina
void insertarEmpleado(Oficina* oficina, Empleado* nuevoEmpleado) {
    if (!oficina->empleados) {
        oficina->empleados = nuevoEmpleado;
    } else {
        Empleado* actual = oficina->empleados;
        Empleado* anterior = nullptr;

        // Buscar la posicion correcta para insertar (orden ascendente por codigo)
        while (actual && nuevoEmpleado->codigo > actual->codigo) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual && nuevoEmpleado->codigo == actual->codigo) {
            cout << "Error: El codigo de empleado " << nuevoEmpleado->codigo << " ya existe en esta oficina." << endl;
            delete nuevoEmpleado;
            return;
        }

        if (anterior == nullptr) {
            nuevoEmpleado->siguiente = oficina->empleados;
            oficina->empleados = nuevoEmpleado;
        } else {
            anterior->siguiente = nuevoEmpleado;
            nuevoEmpleado->siguiente = actual;
        }
    }
    cout << "Empleado " << nuevoEmpleado->nombre << " (codigo " << nuevoEmpleado->codigo << ") agregado a la oficina " << oficina->nombre << "." << endl;
}

// Buscar un empleado por codigo en una oficina
Empleado* buscarEmpleado(Oficina* oficina, int codigo) {
    Empleado* actual = oficina->empleados;
    while (actual) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Modificar un empleado en una oficina
void modificarEmpleado(Oficina* oficina, int codigo, string nuevoNombre, int nuevoCodigo) {
    Empleado* empleadoAModificar = buscarEmpleado(oficina, codigo);
    if (empleadoAModificar) {
        if (nuevoCodigo != codigo && buscarEmpleado(oficina, nuevoCodigo)) {
            cout << "Error: El nuevo codigo de empleado " << nuevoCodigo << " ya existe en esta oficina." << endl;
            return;
        }
        empleadoAModificar->nombre = nuevoNombre;
        if (nuevoCodigo != codigo) {
            // Eliminar y reinsertar para mantener el orden
            Empleado* anterior = nullptr;
            Empleado* actual = oficina->empleados;
            while (actual && actual->codigo != codigo) {
                anterior = actual;
                actual = actual->siguiente;
            }
            if (anterior == nullptr) {
                oficina->empleados = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            empleadoAModificar->codigo = nuevoCodigo;
            empleadoAModificar->siguiente = nullptr;
            insertarEmpleado(oficina, empleadoAModificar);
        } else {
            cout << "Empleado con codigo " << codigo << " modificado." << endl;
        }
    } else {
        cout << "No se encontro el empleado con codigo " << codigo << " en esta oficina." << endl;
    }
}

// Eliminar un empleado de una oficina
void eliminarEmpleado(Oficina* oficina, int codigo) {
    Empleado* actual = oficina->empleados;
    Empleado* anterior = nullptr;

    while (actual) {
        if (actual->codigo == codigo) {
            if (anterior == nullptr) {
                oficina->empleados = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            cout << "Empleado con codigo " << codigo << " eliminado de la oficina " << oficina->nombre << "." << endl;
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cout << "No se encontro el empleado con codigo " << codigo << " en esta oficina." << endl;
}

// Listar los empleados de una oficina
void listarEmpleados(Oficina* oficina) {
    cout << "\nListado de empleados de la oficina " << oficina->nombre << " (codigo " << oficina->codigo << "):\n";
    if (!oficina->empleados) {
        cout << "No hay empleados en esta oficina." << endl;
        return;
    }
    Empleado* actual = oficina->empleados;
    while (actual) {
        cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << endl;
        actual = actual->siguiente;
    }
}

int main() {
    ListaOficinas listaDeOficinas;
    int opcionGeneral, opcionOficina, opcionEmpleado, codigoOficina, codigoEmpleado, nuevoCodigoEmpleado;
    string nombreOficina, nombreEmpleado;
    Oficina* oficinaActual;

    do {
        cout << "\n--- Menu General ---" << endl;
        cout << "1. Menu Oficinas" << endl;
        cout << "2. Menu Empleados" << endl;
        cout << "3. Menu Especial" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionGeneral;

        // Limpiar el buffer del teclado
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcionGeneral) {
            case 1: // Menu Oficinas
                do {
                    cout << "\n--- Menu Oficinas ---" << endl;
                    cout << "1. Crear Oficina" << endl;
                    cout << "2. Modificar Oficina" << endl;
                    cout << "3. Borrar Oficina" << endl;
                    cout << "4. Listar Oficinas (Ascendente por Codigo)" << endl;
                    cout << "5. Listar Oficinas (Descendente por Codigo)" << endl;
                    cout << "0. Volver al Menu General" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> opcionOficina;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (opcionOficina) {
                        case 1: // Crear Oficina
                            cout << "Ingrese el codigo de la nueva oficina: ";
                            cin >> codigoOficina;
                            cout << "Ingrese el nombre de la nueva oficina: ";
                            getline(cin >> ws, nombreOficina);
                            if (!listaDeOficinas.buscarOficina(codigoOficina)) {
                                listaDeOficinas.insertarOficina(new Oficina(codigoOficina, nombreOficina));
                                cout << "Oficina creada." << endl;
                            } else {
                                cout << "Error: Ya existe una oficina con el codigo " << codigoOficina << "." << endl;
                            }
                            break;
                        case 2: // Modificar Oficina
                            cout << "Ingrese el codigo de la oficina a modificar: ";
                            cin >> codigoOficina;
                            cout << "Ingrese el nuevo nombre de la oficina: ";
                            getline(cin >> ws, nombreOficina);
                            if (listaDeOficinas.modificarOficina(codigoOficina, nombreOficina)) {
                                cout << "Oficina modificada." << endl;
                            } else {
                                cout << "No se encontro la oficina con codigo " << codigoOficina << "." << endl;
                            }
                            break;
                        case 3: // Borrar Oficina
                            cout << "Ingrese el codigo de la oficina a borrar: ";
                            cin >> codigoOficina;
                            listaDeOficinas.eliminarOficina(codigoOficina);
                            break;
                        case 4: // Listar Oficinas Ascendente
                            listaDeOficinas.listarOficinasAscendente();
                            break;
                        case 5: // Listar Oficinas Descendente
                            listaDeOficinas.listarOficinasDescendente();
                            break;
                        case 0: // Volver al Menu General
                            break;
                        default:
                            cout << "Opcion invalida." << endl;
                    }
                } while (opcionOficina != 0);
                break;

            case 2: // Menu Empleados
                do {
                    cout << "\n--- Menu Empleados ---" << endl;
                    cout << "1. Crear Empleado" << endl;
                    cout << "2. Modificar Empleado" << endl;
                    cout << "3. Borrar Empleado" << endl;
                    cout << "4. Listar Empleados de una Oficina" << endl;
                    cout << "0. Volver al Menu General" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> opcionEmpleado;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (opcionEmpleado) {
                        case 1: // Crear Empleado
                            cout << "Ingrese el codigo del nuevo empleado: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el nombre del nuevo empleado: ";
                            getline(cin >> ws, nombreEmpleado);
                            cout << "Ingrese el codigo de la oficina para este empleado: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                if (!buscarEmpleado(oficinaActual, codigoEmpleado)) {
                                    insertarEmpleado(oficinaActual, new Empleado(codigoEmpleado, nombreEmpleado));
                                } else {
                                    cout << "Error: El codigo de empleado " << codigoEmpleado << " ya existe en esta oficina." << endl;
                                }
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            break;
                        case 2: // Modificar Empleado
                            cout << "Ingrese el codigo del empleado a modificar: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el nuevo nombre del empleado: ";
                            getline(cin >> ws, nombreEmpleado);
                            cout << "Ingrese el nuevo codigo del empleado: ";
                            cin >> nuevoCodigoEmpleado;
                            cout << "Ingrese el codigo de la oficina del empleado: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                modificarEmpleado(oficinaActual, codigoEmpleado, nombreEmpleado, nuevoCodigoEmpleado);
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            break;
                        case 3: // Borrar Empleado
                            cout << "Ingrese el codigo del empleado a borrar: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el codigo de la oficina del empleado: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                eliminarEmpleado(oficinaActual, codigoEmpleado);
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            break;
                        case 4: // Listar Empleados de una Oficina
                            cout << "Ingrese el codigo de la oficina para listar sus empleados: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                listarEmpleados(oficinaActual);
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            break;
                        case 0: // Volver al Menu General
                            break;
                        default:
                            cout << "Opcion invalida." << endl;
                    }
                } while (opcionEmpleado != 0);
                break;

            case 3: // Menu Especial
                cout << "\n--- Menu Especial ---" << endl;
                cout << "Este menu es para una segunda parte del proyecto." << endl;
                break;

            case 0: // Salir
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcionGeneral != 0);

    // Liberar la memoria (opcional, pero buena practica)
    Oficina* actualOficina = listaDeOficinas.cabeza;
    if (actualOficina) {
        do {
            Empleado* actualEmpleado = actualOficina->empleados;
            while (actualEmpleado) {
                Empleado* temp = actualEmpleado;
                actualEmpleado = actualEmpleado->siguiente;
                delete temp;
            }
            Oficina* tempOficina = actualOficina;
            actualOficina = actualOficina->siguiente;
            delete tempOficina;
        } while (actualOficina != listaDeOficinas.cabeza);
    }
    return 0;
}