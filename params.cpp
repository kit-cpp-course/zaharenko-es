#include <fstream>
#include "params.h"
#include "exception"

using namespace std;

bool params::isRightInput() const {
	try {
		if (argc != 6 || !isRightFileName(1) || !isRightValue(2) || !isRightValue(3) || !isRightValue(4) || !isRightValue(5)) {
			throw exception("Ошибка при вводе параметров.");
		} else {
			cout << "Параметры введены верно." << endl;
			return true;
		}		
	}
	catch (const exception & ex) {
		cout << ex.what() << endl;
		return false;
	}
}

bool params::isRightValue(int index) const {
	if (argv[index][0] == '-') {
		return false;
	}
	return true;

}

bool params::isRightFileName(int index) const {
	ifstream file(argv[index]);
	if (!file.is_open()) {
		return false;
	}
	return true;
}