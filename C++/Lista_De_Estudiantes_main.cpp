#include <iostream>
#include <string>
#include <iomanip> // Para que se vea más chévere al imprimir la lista

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

// Función para verificar si un código o documento ya existe
bool codigoODocumentoExiste(long long int codigo, string documento) {
    for (int i = 0; i < numEstudiantes; ++i) {
        if (estudiantes[i].codigo == codigo || estudiantes[i].documento == documento) {
            return true;
        }
    }
    return false;
}

// Función para capturar datos de un estudiante
void capturarEstudiante() {
    if (numEstudiantes < MAX_ESTUDIANTES) {
    	
    	// volví a daeclararlas para evitar conflictos
        long long int codigo;
        string documento;

        cout << "Ingrese el codigo del estudiante: ";
        cin >> codigo;
        cin.ignore();

        cout << "Ingrese el documento de identidad del estudiante: ";
        getline(cin, documento);

        if (codigoODocumentoExiste(codigo, documento)) {
            cout << "Error: El codigo o documento ya existe." << endl;
            return;
        }

        estudiantes[numEstudiantes].codigo = codigo;
        estudiantes[numEstudiantes].documento = documento;

        cout << "Ingrese el nombre del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].nombre);

        cout << "Ingrese la ciudad del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].ciudad);

        cout << "Ingrese la direccion del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].direccion);

        cout << "Ingrese el telefono del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].telefono);

        cout << "Ingrese el correo del estudiante: ";
        getline(cin, estudiantes[numEstudiantes].correo);

        numEstudiantes++;
        cout << "Estudiante agregado correctamente." << endl;
    } else {
        cout << "No se pueden agregar mas estudiantes. El limite es " << MAX_ESTUDIANTES << "." << endl;
    }
}

// funcion para modificar datos de un estudiante
void modificarEstudiante() {
    long long int codigo;
    cout << "Ingrese el codigo del estudiante que desea modificar: ";
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

            cout << "Ingrese el nuevo telefono del estudiante: ";
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

// funcion para eliminar o quitar un estudiante del arreglo
void eliminarEstudiante() {
    long long int codigo;
    cout << "Ingrese el codigo del estudiante que desea eliminar: ";
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

    cout << "No se encontro ningun estudiante con el codigo ingresado." << endl;
}

// Funcim para listar todos los estudiantes, acá usamos el iomanip para que se vea como una lista
void listarEstudiantes() {
    if (numEstudiantes == 0) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    cout << setw(15) << "Codigo" << setw(35) << "Nombre" << setw(20) << "Ciudad" << setw(30) << "Correo" << setw(20) << "Documento" << endl; // Aumentado el ancho del campo Nombre a 30
    cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < numEstudiantes; ++i) {
        cout << setw(15) << estudiantes[i].codigo
             << setw(35) << estudiantes[i].nombre
             << setw(20) << estudiantes[i].ciudad
             << setw(30) << estudiantes[i].correo
             << setw(20) << estudiantes[i].documento << endl;
    }
}

// funcion de ordenar estudiantes por codigo (con el método burbuja)
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
    cout << "Estudiantes ordenados por codigo:" << endl;
    listarEstudiantes(); // Mostrar la lista ordenada
}

// funcion de ordenar estudiantes por ciudad - nombre (con el mwtodo burbuja) y mostrar luego la lista ordenada
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
    cout << "Estudiantes ordenados por ciudad y nombre:" << endl;
    listarEstudiantes(); // Mostrar la lista ordenada
}

int main() {
    int opcion;

    do {
        cout << "MENU:" << endl;
        cout << "1. Capturar estudiante" << endl;
        cout << "2. Modificar estudiante" << endl;
        cout << "3. Eliminar estudiante" << endl;
        cout << "4. Listar estudiantes" << endl;
        cout << "5. Ordenar por codigo" << endl;
        cout << "6. Ordenar por ciudad y nombre" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
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
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }

        cout << endl;
    } while (opcion != 0);

    return 0;
}
