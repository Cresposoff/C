#include <iostream>
#include <string>
#include <limits>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para los empleados (lista simplemente enlazada)
struct Empleado {
    int codigo;
    string nombre;
    float sueldo;
    Empleado* siguiente;
};

// Estructura para las oficinas (lista circular doblemente enlazada con cabeza y cola)
struct Oficina {
    int codigo;
    string nombre;
    Oficina* siguiente;
    Oficina* anterior;
    Empleado* empleados;
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
    void insertarOficina(int codigo, string nombre) {
        Oficina* nuevaOficina = new Oficina;
        nuevaOficina->codigo = codigo;
        nuevaOficina->nombre = nombre;
        nuevaOficina->siguiente = nullptr;
        nuevaOficina->anterior = nullptr;
        nuevaOficina->empleados = nullptr;

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
        cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << endl;
    }
};

// Funciones para la gestion de empleados dentro de una oficina
void insertarEmpleado(Oficina* oficina, int codigo, string nombre, float sueldo) {
    Empleado* nuevoEmpleado = new Empleado;
    nuevoEmpleado->codigo = codigo;
    nuevoEmpleado->nombre = nombre;
    nuevoEmpleado->sueldo = sueldo;
    nuevoEmpleado->siguiente = nullptr;

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
    cout << "Empleado " << nombre << " (codigo " << codigo << ") agregado a la oficina " << oficina->nombre << "." << endl;
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
void modificarEmpleado(Oficina* oficina, int codigo, string nuevoNombre, float nuevoSueldo, int nuevoCodigo) {
    Empleado* empleadoAModificar = buscarEmpleado(oficina, codigo);
    if (empleadoAModificar) {
        if (nuevoCodigo != codigo && buscarEmpleado(oficina, nuevoCodigo)) {
            cout << "Error: El nuevo codigo de empleado " << nuevoCodigo << " ya existe en esta oficina." << endl;
            return;
        }
        empleadoAModificar->nombre = nuevoNombre;
        empleadoAModificar->sueldo = nuevoSueldo;
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
            insertarEmpleado(oficina, empleadoAModificar->codigo, empleadoAModificar->nombre, empleadoAModificar->sueldo);
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
        cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << ", Sueldo: " << actual->sueldo << endl;
        actual = actual->siguiente;
    }
}

// Función para el Menu Especial: Reporte de los 3 empleados con menor sueldo
void generarReporteEmpleadosMenorSueldo(ListaOficinas listaDeOficinas) {
    system("cls");
    cout << "\n--- Reporte de los 3 Empleados con Menor Sueldo ---" << endl;

    // Vector para almacenar todos los empleados con su informacion de oficina
    vector<pair<Empleado*, Oficina*>> todosLosEmpleados;

    // Recorrer todas las oficinas y sus empleados
    Oficina* actualOficina = listaDeOficinas.cabeza;
    if (actualOficina) {
        do {
            Empleado* actualEmpleado = actualOficina->empleados;
            while (actualEmpleado) {
                todosLosEmpleados.push_back({actualEmpleado, actualOficina});
                actualEmpleado = actualEmpleado->siguiente;
            }
            actualOficina = actualOficina->siguiente;
        } while (actualOficina != listaDeOficinas.cabeza);
    }

    // Si no hay empleados, mostrar mensaje y retornar
    if (todosLosEmpleados.empty()) {
        cout << "No hay empleados en ninguna oficina." << endl;
        _getch();
        return;
    }

    // Ordenar los empleados por sueldo (de menor a mayor)
    sort(todosLosEmpleados.begin(), todosLosEmpleados.end(),
         [](const pair<Empleado*, Oficina*>& a, const pair<Empleado*, Oficina*>& b) {
             return a.first->sueldo < b.first->sueldo;
         });

    // Mostrar los 3 empleados con menor sueldo (o todos si hay menos de 3)
    int numEmpleadosAMostrar = min(3, (int)todosLosEmpleados.size());
    cout << "Los " << numEmpleadosAMostrar << " empleados con menor sueldo son:\n";
    for (int i = 0; i < numEmpleadosAMostrar; ++i) {
        Empleado* empleado = todosLosEmpleados[i].first;
        Oficina* oficina = todosLosEmpleados[i].second;
        cout << "Oficina - Codigo: " << oficina->codigo << ", Nombre: " << oficina->nombre << endl;
        cout << "  Empleado - Codigo: " << empleado->codigo << ", Nombre: " << empleado->nombre
             << ", Sueldo: " << empleado->sueldo << endl;
    }
    _getch();
}

int main() {
    ListaOficinas listaDeOficinas;
    int opcionGeneral, opcionOficina, opcionEmpleado, codigoOficina, codigoEmpleado, nuevoCodigoEmpleado;
    string nombreOficina, nombreEmpleado;
    float sueldoEmpleado, nuevoSueldoEmpleado;
    Oficina* oficinaActual;

    do {
        system("cls");
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
                    system("cls");
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
                            system("cls");
                            cout << "Ingrese el codigo de la nueva oficina: ";
                            cin >> codigoOficina;
                            cout << "Ingrese el nombre de la nueva oficina: ";
                            getline(cin >> ws, nombreOficina);
                            if (!listaDeOficinas.buscarOficina(codigoOficina)) {
                                listaDeOficinas.insertarOficina(codigoOficina, nombreOficina);
                                cout << "Oficina creada." << endl;
                            } else {
                                cout << "Error: Ya existe una oficina con el codigo " << codigoOficina << "." << endl;
                            }
                            _getch();
                            break;
                        case 2: // Modificar Oficina
                            system("cls");
                            cout << "Ingrese el codigo de la oficina a modificar: ";
                            cin >> codigoOficina;
                            cout << "Ingrese el nuevo nombre de la oficina: ";
                            getline(cin >> ws, nombreOficina);
                            if (listaDeOficinas.modificarOficina(codigoOficina, nombreOficina)) {
                                cout << "Oficina modificada." << endl;
                            } else {
                                cout << "No se encontro la oficina con codigo " << codigoOficina << "." << endl;
                            }
                            _getch();
                            break;
                        case 3: // Borrar Oficina
                            system("cls");
                            cout << "Ingrese el codigo de la oficina a borrar: ";
                            cin >> codigoOficina;
                            listaDeOficinas.eliminarOficina(codigoOficina);
                            _getch();
                            break;
                        case 4: // Listar Oficinas Ascendente
                            system("cls");
                            listaDeOficinas.listarOficinasAscendente();
                            _getch();
                            break;
                        case 5: // Listar Oficinas Descendente
                            system("cls");
                            listaDeOficinas.listarOficinasDescendente();
                            _getch();
                            break;
                        case 0: // Volver al Menu General
                            break;
                        default:
                            system("cls");
                            cout << "Opcion invalida." << endl;
                            _getch();
                    }
                } while (opcionOficina != 0);
                break;

            case 2: // Menu Empleados
                do {
                    system("cls");
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
                            system("cls");
                            cout << "Ingrese el codigo del nuevo empleado: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el nombre del nuevo empleado: ";
                            getline(cin >> ws, nombreEmpleado);
                            cout << "Ingrese el sueldo del nuevo empleado: ";
                            cin >> sueldoEmpleado;
                            cout << "Ingrese el codigo de la oficina para este empleado: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                if (!buscarEmpleado(oficinaActual, codigoEmpleado)) {
                                    insertarEmpleado(oficinaActual, codigoEmpleado, nombreEmpleado, sueldoEmpleado);
                                } else {
                                    cout << "Error: El codigo de empleado " << codigoEmpleado << " ya existe en esta oficina." << endl;
                                }
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            _getch();
                            break;
                        case 2: // Modificar Empleado
                            system("cls");
                            cout << "Ingrese el codigo del empleado a modificar: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el nuevo nombre del empleado: ";
                            getline(cin >> ws, nombreEmpleado);
                            cout << "Ingrese el nuevo sueldo del empleado: ";
                            cin >> nuevoSueldoEmpleado;
                            cout << "Ingrese el nuevo codigo del empleado: ";
                            cin >> nuevoCodigoEmpleado;
                            cout << "Ingrese el codigo de la oficina del empleado: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                modificarEmpleado(oficinaActual, codigoEmpleado, nombreEmpleado, nuevoSueldoEmpleado, nuevoCodigoEmpleado);
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            _getch();
                            break;
                        case 3: // Borrar Empleado
                            system("cls");
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
                            _getch();
                            break;
                        case 4: // Listar Empleados de una Oficina
                            system("cls");
                            cout << "Ingrese el codigo de la oficina para listar sus empleados: ";
                            cin >> codigoOficina;
                            oficinaActual = listaDeOficinas.buscarOficina(codigoOficina);
                            if (oficinaActual) {
                                listarEmpleados(oficinaActual);
                            } else {
                                cout << "Error: La oficina con codigo " << codigoOficina << " no existe." << endl;
                            }
                            _getch();
                            break;
                        case 0: // Volver al Menu General
                            break;
                        default:
                            system("cls");
                            cout << "Opcion invalida." << endl;
                            _getch();
                    }
                } while (opcionEmpleado != 0);
                break;

            case 3: // Menu Especial
                generarReporteEmpleadosMenorSueldo(listaDeOficinas);
                break;

            case 0: // Salir
                system("cls");
                cout << "Saliendo del programa." << endl;
                break;

            default:
                system("cls");
                cout << "Opcion invalida." << endl;
                _getch();
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