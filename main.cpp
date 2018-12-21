#include <string>
#include <iostream>
#include <exception>
#include <windows.h>
#include "point.h"
#include "space.h"

using namespace std;
using namespace spaces;

int main() {

	setlocale(LC_ALL, "rus");

	bool check = false;
	string f, answer;
	int t1_X, t1_Y, t2_X, t2_Y;

	cout << "Поиск наикратчайшего пути в двумерном дискретном пространстве" << endl;
	while (!check) {
		system("color 70");
		try {
			cout << "Введите имя файла (например, test.txt):" << endl;
			cin >> f;
			Space S1(f);
			S1.getSpace();
			cout << "Введите координату Х точки старта (число от 0 до " << S1.getColumns() - 1 << "):" << endl;
			cin >> t1_X;
			if (t1_X < 0 || t1_X >= S1.getColumns()) {
				throw exception("Недопустимое значение");
			}
			cout << "Введите координату Y точки старта (число от 0 до " << S1.getRows() - 1 << "):" << endl;
			cin >> t1_Y;
			if (t1_Y < 0 || t1_Y >= S1.getRows()) {
				throw exception("Недопустимое значение");
			}
			cout << "Введите координату Х конечной точки (число от 0 до " << S1.getColumns() - 1 << "):" << endl;
			cin >> t2_X;
			if (t2_X < 0 || t2_X >= S1.getColumns()) {
				throw exception("Недопустимое значение");
			}
			cout << "Введите координату Y конечной точки (число от 0 до " << S1.getRows() - 1 << "):" << endl;
			cin >> t2_Y;
			if (t2_Y < 0 || t2_Y >= S1.getRows()) {
				throw exception("Недопустимое значение");
			}
			check = true;

			S1.setStart(t1_X, t1_Y);
			S1.setFinish(t2_X, t2_Y);

			cout << "Попытка найти кратчайший путь..." << endl;
			if (lee(S1)) {
				cout << "Поиск завершен успешно!" << endl;
			}
			else {
				cout << "Невозможно найти кратчайший путь!" << endl;
			}

			cout << "Продолжим? (yes/no)" << endl;
			cin >> answer;
			if (answer == "yes") {
				check = false;
			}


		}
		catch (const exception & ex) {
			cout << ex.what() << endl;
		}

	}
	system("pause");

}

