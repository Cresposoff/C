#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
    long long int codigo;
    string nombre;
    string ciudad;
    string direccion;
    string telefono;
    string correo;
    string documento;
};

const int MAX_ESTUDIANTES = 30;
Estudiante estudiantes[MAX_ESTUDIANTES];
int numEstudiantes = 0;

// Función para capturar datos de un estudiante
void capturarEstudiante() {
    if (numEstudiantes < MAX_ESTUDIANTES) {
        cout << "Ingrese el código del estudiante: ";
        cin >> estudiantes[numEstudiantes].codigo;
        cin.ignore();

        cout << "Ingrese el nombre del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].nombre);

        cout << "Ingrese la ciudad del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].ciudad);

        cout << "Ingrese la dirección del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].direccion);

        cout << "Ingrese el teléfono del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].telefono);

        cout << "Ingrese el correo del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].correo);

        cout << "Ingrese el documento de identidad del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].documento);

        numEstudiantes++;
        cout << "Estudiante agregado correctamente." << endl;
    } else {
        cout << "No se pueden agregar más estudiantes. El límite es " << MAX_ESTUDIANTES << "." << endl;
    }
}

// Función para modificar datos de un estudiante
void modificarEstudiante() {
    long long int codigo;
    cout << "Ingrese el código del estudiante que desea modificar: ";
    cin >> codigo;
    cin.ignore();

    for (int i = 0; i < numEstudiantes; ++i) {
        if (estudiantes[i].codigo == codigo) {
            cout << "Ingrese el nuevo nombre del estudiante: ";
            getline(cin, estudiantes[i].nombre);

            cout << "Ingrese la nueva ciudad del estudiante: ";
            getline(cin, estudiantes[i].ciudad);

            cout << "Ingrese la nueva dirección del estudiante: ";
            getline(cin, estudiantes[i].direccion);

            cout << "Ingrese el nuevo teléfono del estudiante: ";
            getline(cin, estudiantes[i].telefono);

            cout << "Ingrese el nuevo correo del estudiante: ";
            getline(cin, estudiantes[i].correo);

            cout << "Ingrese el nuevo documento de identidad del estudiante: ";
            getline(cin, estudiantes[i].documento);

            cout << "Estudiante modificado correctamente." << endl;
            return;
        }
    }

    cout << "No se encontró ningún estudiante con el código ingresado." << endl;
}

// Función para eliminar un estudiante
void eliminarEstudiante() {
    long long int codigo;
    cout << "Ingrese el código del estudiante que desea eliminar: ";
    cin >> codigo;
    cin.ignore();

    for (int i = 0; i < numEstudiantes; ++i) {
        if (estudiantes[i].codigo == codigo) {
            for (int j = i; j < numEstudiantes - 1; ++j) {
                estudiantes[j] = estudiantes[j + 1];
            }
            numEstudiantes--;
            cout << "Estudiante eliminado correctamente." << endl;
            return;
        }
    }

    cout << "No se encontró ningún estudiante con el código ingresado." << endl;
}

// Función para listar todos los estudiantes
void listarEstudiantes() {
    if (numEstudiantes == 0) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    cout << "Lista de estudiantes:" << endl;
    for (int i = 0; i < numEstudiantes; ++i) {
        cout << "Código: " << estudiantes[i].codigo << endl;
        cout << "Nombre: " << estudiantes[i].nombre << endl;
        cout << "Ciudad: " << estudiantes[i].ciudad << endl;
        cout << "Dirección: " << estudiantes[i].direccion << endl;
        cout << "Teléfono: " << estudiantes[i].telefono << endl;
        cout << "Correo: " << estudiantes[i].correo << endl;
        cout << "Documento: " << estudiantes[i].documento << endl;
        cout << "------------------------" << endl;
    }
}

// Función para ordenar estudiantes por código (método burbuja)
void ordenarPorCodigo() {
    for (int i = 0; i < numEstudiantes - 1; ++i) {
        for (int j = 0; j < numEstudiantes - i - 1; ++j) {
            if (estudiantes[j].codigo > estudiantes[j + 1].codigo) {
                Estudiante temp = estudiantes[j];
                estudiantes[j] = estudiantes[j + 1];
                estudiantes[j + 1] = temp;
            }
        }
    }
    cout << "Estudiantes ordenados por código." << endl;
}

// Función para ordenar estudiantes por ciudad y nombre (método burbuja)
void ordenarPorCiudadNombre() {
    for (int i = 0; i < numEstudiantes - 1; ++i) {
        for (int j = 0; j < numEstudiantes - i - 1; ++j) {
            if (estudiantes[j].ciudad > estudiantes[j + 1].ciudad ||
                (estudiantes[j].ciudad == estudiantes[j + 1].ciudad && estudiantes[j].nombre > estudiantes[j + 1].nombre)) {
                Estudiante temp = estudiantes[j];
                estudiantes[j] = estudiantes[j + 1];
                estudiantes[j + 1] = temp;
            }
        }
    }
    cout << "Estudiantes ordenados por ciudad y nombre." << endl;
}

int main() {
    int opcion;

    do {
        cout << "Menú:" << endl;
        cout << "1. Capturar estudiante" << endl;
        cout << "2. Modificar estudiante" << endl;
        cout << "3. Eliminar estudiante" << endl;
        cout << "4. Listar estudiantes" << endl;
        cout << "5. Ordenar por código" << endl;
        cout << "6. Ordenar por ciudad y nombre" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                capturarEstudiante();
                break;
            case 2:
                modificarEstudiante();
                break;
            case 3:
                eliminarEstudiante();
                break;
            case 4:
                listarEstudiantes();
                break;
            case 5:
                ordenarPorCodigo();
                break;
            case 6:
                ordenarPorCiudadNombre();
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
        }

        cout << endl;
    } while (opcion != 0);

    return 0;
}
