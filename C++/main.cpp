#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {

int numero = 10;
int *ptr = &numero; // ptr almacena la direcci�n de memoria de numero

cout << "Valor de numero: " << numero << endl;
cout << "Direcci�n de numero: " << &numero << endl;
cout << "Valor apuntado por ptr: " << *ptr << endl;
}
