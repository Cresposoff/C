// librerias
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct lista {
	int codigo;
	string nombre;
	lista *der;  // variable derdor enlace
	lista *izq;
};
// variables de la lista
lista *cola, *cab, *nuevo, *bus1, *bus2;
//funciones
void menu(void);
void ingresar(void);
void mostrar_cab(void);
void mostrar_cola(void);
void sacar_cab(void);
void sacar_cola(void);
void modificar_cab(void);
void modificar_cola(void);
main() {
	menu();
}
void menu(void) {
	int y, opc;
	opc = 9;
	while ( opc != 0) {
		system("cls");
		cout<<"\n 1 Ingresar Datos";
		cout<<"\n 2 Sacar Datos cab";
		cout<<"\n 3 Sacar Datos cola";
		cout<<"\n 4 Mostrar Datos cab";
		cout<<"\n 5 Mostrar Datos cola";
		cout<<"\n 6 Modificar Datos cab";
		cout<<"\n 7 Modificar Datos cola";
		cout<<"\n 0 Terminar";
		cout<<"\n Ingrese Opcion: ";
		cin>>opc;

		switch(opc) {
			case 1:
				ingresar();
				break;
			case 2:
				sacar_cab();
				break;
			case 3:
				sacar_cola();
				break;
			case 4:
				mostrar_cab();
				break;
			case 5:
				mostrar_cola();
				break;
			case 6:
				modificar_cab();
				break;
			case 7:
				modificar_cola();
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
	cout<<"Ingresa el nombre : ";
	//cin >> cab->nombre;
	getline(cin,nuevo->nombre);
	cout<<"\n\n";
	fflush(stdin);
	nuevo->der = NULL;
	nuevo->izq = NULL;
	if ( !cab ) {
		cab = new(lista);
		cola = new(lista);

		cab = nuevo;
		cola = nuevo;
	} else {
		if (nuevo->codigo >= cola->codigo) {
			nuevo->izq = cola;
			cola->der = nuevo;
			cola = nuevo;
		} else {
			if (nuevo->codigo <= cab->codigo) {
				nuevo->der = cab;
				cola->izq = nuevo;
				cab = nuevo;
			} else {
				bus1 = new(lista);
				bus2 = new(lista);

				bus1 = cab;
				bus2 = bus1->der;
				existe = 0;
				while (existe == 0) {
					if (nuevo->codigo <= bus2->codigo) {
						nuevo->izq = bus1;
						nuevo->der = bus2;
						bus1->der = nuevo;
						bus2->izq = nuevo;
						existe = 8;
					} else {
						bus1 = bus1->der;
						bus2 = bus2->izq;
					}
				}
			}
		}
	}
	nuevo->der = NULL;  /// la estructura Nuevo esta derndo al Final o vacio
	nuevo->izq = NULL;
	//cola->der = nuevo;  /// el ultimo nodo de la lista se une al NUEVO
	nuevo->der 	= cab;
	cab->izq	= nuevo;
	cab = nuevo;  /// la variable cab toma la posicion de Nuevo
}
void sacar_cab(void) { // o borrar
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Sacar ";
		return;
	}
	nuevo = new(lista);
	nuevo = cola;
	cout <<"\n\n Elemento Eliminado: "<<nuevo->codigo;
	cout <<"\n Nombre : "<<nuevo->nombre;
	cab = nuevo->izq;
	//cab = cab->der;   es igual al cab = nuevo->der
	delete(nuevo);
}
void sacar_cola(void) { // o borrar
	if ( !cab ) {
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
void mostrar_cab(void) { // o  listar
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Mostrar ";
		return;
	}
	nuevo = new(lista);
	nuevo = cab;

	while ( nuevo != NULL  ) {
		cout <<"\n\n Elemento : "<<nuevo->codigo;
		cout <<"\n Nombre : "<<nuevo->nombre;
		nuevo = nuevo->der;  // avanzar en la lista
	}
}
void mostrar_cola(void) { // o  listar
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Mostrar ";
		return;
	}
	nuevo = new(lista);
	nuevo = cola;
	while ( nuevo != NULL  ) {
		cout <<"\n\n Elemento : "<<nuevo->codigo;
		cout <<"\n Nombre : "<<nuevo->nombre;
		nuevo = nuevo->izq;  // avanzar en la lista
	}
}
void modificar_cab(void) {
	int encontro;
	int codigo_buscar;
	encontro = 0;
	if ( !cab ) {
		cout <<"\n\n No hay Elementos Para Modificar";
		return;
	}
	nuevo = new(lista);
	nuevo = cola;
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
			nuevo = nuevo->izq;  // avanzar en la lista
	}
	if (encontro == 0) {
		cout <<"\n\n No Existe Elementos Para Modificar";
	}
}
void modificar_cola(void) {
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