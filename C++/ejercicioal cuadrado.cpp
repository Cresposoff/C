#include <iostream>
#include <conio.h>

using namespace std;

void pedirDatos();
void alCuadrado(float x);

float num1;

int main(){
	pedirDatos();
	alCuadrado(num1);
	
	getch();
	return 0;
}

void pedirDatos(){
	cout << "Ingrese el valor que desea elevar al cuadrado: ";
	cin >> num1;
}

void alCuadrado(float x){
	float cuadrado = num1*num1;
	cout << "El cuadrado de " << num1 << " es: " << cuadrado;
}