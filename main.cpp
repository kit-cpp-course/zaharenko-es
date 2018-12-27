#include <string>
#include <iostream>
#include <exception>
#include <windows.h>
#include "space.h"
#include "params.h"

using namespace std;
using namespace spaces;

int main(int argc,char ** argv) {
	setlocale(LC_ALL, "rus");

	params pars(argc, argv);

	if (pars.isRightInput())
	{
		cout << "Поиск наикратчайшего пути в двумерном дискретном пространстве" << endl;
		Space S1(pars.getStringArg());
		S1.getSpace();

		if (S1.setStart(pars.getIntegerArg(2), pars.getIntegerArg(3)) && S1.setFinish(pars.getIntegerArg(4), pars.getIntegerArg(5))) {
			LeeAlgorithm L;
			PathAcquisition * paths[] = { &L };
			
			cout << "Попытка найти кратчайший путь..." << endl;

			if (paths[0]->findPath(S)) {
				cout << "Поиск завершен успешно!" << endl;
			}
			else {
				cout << "Невозможно найти кратчайший путь!" << endl;
			}
		}
		else cout << "Выход точки за границу массива, поиск невозможен." << endl;

	}

	system("pause");

}

