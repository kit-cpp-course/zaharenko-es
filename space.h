#pragma once
#include <string>
#include <fstream>
using namespace std;

namespace spaces {

	/*
	* Представление двумерного дискретного пространства для осуществления поиска.
	*/
	class Space :public point {

		friend bool lee(Space &);
		/*
		* Файл, из которого считываются данные для записи в массив
		*/
		string file_name;
		/*
		* Массив чисел, который составляет пространство
		*/
		int ** arr;
		/*
		* Количество строк и столбцов массива
		*/
		int c_rows, c_columns;
		/*
		* Точки старта и финиша, между которыми нужно найти кратчайший путь
		*/
		point start, finish;
		/*
		* Координаты x и y точек старта и финиша
		*/
		int ax, ay, bx, by;
		/*
		* Функция копирования значений из одного массива в другой
		* @param c_arr - массив, в который нужно скопировать данные
		*/
		void copy(int ** c_arr) {
			for (int i = 0; i < c_rows; i++) {
				for (int j = 0; j < c_columns; j++)
					c_arr[i][j] = arr[i][j];

			}
		}
		/*
		* Функция, создающая инициализирующая массив, состовляющий пространство, на основе данных из файла.
		* @param f_name - имя файла, из которого нужно считывать данные.
		*/
		void makeArray(string f_name) {
			ifstream file(f_name);
			if (!file.is_open()) {
				throw exception("Файл недоступен");
			}
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
	public:
		/*
		* Конструктор класса Space
		* @param f_name - имя файла
		*/
		Space(string f_name) {
			makeArray(f_name);
		}
		/*
		* Деструктор
		*/
		~Space() {
			for (int i = 0; i < c_rows; i++)
			{
				delete[] arr[i];
			}
			delete[] arr;
		}
		/*
		* Функция вывода массива на экран
		*/
		void getSpace() {
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

		/*
		* Возвращает количество строк массива
		* @return c_rows - количество строк массива
		*/
		int getRows() {
			return c_rows;
		}
		/*
		* Возвращает количество столбцов массива
		* @return c_columns - количество столбцов массива
		*/
		int getColumns() {
			return c_columns;
		}
		/*
		* Присваивает значение точке старта
		* @param x, y - коодинаты точки
		*/
		void setStart(int x, int y) {
			start = point(x, y);
			ax = x;
			ay = y;
		}
		/*
		* Присваивает значение точке финиша
		* @param x, y - коодинаты точки
		*/
		void setFinish(int x, int y) {
			finish = point(x, y);
			bx = x;
			by = y;
		}
	};
	/*
	* Функция вывода на экран кратчайшего пути
	* @param len - длина кратчайшего пути
	* @param pi, pj - координаты ячеек пути
	*/
	void displayPath(int len, int * pi, int *pj) {

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
	/*
	* Восстановление кратчайшего пути
	* @param field - рабочее поле
	* @param pi, pj - координаты ячеек пути
	* @param dx, dy - координаты смещений
	* @param col, rows - количество столбцов и строк массива-поля
	* @param t1_x, t1_y, t2_x, t2_y - координаты точек старта и финиша
	* @return len - длина крайтчайшего пути
	*/
	int recoverPath(int ** field, int *pi, int *pj, int dx[], int dy[], int col, int rows, int t1_x, int t1_y, int t2_x, int t2_y) {
		int k, j, i, d;
		/*
		* Длина кратчайшего пути из (ax, ay) в (bx, by)
		*/
		int len = field[t2_y][t2_x];
		j = t2_x;
		i = t2_y;
		d = len;
		while (d > 0)
		{
			pj[d] = j;
			pi[d] = i;
			d--;
			for (k = 0; k < 4; ++k)
			{
				int neighb_i = i + dy[k], neighb_j = j + dx[k];
				if (neighb_i >= 0 && neighb_i <rows && neighb_j >= 0 && neighb_j < col && field[neighb_i][neighb_j] == d)
				{
					j = j + dx[k];
					i = i + dy[k];
					break;
				}
			}
		}
		pj[0] = t1_x;
		pi[0] = t1_y;

		return len;
	}
	/*
	* Функция, реализующая алгоритм Ли поиска кратчайшего пути из точки (ax, ay) в точку (bx, by)
	* @param s - ссылка на объект класса Space
	* @return значение true в случае, если путь найден, иначе false
	*/
	bool lee(Space &s)
	{
		/*
		* Длина пути
		*/
		int len = 0;
		/*
		* Массив точек, составляющих путь
		*/
		int * pi = new int[s.c_columns*s.c_rows];
		int * pj = new int[s.c_columns*s.c_rows];
		/*
		* Координаты точки старта и точки финиша (переменные необходимы для передачи в функцию recoverPath)
		*/
		int t1_x = s.ax, t1_y = s.ay, t2_x = s.bx, t2_y = s.by;
		/*
		* Копируем значения массива arr в новый массив, чтобы не "испортить" значения в результате работы алгоритма.
		*/
		int **field = new int *[s.c_rows];
		for (int i = 0; i < s.c_rows; ++i)
			field[i] = new int[s.c_columns];
		s.copy(field);
		/*
		* Непроходимая ячейка (препятствие)
		*/
		const int WALL = -1;
		/*
		* Cвободная непомеченная ячейка
		*/
		const int BLANK = -2;
		/*
		* Значения смещений для получения координат соседних ячеек слева и справа.
		*/
		int dx[4] = { 1, 0, -1, 0 };
		/*
		* Значения смещений для получения координат соседних ячеек сверху и снизу.
		*/
		int dy[4] = { 0, 1, 0, -1 };

		int d = 0, j, i, k;
		bool stop;

		if (field[t1_y][t1_x] == WALL || field[t2_y][t2_x] == WALL) return false;

		field[t1_y][t1_x] = 0;
		do {
			stop = true;
			for (i = 0; i < s.c_rows; ++i) {
				for (j = 0; j < s.c_columns; ++j) {
					if (field[i][j] == d)
					{
						for (k = 0; k < 4; ++k)//Проходим по всем непомеченным соседним ячейкам
						{
							int neighb_i = i + dy[k], neighb_j = j + dx[k];//Вычисляем координаты соседних ячеек
							if (neighb_i >= 0 && neighb_i < s.c_rows && neighb_j >= 0 && neighb_j < s.c_columns && field[neighb_i][neighb_j] == BLANK)
								//Проверяем, не выходим ли за границы массива и является ли непомеченной данная ячейка
							{
								stop = false; //Найдены непомеченные ячейки
								field[neighb_i][neighb_j] = d + 1;//Распространение волны
							}
						}
					}
				}
			}
			d++;
		} while (!stop && field[t2_y][t2_x] == BLANK);
		/*
		* После распространения всех волн проверяем, помечена ли точка финиша.
		* Если не помечена, то путь недостижим.
		*/
		if (field[t2_y][t2_x] == BLANK) return false;

		len = recoverPath(field, pi, pj, dx, dy, s.c_columns, s.c_rows, t1_x, t1_y, t2_x, t2_y);
		displayPath(len, pi, pj);

		return true;
	}

}

