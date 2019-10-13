#include "CList.h"

int main(){
	CList_PTR2<int> lista;
	cout << "PARCIAL CCOMP 4-1" << endl;
	cout << "Alumno: Italo Mamani Huaricallo" << endl; //Ingrese 1,2 o 3 para hacer una accion determinada dada en la lista a continuacion, los datos son leidos 1 por 1 asi que tendra que hacerlo 1 por vez
	cout << "Lista de Listas\n" << endl;
	cout << "\t1. Insertar" << endl;
	cout << "\t2. Imprimir Lista" << endl;
	cout << "\t3. Salir" << endl;
	while (true) {
		int op; cout << "Que quiere hacer?: "; cin >> op;
		if (op == 1) {
			int data;
			cout << "Ingrese nuevo dato: "; cin >> data;
			lista.AddNewNode(data);
			cout << "\tNODO INGRESADO" << endl;
		}
		if (op == 2) {
			lista.PrintList();
		}
		if (op == 3) {
			break;
		}
	}
	return 0;
}
