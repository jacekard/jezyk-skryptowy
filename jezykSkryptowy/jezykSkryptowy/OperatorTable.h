#pragma once
#include <iostream>
#include "operatory.h"

class o::Operator;
#define OPERATOR_COUNT 15

class OperatorTable {
public:
	o::Operator **tab;
	OperatorTable() {
		using namespace o;
		tab = new Operator*[OPERATOR_COUNT];
		tab[0] = new assign();
		tab[1] = new OR();
		tab[2] = new AND();
		tab[3] = new o::plus();
		tab[4] = new o::minus();
		tab[5] = new divide();
		tab[6] = new multiply();
		tab[7] = new modulo();

		tab[8] = new lessThan();
		tab[9] = new greaterThan();
		tab[10] = new notEqual();
		tab[11] = new Equal();
		tab[12] = new lessEqualThan();
		tab[13] = new greaterEqualThan();
		tab[14] = new NOT();

	}

	o::Operator* getOperator(char *s) {
		using namespace o;

		if (strcmp(s,"=") == 0) return tab[0]; //assign
		else if (strcmp(s, "|") == 0) return tab[1]; //OR
		else if (strcmp(s, "&") == 0) return tab[2]; //AND
		else if (strcmp(s, "+") == 0) return tab[3]; //plus
		else if (strcmp(s, "-") == 0) return tab[4]; //minus
		else if (strcmp(s, "/") == 0) return tab[5]; //divide
		else if (strcmp(s, "*") == 0) return tab[6]; //multiply
		else if (strcmp(s, "%") == 0) return tab[7]; //modulo
		
		else if (strcmp(s, "<") == 0) return tab[8]; //lessThan
		else if (strcmp(s, ">") == 0) return tab[9]; //greaterThan
		else if (strcmp(s, "!=") == 0) return tab[10]; //notEqual();
		else if (strcmp(s, "==") == 0) return tab[11]; //Equal();
		else if (strcmp(s, "<=") == 0) return tab[12]; //lessEqualThan();
		else if (strcmp(s, ">=") == 0) return tab[13]; //greaterEqualThan();
		
		else if (strcmp(s, "!") == 0) return tab[14]; //NOT();

		//if (*(s + 1) == '=') {
		//	if (*s == '!')		return tab[3];//new 
		//	else if (*s == '=') return tab[4];//new 
		//	else if (*s == '<') return tab[7];//new 
		//	else if (*s == '>') return tab[8];//new 
		//	else return NULL;
		//}

		else return NULL;
	}


};