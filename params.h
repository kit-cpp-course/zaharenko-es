#pragma once
#include <iostream>
using namespace std;

class params {
	int argc;

	char ** argv;

	bool isRightFileName(int index) const;

	bool isRightValue(int index) const;

public:

	params(int count, char ** arguments) :argc(count), argv(arguments) {}

	bool isRightInput() const;

	int inline getIntegerArg(int index) {
		return atoi(argv[index]);
	}

	string inline getStringArg() {
		return (string)argv[1];
	}

};