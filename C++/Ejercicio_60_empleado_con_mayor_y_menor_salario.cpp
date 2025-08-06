#include <iostream>
#include <conio.h>
#include <cstdlib> // contiene la funcion system("pause")

using namespace std;

struct atleta {

	char nombre[30];
	char pais[10];
	int numero_medallas;

} atleta[100];

int main () {
	
	int n_atletas, posM=0, posm=0;
	float mayor=0, menor=999999;

	cout << "numero de atletas: ";
	cin >> n_atletas;

	for (int i=0; i<n_atletas; i++) {
			
		cout << "\nAtleta " << i+1 << endl << "NOMBRE del atleta: ";
		cin.getline(atleta[i].nombre,30,'\n');

		cout << "PAIS del atleta: ";
		cin.getline(atleta[i].pais,10,'\n');

		cout << "MEDALLAS ganadas del atleta: ";
		cin >> atleta[i].numero_medallas;

		if (atleta[i].numero_medallas > mayor) {
			mayor = atleta[i].numero_medallas;
			posM = i;
		}
		if ( atleta[i].numero_medallas < menor) {
			menor = atleta[i].numero_medallas;
			posm = i;
		}

		cout << "\n";

	}

	cout << ".:MAYOR NUMERO DE MEDALLAS:." << "\nNombre: " << atleta[posM].nombre << "\nPais: " << atleta[posM].pais;

	cout << "\n\n.:MENOR NUMERO DE MEDALLAS:." << "\nNombre: " << atleta[posm].nombre << "\nPais: " << atleta[posm].pais;

	getch();
	return 0;
}