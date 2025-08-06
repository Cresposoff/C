// librerias
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct lista {
	int codigo;
	string nombre;
	string departamento;
	string municipio;
	lista *der; // siguiente
	lista *izq; // anterior
};

// variables de la lista
lista *cola, *cab, *nuevo, *bus1, *bus2;

//funciones menu
void menu(void);
void ingresar(void);
void mostrar_cab(void);
void mostrar_cola(void);
void sacar(void);
void modificar(void);

main() {
	menu();
}

void menu(void) {
	int y, opc;
	opc = 9;
	while ( opc != 0) {
		system("cls");
		cout<<"\n 1 Ingresar Datos";
		cout<<"\n 2 Sacar Datos";
		cout<<"\n 3 Mostrar Datos cab";
		cout<<"\n 4 Mostrar Datos cola";
		cout<<"\n 5 Modificar Datos";
		cout<<"\n 0 Terminar";
		cout<<"\n\n OPCION: ";
		cin>>opc;

		switch(opc) {
			case 1:
				ingresar();
				break;
			case 2:
				sacar();
				break;
			case 3:
				mostrar_cola();
				break;
			case 4:
				mostrar_cab();
				break;
			case 5:
				modificar();
				break;
			default:
				cout <<"\n Opcion no Valida !! ";
				break;
		}
		cout <<"\n\n Oprima una tecla para continuar";
		getch();
	}
}

void ingresar(void) {
	int existe;
	nuevo = new(lista);
	cout <<"\n Ingrese un Codigo: ";
	cin >>nuevo->codigo;
	fflush(stdin);

	cout<<"Ingresa el nombre: ";
	//cin >> cab->nombre;
	getline(cin,nuevo->nombre);
	cout<<"\n";

	cout<<"Ingresa el departamento: ";
	getline(cin,nuevo->departamento);
	cout<<"\n";

	cout<<"Ingresa el municipio: ";
	getline(cin,nuevo->municipio);
	cout<<"\n";

	fflush(stdin);

	nuevo->der = nuevo;
	nuevo->izq = nuevo;

	if ( !cab ) {
		cab = new(lista);
		cola = new(lista);
		cab = nuevo;
		cola = nuevo;
	} else {
		if ( nuevo->codigo >= cola->codigo ) {
			nuevo->izq = cola;
			cola->der  = nuevo;
			cola       = nuevo;
			cola->der = cab;
			cab->izq = cola;
		} else {
			if ( nuevo->codigo <= cab->codigo ) {
				nuevo->der = cab;
				cab->izq   = nuevo;
				cab        = nuevo;
				cab->izq = cola;
				cola->der = cab;
			} else {
				bus1 = new(lista);
				bus2 = new(lista);
				bus1 = cab;
				bus2 = bus1->der;
				existe = 0;
				while ( existe == 0 ) {
					if ( nuevo->codigo <= bus2->codigo ) {
						nuevo->izq = bus1;
						nuevo->der = bus2;
						bus1->der  = nuevo;
						bus2->izq  = nuevo;
						existe = 8;
					} else {
						bus1  = bus1->der;
						bus2  = bus2->der;
					}
				}

			}
		}
	}
}

/*void ingresar(void)
{
	if ( !cab )
	{
		cab = new(lista);
		cout <<"\n Ingrese un codigo : ";
		cin >>cab->codigo;
        fflush(stdin);    //esta funcion libera la memoria

		cout<<"Ingresa el nombre : ";
		//cin >> cab->nombre;
		getline(cin,cab->nombre);        //"juan alberto ramires"
              // cin >> nombre           juan alberto ramirez
              //  realmente almacena es  "juan"

        cout<<"\n\n";
        fflush(stdin);

		cab->der = NULL;
		cab->izq = NULL;

		cola = new(lista);
		cola = cab;
		return;
	}
	nuevo = new(lista);
	cout <<"\n Ingrese un Codigo: ";
	cin >>nuevo->codigo;
	fflush(stdin);

    cout<<"Ingresa el nombre : ";
    //cin >> cab->nombre;
    getline(cin,nuevo->nombre);
    cout<<"\n\n";
    fflush(stdin);

	nuevo->der = NULL;  /// la estructura Nuevo esta derndo al Final o vacio
	nuevo->izq = NULL;
	//cola->der = nuevo;  /// el ultimo nodo de la lista se une al NUEVO

	nuevo->der 	= cab;
	cab->izq	= nuevo;
	cab = nuevo;  /// la variable cab toma la posicion de Nuevo
}*/

/*
void sacar(void)   // o borrar
{
	if ( !cab )
	{
		cout <<"\n\n No hay Elementos Para Sacar ";
		return;
	}
	nuevo = new(lista);
	nuevo = cab;
	cout <<"\n\n Elemento Eliminado: "<<nuevo->codigo;
	cout <<"\n Nombre : "<<nuevo->nombre;

	cab = nuevo->der;
	//cab = cab->der;   es igual al cab = nuevo->der

	delete(nuevo);
}
*/

void sacar(void) {

	string departamento_buscar;
	string municipio_buscar;

	int encontro = 0;
	if (!cab) {
		cout<<"\nno hay elementos en la lista. ";
		return;
	}
	nuevo = new(lista);
	nuevo = cab;

	fflush(stdin);
	cout << "\n Digite un Departamento a sacar : ";
	getline(cin,departamento_buscar);

	cout << "\n Digite un Municipio a sacar : ";
	getline(cin,municipio_buscar);


	while (nuevo != NULL) {
		if (nuevo->departamento == departamento_buscar && nuevo->municipio == municipio_buscar) {
			lista* temp = nuevo;
			nuevo = nuevo->der;

			if (temp->izq != NULL) {
				temp->izq->der = temp->der;
			} else {
				// Si es la cabeza
				cab = temp->der;
			}

			if (temp->der != NULL) {
				temp->der->izq = temp->izq;
			} else {
				// Si es la cola
				cola = temp->izq;
			}

			cout <<"\n\n Elemento Eliminado: "<<nuevo->codigo;
			cout <<"\n Nombre : "<<nuevo->nombre;
			cout <<"\n Departamento : "<<nuevo->departamento;
			cout <<"\n Muncicipio : "<<nuevo->municipio;

			delete (temp);
			nuevo = nuevo->der;
			sacar();
			encontro = 1;

		}
	}
	if (encontro == 0) {
		cout <<"\n\n No Existe Elementos Para Modificar";
	}
}

void mostrar_cab(void) { // o  listar
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Mostrar ";
		return;
	}
	nuevo = new(lista);
	nuevo = cab;

	do {
		cout <<"\n\n Elemento : "<<nuevo->codigo;
		cout <<"\n Nombre : "<<nuevo->nombre;
		cout <<"\n Departamento : "<<nuevo->departamento;
		cout <<"\n Muncicipio : "<<nuevo->municipio;

		nuevo = nuevo->der;  // avanzar en la lista
	} while ( nuevo != cab );
}

void mostrar_cola(void) { // o  listar
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Mostrar ";
		return;
	}
	nuevo = new(lista);
	nuevo = cola;

	do {
		cout <<"\n\n Elemento : "<<nuevo->codigo;
		cout <<"\n Nombre : "<<nuevo->nombre;
		cout <<"\n Departamento : "<<nuevo->departamento;
		cout <<"\n Muncicipio : "<<nuevo->municipio;

		nuevo = nuevo->izq;  // avanzar en la lista
	} while ( nuevo != cola );
}
void modificar(void) {
	int encontro;
	int codigo_buscar;
	encontro = 0;
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Modificar";
		return;
	}
	nuevo = new(lista);
	nuevo = cab;
	cout << "\n Digite un codigo a modificar : ";
	cin >> codigo_buscar;
	while (nuevo != NULL && encontro == 0) {
		if (nuevo->codigo == codigo_buscar) {
			cout <<"\n\n Elemento : "<<nuevo->codigo;
			cout <<"\n Nombre : "<<nuevo->nombre;
			cout <<"\n Ingrese un codigo : ";
			cin >>nuevo->codigo;
			fflush(stdin);
			cout<<"Ingresa el nombre : ";
			getline(cin,nuevo->nombre);
			encontro = 1;
		} else
			nuevo = nuevo->der;  // avanzar en la lista
	}
	if (encontro == 0) {
		cout <<"\n\n No Existe Elementos Para Modificar";
	}
}
