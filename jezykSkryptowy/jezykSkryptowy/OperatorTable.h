#pragma once
#include <iostream>
#include "operatory.h"


using namespace std;

class OperatorTable {
public:
	Operator **tab;
	OperatorTable() {
		tab = new Operator*[OPERATOR_COUNT];
		tab[0] = new Assign();
		tab[1] = new OR();
		tab[2] = new AND();
		tab[3] = new Plus();
		tab[4] = new Minus();
		tab[5] = new Divide();
		tab[6] = new Multiply();
		tab[7] = new Modulo();

		tab[8] = new lessThan();
		tab[9] = new greaterThan();
		tab[10] = new notEqual();
		tab[11] = new Equal();
		tab[12] = new lessEqualThan();
		tab[13] = new greaterEqualThan();
		tab[14] = new NOT();
		tab[15] = new Unary();
	}

	Operator* getOperator(char *s) {
		if (strcmp(s,"=") == 0) return tab[0]; //Assign
		else if (strcmp(s, "|") == 0) return tab[1]; //OR
		else if (strcmp(s, "&") == 0) return tab[2]; //AND
		else if (strcmp(s, "+") == 0) return tab[3]; //Plus
		else if (strcmp(s, "-") == 0) return tab[4]; //Minus
		else if (strcmp(s, "/") == 0) return tab[5]; //Divide
		else if (strcmp(s, "*") == 0) return tab[6]; //Multiply
		else if (strcmp(s, "%") == 0) return tab[7]; //Modulo
		
		else if (strcmp(s, "<") == 0) return tab[8]; //lessThan
		else if (strcmp(s, ">") == 0) return tab[9]; //greaterThan
		else if (strcmp(s, "!=") == 0) return tab[10]; //notEqual();
		else if (strcmp(s, "==") == 0) return tab[11]; //Equal();
		else if (strcmp(s, "<=") == 0) return tab[12]; //lessEqualThan();
		else if (strcmp(s, ">=") == 0) return tab[13]; //greaterEqualThan();
		
		else if (strcmp(s, "!") == 0) return tab[14]; //NOT();

		else return NULL;
	}


};
