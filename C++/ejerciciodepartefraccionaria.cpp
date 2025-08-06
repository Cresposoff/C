#include <iostream>
#include <conio.h>

using namespace std;

void pedirDatos();
void parteFraccionaria(double);

double num;

int main() {
	
	pedirDatos();
	parteFraccionaria(num);
	
	getch();
	return 0;
	
}

void pedirDatos() {
	cout << "Ingrese el numero para sacar la parte fraccionaria: ";
	cin >> num;
}

void parteFraccionaria(double x) {
	long parteEntera = x;
	double parteFraccionaria = x - parteEntera;
	
	cout << "La parte fraccionaria es: " << parteFraccionaria;
}
