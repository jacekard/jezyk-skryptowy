#pragma once
#include <iostream>
#include "operatory.h"

class o::Operator;

class OperatorTable {
public:
	const int operatorCount = 15;
	o::Operator **tab;
	OperatorTable() {
		/*using namespace o;*/
		tab = new o::Operator*[operatorCount];
		tab[0] = new o::assign();
		tab[1] = new o::OR();
		tab[2] = new o::AND();
		tab[3] = new o::notEqual();
		tab[4] = new o::Equal();
		tab[5] = new o::lessThan();
		tab[6] = new o::greaterThan();
		tab[7] = new o::lessEqualThan();
		tab[8] = new o::greaterEqualThan();
		tab[9] = new o::plus();
		tab[10] = new o::minus();
		tab[11] = new o::divide();
		tab[12] = new o::multiply();
		tab[13] = new o::modulo();
		tab[14] = new o::NOT();
		//tab[15] = new opposite();
	}

	o::Operator* getOperator(char *s) {
		if (*(s + 1) == '=') {
			if (*s == '!')		return tab[3];//new notEqual();
			else if (*s == '=') return tab[4];//new Equal();
			else if (*s == '<') return tab[7];//new lessEqualThan();
			else if (*s == '>') return tab[8];//new greaterEqualThan();
		}
		else if (*s == '=') return tab[0];//new o::assign();
		else if (*s == '|') return tab[1];//new OR();
		else if (*s == '&') return tab[2];//new AND();
		else if (*s == '<') return tab[5];//new lessThan();
		else if (*s == '>') return tab[6];//new greaterThan();
		else if (*s == '+') return tab[9];//new o::plus();
		else if (*s == '-') return tab[10];//new o::minus();
		else if (*s == '/') return tab[11];//new o::divide();
		else if (*s == '*') return tab[12];//new multiply();
		else if (*s == '%') return tab[13];//new modulo();
		else if (*s == '!') return tab[14];//new NOT();

		else return NULL;
	}


};