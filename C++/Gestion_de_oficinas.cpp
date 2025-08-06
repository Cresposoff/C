#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para los empleados
struct Empleado {
    int codigo;
    string nombre;
    Empleado* siguiente;
    Empleado* anterior;

    Empleado(int cod, string nom) : codigo(cod), nombre(nom), siguiente(nullptr), anterior(nullptr) {}
};

// Estructura para las oficinas (nodos de la lista circular doblemente enlazada)
struct Oficina {
    int codigo;
    string nombre;
    Oficina* siguiente;
    Oficina* anterior;
    Empleado* empleados; // Puntero al primer empleado de esta oficina

    Oficina(int cod, string nom) : codigo(cod), nombre(nom), siguiente(nullptr), anterior(nullptr), empleados(nullptr) {}
};

// Clase para la lista circular doblemente enlazada de oficinas
class ListaOficinas {
private:
    Oficina* cabeza;
    Oficina* cola;

public:
    ListaOficinas() : cabeza(nullptr), cola(nullptr) {}

    // Función para verificar si la lista de oficinas está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }

    // Función para buscar una oficina por su código
    Oficina* buscarOficina(int codigo) const {
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

    // Función para crear una nueva oficina
    void crearOficina(int codigo, string nombre) {
        if (buscarOficina(codigo)) {
            cout << "Error: Ya existe una oficina con el codigo " << codigo << endl;
            return;
        }
        Oficina* nuevaOficina = new Oficina(codigo, nombre);
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
        cout << "Oficina " << nombre << " (Codigo: " << codigo << ") creada." << endl;
    }

    // Función para modificar el nombre de una oficina existente
    void modificarOficina(int codigo, string nuevoNombre) {
        Oficina* oficina = buscarOficina(codigo);
        if (oficina) {
            oficina->nombre = nuevoNombre;
            cout << "Oficina con codigo " << codigo << " modificada a '" << nuevoNombre << "'." << endl;
        } else {
            cout << "Error: No existe una oficina con el codigo " << codigo << endl;
        }
    }

    // Función para borrar una oficina
    void borrarOficina(int codigo) {
        Oficina* oficina = buscarOficina(codigo);
        if (!oficina) {
            cout << "Error: No existe una oficina con el codigo " << codigo << endl;
            return;
        }

        if (oficina->empleados != nullptr) {
            cout << "Error: No se puede borrar la oficina '" << oficina->nombre << "' porque tiene empleados asignados." << endl;
            return;
        }

        if (oficina == cabeza && oficina == cola) {
            cabeza = nullptr;
            cola = nullptr;
        } else if (oficina == cabeza) {
            cabeza = cabeza->siguiente;
            cabeza->anterior = cola;
            cola->siguiente = cabeza;
        } else if (oficina == cola) {
            cola = cola->anterior;
            cola->siguiente = cabeza;
            cabeza->anterior = cola;
        } else {
            oficina->anterior->siguiente = oficina->siguiente;
            oficina->siguiente->anterior = oficina->anterior;
        }
        cout << "Oficina '" << oficina->nombre << "' (Codigo: " << codigo << ") borrada." << endl;
        delete oficina;
    }

    // Función para listar las oficinas en orden ascendente por código
    void listarOficinasAscendente() const {
        if (estaVacia()) {
            cout << "No hay oficinas creadas." << endl;
            return;
        }
        vector<Oficina*> oficinas;
        Oficina* actual = cabeza;
        do {
            oficinas.push_back(actual);
            actual = actual->siguiente;
        } while (actual != cabeza);

        sort(oficinas.begin(), oficinas.end(), [](const Oficina* a, const Oficina* b) {
            return a->codigo < b->codigo;
        });

        cout << "\nListado de oficinas (ascendente por codigo):\n";
        for (const auto& oficina : oficinas) {
            cout << "Código: " << oficina->codigo << ", Nombre: " << oficina->nombre << endl;
        }
    }

    // Función para listar las oficinas en orden descendente por código
    void listarOficinasDescendente() const {
        if (estaVacia()) {
            cout << "No hay oficinas creadas." << endl;
            return;
        }
        vector<Oficina*> oficinas;
        Oficina* actual = cabeza;
        do {
            oficinas.push_back(actual);
            actual = actual->siguiente;
        } while (actual != cabeza);

        sort(oficinas.begin(), oficinas.end(), [](const Oficina* a, const Oficina* b) {
            return a->codigo > b->codigo;
        });

        cout << "\nListado de oficinas (descendente por codigo):\n";
        for (const auto& oficina : oficinas) {
            cout << "Codigo: " << oficina->codigo << ", Nombre: " << oficina->nombre << endl;
        }
    }

    // --- Métodos para la gestión de empleados dentro de una oficina ---

    // Función para buscar un empleado por código dentro de una oficina
    Empleado* buscarEmpleado(Oficina* oficina, int codigo) const {
        if (!oficina || !oficina->empleados) {
            return nullptr;
        }
        Empleado* actual = oficina->empleados;
        while (actual) {
            if (actual->codigo == codigo) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Función para crear un empleado en una oficina, manteniendo el orden ascendente por código
    void crearEmpleado(int codigoOficina, int codigoEmpleado, string nombreEmpleado) {
        Oficina* oficina = buscarOficina(codigoOficina);
        if (!oficina) {
            cout << "Error: No existe la dependencia con codigo " << codigoOficina << endl;
            return;
        }

        if (buscarEmpleado(oficina, codigoEmpleado)) {
            cout << "Error: Ya existe un empleado con el codigo " << codigoEmpleado << " en la oficina '" << oficina->nombre << "'." << endl;
            return;
        }

        Empleado* nuevoEmpleado = new Empleado(codigoEmpleado, nombreEmpleado);
        if (!oficina->empleados) {
            oficina->empleados = nuevoEmpleado;
        } else if (codigoEmpleado < oficina->empleados->codigo) {
            nuevoEmpleado->siguiente = oficina->empleados;
            oficina->empleados->anterior = nuevoEmpleado;
            oficina->empleados = nuevoEmpleado;
        } else {
            Empleado* actual = oficina->empleados;
            while (actual->siguiente && actual->siguiente->codigo < codigoEmpleado) {
                actual = actual->siguiente;
            }
            nuevoEmpleado->siguiente = actual->siguiente;
            nuevoEmpleado->anterior = actual;
            if (actual->siguiente) {
                actual->siguiente->anterior = nuevoEmpleado;
            }
            actual->siguiente = nuevoEmpleado;
        }
        cout << "Empleado '" << nombreEmpleado << "' (Codigo: " << codigoEmpleado << ") creado en la oficina '" << oficina->nombre << "'." << endl;
    }

    // Función para modificar un empleado existente en una oficina
    void modificarEmpleado(int codigoOficina, int codigoEmpleado, string nuevoNombre) {
        Oficina* oficina = buscarOficina(codigoOficina);
        if (!oficina) {
            cout << "Error: No existe la dependencia con codigo " << codigoOficina << endl;
            return;
        }
        Empleado* empleado = buscarEmpleado(oficina, codigoEmpleado);
        if (empleado) {
            empleado->nombre = nuevoNombre;
            cout << "Empleado con codigo " << codigoEmpleado << " en la oficina '" << oficina->nombre << "' modificado a '" << nuevoNombre << "'." << endl;
        } else {
            cout << "Error: No existe un empleado con el codigo " << codigoEmpleado << " en la oficina '" << oficina->nombre << "'." << endl;
        }
    }

    // Función para borrar un empleado de una oficina
    void borrarEmpleado(int codigoOficina, int codigoEmpleado) {
        Oficina* oficina = buscarOficina(codigoOficina);
        if (!oficina) {
            cout << "Error: No existe la dependencia con codigo " << codigoOficina << endl;
            return;
        }
        Empleado* empleado = buscarEmpleado(oficina, codigoEmpleado);
        if (!empleado) {
            cout << "Error: No existe un empleado con el codigo " << codigoEmpleado << " en la oficina '" << oficina->nombre << "'." << endl;
            return;
        }

        if (empleado == oficina->empleados) {
            oficina->empleados = empleado->siguiente;
            if (oficina->empleados) {
                oficina->empleados->anterior = nullptr;
            }
        } else {
            empleado->anterior->siguiente = empleado->siguiente;
            if (empleado->siguiente) {
                empleado->siguiente->anterior = empleado->anterior;
            }
        }
        cout << "Empleado con codigo " << codigoEmpleado << " borrado de la oficina '" << oficina->nombre << "'." << endl;
        delete empleado;
    }

    // Función para listar los empleados de una oficina
    void listarEmpleados(int codigoOficina) const {
        Oficina* oficina = buscarOficina(codigoOficina);
        if (!oficina) {
            cout << "Error: No existe la dependencia con codigo " << codigoOficina << endl;
            return;
        }
        if (!oficina->empleados) {
            cout << "La oficina '" << oficina->nombre << "' no tiene empleados." << endl;
            return;
        }
        cout << "\nListado de empleados de la oficina '" << oficina->nombre << "':\n";
        Empleado* actual = oficina->empleados;
        while (actual) {
            cout << "Codigo: " << actual->codigo << ", Nombre: " << actual->nombre << endl;
            actual = actual->siguiente;
        }
    }

    // Destructor para liberar la memoria de las oficinas y sus empleados
    ~ListaOficinas() {
        if (!estaVacia()) {
            Oficina* actual = cabeza->siguiente;
            while (actual != cabeza) {
                Empleado* empleadoActual = actual->empleados;
                while (empleadoActual) {
                    Empleado* tempEmpleado = empleadoActual;
                    empleadoActual = empleadoActual->siguiente;
                    delete tempEmpleado;
                }
                Oficina* tempOficina = actual;
                actual = actual->siguiente;
                delete tempOficina;
            }
            Empleado* empleadoCabeza = cabeza->empleados;
            while (empleadoCabeza) {
                Empleado* tempEmpleado = empleadoCabeza;
                empleadoCabeza = empleadoCabeza->siguiente;
                delete tempEmpleado;
            }
            delete cabeza;
        }
    }
};

// Función principal del programa
int main() {
    ListaOficinas listaOficinas;

    // Crear las 3 oficinas iniciales
    listaOficinas.crearOficina(100, "Gerencia");
    listaOficinas.crearOficina(200, "Contabilidad");
    listaOficinas.crearOficina(300, "Practicas");

    int opcionGeneral, opcionDependencia, opcionEmpleado;

    do {
        cout << "\n--- Menu General ---" << endl;
        cout << "1. Dependencias" << endl;
        cout << "2. Empleados" << endl;
        cout << "3. Menu Especial (Salir)" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionGeneral;

        switch (opcionGeneral) {
            case 1: // Menú Dependencias
                do {
                    cout << "\n--- Menu Dependencias ---" << endl;
                    cout << "1. Crear Dependencia" << endl;
                    cout << "2. Modificar Dependencia" << endl;
                    cout << "3. Borrar Dependencia" << endl;
                    cout << "4. Listar Dependencias (Ascendente por Codigo)" << endl;
                    cout << "5. Listar Dependencias (Descendente por Codigo)" << endl;
                    cout << "6. Volver al Menu General" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> opcionDependencia;

                    switch (opcionDependencia) {
                        case 1: {
                            int codigo;
                            string nombre;
                            cout << "Ingrese el codigo de la nueva dependencia: ";
                            cin >> codigo;
                            cout << "Ingrese el nombre de la nueva dependencia: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del teclado
                            getline(cin, nombre);
                            listaOficinas.crearOficina(codigo, nombre);
                            break;
                        }
                        case 2: {
                            int codigo;
                            string nuevoNombre;
                            cout << "Ingrese el codigo de la dependencia a modificar: ";
                            cin >> codigo;
                            cout << "Ingrese el nuevo nombre de la dependencia: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del teclado
                            getline(cin, nuevoNombre);
                            listaOficinas.modificarOficina(codigo, nuevoNombre);
                            break;
                        }
                        case 3: {
                            int codigo;
                            cout << "Ingrese el codigo de la dependencia a borrar: ";
                            cin >> codigo;
                            listaOficinas.borrarOficina(codigo);
                            break;
                        }
                        case 4:
                            listaOficinas.listarOficinasAscendente();
                            break;
                        case 5:
                            listaOficinas.listarOficinasDescendente();
                            break;
                        case 6:
                            cout << "Volviendo al Menu General..." << endl;
                            break;
                        default:
                            cout << "Opcion invalida. Intente de nuevo." << endl;
                    }
                } while (opcionDependencia != 6);
                break;

            case 2: // Menú Empleados
                do {
                    cout << "\n--- Menu Empleados ---" << endl;
                    cout << "1. Crear Empleado" << endl;
                    cout << "2. Modificar Empleado" << endl;
                    cout << "3. Borrar Empleado" << endl;
                    cout << "4. Listar Empleados por Dependencia" << endl;
                    cout << "5. Volver al Menu General" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> opcionEmpleado;

                    switch (opcionEmpleado) {
                        case 1: {
                            int codigoDependencia, codigoEmpleado;
                            string nombreEmpleado;
                            cout << "Ingrese el codigo de la dependencia para el nuevo empleado: ";
                            cin >> codigoDependencia;
                            cout << "Ingrese el codigo del nuevo empleado: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el nombre del nuevo empleado: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
                            getline(cin, nombreEmpleado);
                            listaOficinas.crearEmpleado(codigoDependencia, codigoEmpleado, nombreEmpleado);
                            break;
                        }
                        case 2: {
                            int codigoDependencia, codigoEmpleado;
                            string nuevoNombreEmpleado;
                            cout << "Ingrese el codigo de la dependencia del empleado a modificar: ";
                            cin >> codigoDependencia;
                            cout << "Ingrese el codigo del empleado a modificar: ";
                            cin >> codigoEmpleado;
                            cout << "Ingrese el nuevo nombre del empleado: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
                            getline(cin, nuevoNombreEmpleado);
                            listaOficinas.modificarEmpleado(codigoDependencia, codigoEmpleado, nuevoNombreEmpleado);
                            break;
                        }
                        case 3: {
                            int codigoDependencia, codigoEmpleado;
                            cout << "Ingrese el codigo de la dependencia del empleado a borrar: ";
                            cin >> codigoDependencia;
                            cout << "Ingrese el codigo del empleado a borrar: ";
                            cin >> codigoEmpleado;
                            listaOficinas.borrarEmpleado(codigoDependencia, codigoEmpleado);
                            break;
                        }
                        case 4: {
                            int codigoDependencia;
                            cout << "Ingrese el codigo de la dependencia para listar sus empleados: ";
                            cin >> codigoDependencia;
                            listaOficinas.listarEmpleados(codigoDependencia);
                            break;
                        }
                        case 5:
                            cout << "Volviendo al Menu General..." << endl;
                            break;
                        default:
                            cout << "Opción invalida. Intente de nuevo." << endl;
                    }
                } while (opcionEmpleado != 5);
                break;

            case 3: // Menú Especial (Salir)
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcionGeneral != 3);

    return 0;
}

