#include<iostream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct lista
{
    int codigo;
    string nombre;
    lista *der;
    lista *izq;
};

lista *cola, *cab, *nuevo, *bus1, *bus2;

void menu(void);
void ingresar(void);
void mostrar_cab(void);
void mostrar_cola(void);
void sacar(void);
void modificar(void);

main()
{
    menu();
}

void menu(void)
{
    int y, opc;
    opc = 9;
    while (opc != 0)
    {
        system("cls");
        cout << "\n 1 Ingresar Datos";
        cout << "\n 2 Sacar Datos";
        cout << "\n 3 Mostrar Datos cab";
        cout << "\n 4 Mostrar Datos cola";
        cout << "\n 5 Modificar Datos";
        cout << "\n 0 Terminar";
        cout << "\n Ingrese Opcion";
        cin >> opc;

        switch (opc)
        {
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
            cout << "\n Opcion no Valida !! ";
            break;
        }
        cout << "\n\n Oprima una tecla para continuar";
        getch();
    }
}

void ingresar(void)
{
    int existe;
    nuevo = new(lista);
    cout << "\n Ingrese un Codigo: ";
    cin >> nuevo->codigo;
    fflush(stdin);

    cout << "Ingresa el nombre : ";
    getline(cin, nuevo->nombre);
    cout << "\n\n";
    fflush(stdin);

    nuevo->der = NULL;
    nuevo->izq = NULL;

    if (!cab)
    {
        cab = new(lista);
        cola = new(lista);
        cab = nuevo;
        cola = nuevo;
    }
    else
    {
        if (nuevo->codigo >= cola->codigo)
        {
            nuevo->izq = cola;
            cola->der = nuevo;
            cola = nuevo;
        }
        else
        {
            if (nuevo->codigo <= cab->codigo)
            {
                nuevo->der = cab;
                cab->izq = nuevo;
                cab = nuevo;
            }
            else
            {
                bus1 = new(lista);
                bus2 = new(lista);
                bus1 = cab;
                bus2 = bus1->der;
                existe = 0;
                while (existe == 0)
                {
                    if (nuevo->codigo <= bus2->codigo)
                    {
                        nuevo->izq = bus1;
                        nuevo->der = bus2;
                        bus1->der = nuevo;
                        bus2->izq = nuevo;
                        existe = 8;
                    }
                    else
                    {
                        bus1 = bus1->der;
                        bus2 = bus2->der;
                    }
                }

            }
        }
    }
}

void sacar(void)
{
    if (!cab)
    {
        cout << "\n\n No hay Elementos Para Sacar ";
        return;
    }

    int codigo_eliminar;
    cout << "\n Ingrese el codigo del estudiante a eliminar: ";
    cin >> codigo_eliminar;

    bus1 = cab;
    while (bus1 != NULL)
    {
        if (bus1->codigo == codigo_eliminar)
        {
            if (bus1 == cab) // Si es el primer nodo
            {
                cab = bus1->der;
                if (cab != NULL)
                {
                    cab->izq = NULL;
                }
            }
            else if (bus1 == cola) // Si es el último nodo
            {
                cola = bus1->izq;
                cola->der = NULL;
            }
            else // Si está en medio de la lista
            {
                bus1->izq->der = bus1->der;
                bus1->der->izq = bus1->izq;
            }

            cout << "\n Elemento Eliminado: " << bus1->codigo;
            cout << "\n Nombre: " << bus1->nombre;
            delete bus1;
            return;
        }
        bus1 = bus1->der;
    }

    cout << "\n No se encontro un estudiante con el codigo: " << codigo_eliminar;
}

void mostrar_cab(void)
{
    if (!cab)
    {
        cout << "\n\n No hay Elementos Para Mostrar ";
        return;
    }
    nuevo = new(lista);
    nuevo = cab;

    while (nuevo != NULL)
    {
        cout << "\n\n Elemento : " << nuevo->codigo;
        cout << "\n Nombre : " << nuevo->nombre;

        nuevo = nuevo->der;
    }
}

void mostrar_cola(void)
{
    if (!cab)
    {
        cout << "\n\n No hay Elementos Para Mostrar ";
        return;
    }
    nuevo = new(lista);
    nuevo = cola;

    while (nuevo != NULL)
    {
        cout << "\n\n Elemento : " << nuevo->codigo;
        cout << "\n Nombre : " << nuevo->nombre;

        nuevo = nuevo->izq;
    }
}
void modificar(void)
{
    int encontro;
    int codigo_buscar;
    encontro = 0;
    if (!cab)
    {
        cout << "\n\n No hay Elementos Para Modificar";
        return;
    }
    nuevo = new(lista);
    nuevo = cab;
    cout << "\n Digite un codigo a modificar : ";
    cin >> codigo_buscar;
    while (nuevo != NULL && encontro == 0)
    {
        if (nuevo->codigo == codigo_buscar)
        {
            cout << "\n\n Elemento : " << nuevo->codigo;
            cout << "\n Nombre : " << nuevo->nombre;
            cout << "\n Ingrese un codigo : ";
            cin >> nuevo->codigo;
            fflush(stdin);
            cout << "Ingresa el nombre : ";
            getline(cin, nuevo->nombre);
            encontro = 1;
        }
        else
            nuevo = nuevo->der;
    }
    if (encontro == 0)
    {
        cout << "\n\n No Existe Elementos Para Modificar";
    }
}
