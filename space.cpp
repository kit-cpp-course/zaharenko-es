#include <iostream>
#include "space.h"

using namespace std;
using namespace spaces;


Space::Space(string f_name) {
	makeArray(f_name);
}

Space::~Space() {
	for (int i = 0; i < c_rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void Space::copy(int ** c_arr) {
	for (int i = 0; i < c_rows; i++) {
		for (int j = 0; j < c_columns; j++)
			c_arr[i][j] = arr[i][j];

	}
}

void Space::makeArray(string f_name) {
	ifstream file(f_name);
	file_name = f_name;
	/*
	* Подсчитаем количество чисел в файле
	*/
	int count = 0;
	int temp;

	while (file.good())
	{
		file >> temp;
		count++;
	}

	file.seekg(0, ios::beg);
	file.clear();
	/*
	* Подсчитаем количество пробелов в одной строке
	*/
	char symbol;
	int count_space = 0;

	do {
		file.get(symbol);
		if (symbol == ' ') count_space++;
	} while (symbol != '\n');

	c_rows = count / (count_space + 1);
	c_columns = count_space + 1;

	arr = new int*[c_rows];
	for (int i = 0; i < c_rows; i++) {
		arr[i] = new int[c_columns];
	}

	file.seekg(0, ios::beg);
	file.clear();
	/*
	* Проинициализируем массив
	*/
	for (int i = 0; i < c_rows; i++)
		for (int j = 0; j < c_columns; j++) {
			file >> arr[i][j];
		}
}

void Space::getSpace() {
	cout << "     ";
	for (int v = 0; v < c_columns; v++) {
		if (v > 9 && v < 100) {
			cout << " " << v << "  ";
		}
		else cout << "  " << v << "  ";
	}
	cout << endl;
	cout << "     ";
	for (int v = 0; v < c_columns; v++) {

		cout << " ___ ";
	}
	cout << endl;

	for (int i = 0; i < c_rows; i++) {
		int j = 0;
		if (i > 9 && i < 100) {
			cout << "" << i << "  " << '|' << ' ' << arr[i][j] << ' ' << '|';
		}
		else cout << ' ' << i << "  " << '|' << ' ' << arr[i][j] << ' ' << '|';
		for (j = 1; j < c_columns; j++) {
			cout << ' ' << arr[i][j] << ' ' << '|';
		}

		cout << endl;
		cout << "     ";
		for (int k = 0; k < c_columns; k++)
			cout << " --- ";
		cout << endl;
	}
}

bool Space::setStart(int x, int y) {
	if (x > c_columns-1 || y > c_rows-1) {
		return false;
	}
	start = point(x, y);
	return true;
}

bool Space::setFinish(int x, int y) {
	if (x > c_columns-1 || y > c_rows-1) {
		return false;
	}
	finish = point(x, y);
	return true;
}


void LeeAlgorithm::displayPath() {

	cout << "Путь:" << endl;
	if (len == 0) {
		cout << "Точки старта и финиша совпадают.";
	}
	else {
		for (int i = 0; i <= len; i++) {
			if (i == len) {
				cout << '[' << pj[i] << ',' << pi[i] << "]";
				break;
			}
			cout << '[' << pj[i] << ',' << pi[i] << "] -> ";
		}
	}
	cout << endl;
}

void LeeAlgorithm::recoverPath(Space &S) {

	int k, j, i, d;
	/*
	* Длина кратчайшего пути из (ax, ay) в (bx, by)
	*/
	len = field[S.finish.y][S.finish.x];

	j = S.finish.x;
	i = S.finish.y;
	d = len;
	while (d > 0)
	{
		pj[d] = j;
		pi[d] = i;
		d--;
		for (k = 0; k < 4; ++k)
		{
			int neighb_i = i + dy[k], neighb_j = j + dx[k];
			if (neighb_i >= 0 && neighb_i <S.c_rows && neighb_j >= 0 && neighb_j < S.c_columns && field[neighb_i][neighb_j] == d)
			{
				j = j + dx[k];
				i = i + dy[k];
				break;
			}
		}
	}
	pj[0] = S.start.x;
	pi[0] = S.start.y;

}

bool LeeAlgorithm::lee(Space &S)
{
	/*
	* Непроходимая ячейка (препятствие)
	*/
	const int WALL = -1;
	/*
	* Cвободная непомеченная ячейка
	*/
	const int BLANK = -2;

	len = 0;
	field = new int *[S.c_rows];
	for (int i = 0; i < S.c_rows; ++i)
		field[i] = new int[S.c_columns];
	S.copy(field);

	pi = new int[S.c_columns*S.c_rows];
	pj = new int[S.c_columns*S.c_rows];

	int d = 0, j, i, k;
	bool stop;

	if (field[S.start.y][S.start.x] == WALL || field[S.finish.y][S.finish.x] == WALL) return false;
	

	field[S.start.y][S.start.x] = 0;
	do {
		stop = true;
		for (i = 0; i < S.c_rows; ++i) {
			for (j = 0; j < S.c_columns; ++j) {
				if (field[i][j] == d)
				{
	/*
	* Проходим по всем непомеченным соседним ячейкам
	*/
					for (k = 0; k < 4; ++k)
					{
	/*
	*Вычисляем координаты соседних ячеек
	*/
						int neighb_i = i + dy[k], neighb_j = j + dx[k];
	/*
	* Проверяем, не выходим ли за границы массива и является ли непомеченной данная ячейка
	*/
						if (neighb_i >= 0 && neighb_i < S.c_rows && neighb_j >= 0 && neighb_j < S.c_columns && field[neighb_i][neighb_j] == BLANK)							
						{
	/*
	* Найдены непомеченные ячейки
	*/
							stop = false;
	/*
	* Распространение волны
	*/
							field[neighb_i][neighb_j] = d + 1;
						}
					}
				}
			}
		}
		d++;
	} while (!stop && field[S.finish.y][S.finish.x] == BLANK);
	/*
	* После распространения всех волн проверяем, помечена ли точка финиша.
	* Если не помечена, то путь недостижим.
	*/
	if (field[S.finish.y][S.finish.x] == BLANK) return false;

	recoverPath(S);
	displayPath();

	return true;
}
