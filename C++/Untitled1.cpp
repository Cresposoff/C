#include <iostream>
using namespace std;
int main() {

	int * int_ptr=new int;
	*int_ptr=10;
	cout << "Valor antes de delete: " << *int_ptr << endl;
	delete int_ptr; // Liberando memoria
	cout << int_ptr << endl;
	int_ptr = nullptr; // Buena práctica para evitar puntero colgante.
}