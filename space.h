﻿#pragma once

#include <string>
#include <fstream>

using namespace std;

namespace spaces {
  
	class LeeAlgorithm;
	/*
	* Представление двумерного дискретного пространства для осуществления поиска.
	*/
	class Space {
		friend class LeeAlgorithm;
	/*
	* Представление точки в двумерном пространстве.
	*/
		class point {	
		public:
	/*
	* Координаты точки
	*/
			int x, y;
	/*
	* Конструктор по умолчанию
	*/
			point() { x = 0; y = 0; }
	/*
	* Параметризированный конструктор
	*/
			point(int x, int y) :x(x), y(y) {}
		};
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
	* Функция копирования значений из одного массива в другой
	* @param c_arr - массив, в который нужно скопировать данные
	*/
		void copy(int ** c_arr);
	/*
	* Метод, создающий и инициализирующий массив на основе данных из файла.
	* @param f_name - имя файла, из которого нужно считывать данные.
	*/
		void makeArray(string f_name);

	public:	
	/*
	* Конструктор класса Space
	* @param f_name - имя файла
	*/
		Space(string f_name);
	/*
	* Деструктор
	*/
		~Space();
	/*
	* Метод вывода массива на экран
	*/
		void getSpace();
	/*
	* Возвращает количество строк массива
	* @return c_rows - количество строк массива
	*/
		const inline int getRows() {
			return c_rows;
		}
	/*
	* Возвращает количество столбцов массива
	* @return c_columns - количество столбцов массива
	*/
		const inline int getColumns() {
			return c_columns;
		}
	/*
	* Присваивает значение точке старта
	* @param x, y - коодинаты точки
	* @return значение true или false как результат того, лежит ли точка внути массива
	*/
		bool setStart(int x, int y);
	/*
	* Присваивает значение точке финиша
	* @param x, y - коодинаты точки
	* @return значение true или false как результат того, лежит ли точка внути массива
	*/
		bool setFinish(int x, int y);
	};

	/*
	* Абстрактный класс, в котором определяется кратчайший путь от точки старта
	* до точки финиша.
	*/
	class PathAcquisition {
	public:
	/*
	* Вывод пути в консоль
	*/
		virtual bool findPath(Space &) const = 0;
	};

	class LeeAlgorithm :public PathAcquisition {
	/*
	* Длина пути
	*/
		mutable int len;
	/*
	* Массивы координат точек, составляющих путь
	*/
		mutable int * pi;
		mutable int * pj;
	/*
	* Массив, значения ячеек которого скопированы из int ** arr, чтобы не "испортить" значения arr в результате работы алгоритма.
	*/
		mutable int **field;
	/*
	* Значения смещений для получения координат соседних ячеек слева и справа.
	*/
		const int dx[4] = { 1, 0, -1, 0 };
	/*
	* Значения смещений для получения координат соседних ячеек сверху и снизу.
	*/
		const int dy[4] = { 0, 1, 0, -1 };
	/*
	* Восстановление кратчайшего пути
	*/
		void recoverPath(Space &S) const;
	/*
	* Функция, реализующая алгоритм Ли поиска кратчайшего пути из точки (ax, ay) в точку (bx, by)
	* @param S - ссылка на объект класса Space
	* @return значение true в случае, если путь найден, иначе false
	*/
		bool lee(Space &S) const;

	public:
	/*
	* Вывод пути в консоль
	* @param S - ссылка на объект класса Space
	* @return значение true в случае, если путь найден, иначе false
	*/
		bool findPath(Space &S) const;
	};
}
