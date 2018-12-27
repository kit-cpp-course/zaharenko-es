#pragma once
#include <iostream>
using namespace std;
/*
* Объект типа params определяет параметры командной строки.
* В данном классе происходит проверка параметров на то,
* удовлетворяют ли они условиям данной задачи.
*/
class params {
/*
* Количество аргументов
*/	
	int argc;
/*
* Массив аргументов
*/
	char ** argv;
/*
* Значение-маркер, определяющее, правильно ли введено имя файла.
*/
	bool isRightFileName(int index) const;
/*
* Значение-маркер, определяющее, правильно ли введены аргументы, отвечающие за координаты
* точек старта и финиша.
*/
	bool isRightValue(int index) const;

public:
/*
* Конструктор по умолчанию
*/
	params(int count, char ** arguments) :argc(count), argv(arguments) {}
/*
* Метод, проверяющий, верно ли введены данные.
* @return значение false или true, определяющее, верно ли введены параметры.
*/
	bool isRightInput() const;
/*
* Метод, возвращающий целочисленные аргументы.
* @param index - значение, обозначающее индекс необходимого аргумента в массиве argv
* @return целочисленный аргумент
*/
	int inline getIntegerArg(int index) {
		return atoi(argv[index]);
	}
/*
* Метод, возвращающий строковые аргументы.
* @param index - значение, обозначающее индекс необходимого аргумента в массиве argv
* @return строковый аргумент
*/
	string inline getStringArg() {
		return (string)argv[1];
	}

};
