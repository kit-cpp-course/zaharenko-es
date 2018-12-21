#pragma once
namespace spaces {
	class point {
	/*
	* Координаты точки
	*/
		int x, y;
	public:
	/*
	* Конструктор по умолчанию
	*/
		point() { x = 0; y = 0; }
	/*
	* Параметризированный конструктор
	*/
		point(int x, int y) :x(x), y(y) {}
	};
}
