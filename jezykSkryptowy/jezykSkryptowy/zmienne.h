#pragma once

#define OPERATOR_COUNT 15
#define Nul -858993460
#define max 1000

enum ARG_TYPE {
	ONEARG,
	TWOARG,
	NONE,
};

enum MATH_TYPE {
	VARIABLE,
	OPERATOR,
	NUMBER,
	WHILE_LOOP,
	CONDITIONAL
};

class MathObject {
public:
	char *key;
	MATH_TYPE math_type;
	MathObject() {};
	MathObject(char* str) {
		key = new char[max];
		strcpy(key, str);
	}
	virtual ~MathObject() {
		delete key;
	};
};

class Number : public MathObject {
public:
	int value;
	Number() : value(Nul) {
		math_type = NUMBER;
	};
	Number(int val) : value(val) {
		math_type = NUMBER;
	};
	Number(char *name) : MathObject(name), value(0) {
		math_type = NUMBER;
		int i = 0;
		while (*(name + i) != '\0') {
			value *= 10;
			value += *(name + i) - '0';
			i++;
		}
	};
	void setValue(int val) {
		value = val;
	};
	void setInverse() {
		value = -value;
	}
};

class Variable : public MathObject {
public:
	Number liczba;
	bool toDisplay;
	Variable() {
		key = '\0';
		toDisplay = false;
		math_type = VARIABLE;
	};
	Variable(char* str) : MathObject(str) {
		toDisplay = false;
		math_type = VARIABLE;
	};
	~Variable() {};
};

class Conditional : public MathObject {
public:
	Conditional() {
		math_type = CONDITIONAL;
		key = "?";
	};
	
};

class While : public MathObject {
public:
	While() {
		math_type = WHILE_LOOP;
		key = "@";
	};

};