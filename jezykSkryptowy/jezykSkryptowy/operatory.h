#pragma once
#include "zmienne.h"
namespace o {

	class Operator {
	public:
		char *id;
		int priority;
		Operator(char* id) : id(id) {}
		virtual int operation(variable &a, variable &b) = 0;
	};

	class plus : public Operator {
	public:
		plus() : Operator("+") { 
			priority = 3;
		}
		int operation(variable &a, variable &b) {
			return a.value + b.value;
		}
	};

	class minus : public Operator {
	public:
		minus() : Operator("-") {
			priority = 3;
		}
		int operation(variable &a, variable &b) {
			return a.value - b.value;
		}
	};

	class multiply : public Operator {
	public:
		multiply() : Operator("*") {
			priority = 4;
		}
		int operation(variable &a, variable &b) {
			return a.value * b.value;
		}
	};

	class divide : public Operator {
	public:
		divide() : Operator("/") {
			priority = 4;
		}
		int operation(variable &a, variable &b) {
			return a.value / b.value;
		}
	};

	class modulo : public Operator {
	public:
		modulo() : Operator("%") {
			priority = 4;
		}
		int operation(variable &a, variable &b) {
			return a.value % b.value;
		}
	};

	//class opposite : public Operator {
	//public:
	//	opposite() : Operator("-u") {
	//		priority = 5;
	//	}
	//	int operation(variable &a, variable &b) {
	//		return a.value % b.value;
	//	}
	//};


	class NOT : public Operator {
	public:
		NOT() : Operator("!") {
			priority = 5;
		}
		int operation(variable &a, variable &b) {
			return 0;
		}
		int operation(variable &a) {
			return 1;//
		}
	};

	class assign : public Operator {
	public:
		assign() : Operator("=") { 
			priority = 0;
		}
		int operation(variable &a, variable &b) { return 0; }
		int operation(variable &a, int suma) {
			a.value = suma;
		}
	};

	class OR : public Operator {
	public:
		OR() : Operator("|") {
			priority = 0;
		}
		int operation(variable &a, variable &b) { 
			return a.value | b.value; 
		}
	};

	class AND : public Operator {
	public:
		AND() : Operator("&") {
			priority = 0;
		}
		int operation(variable &a, variable &b) {
			return a.value & b.value;
		}
	};

	class lnawias : public Operator {
	public:
		lnawias() : Operator("(") {
			priority = 0;
		}
		int operation(variable &a, variable &b) { return 0; }
	};
	
	class pnawias : public Operator {
	public:
		pnawias() : Operator(")") {
			priority = 0;
		}
		int operation(variable &a, variable &b) { return 0; }
	};

	class notEqual : public Operator {
	public:
		notEqual() : Operator("!=") {
			priority = 1;
		}
		int operation(variable &a, variable &b) { 
			return a.value != b.value ? true : false; 
		}
	};

	class Equal : public Operator {
	public:
		Equal() : Operator("==") {
			priority = 1;
		}
		int operation(variable &a, variable &b) {
			return a.value == b.value ? true : false;
		}
	};

	class lessThan : public Operator {
	public:
		lessThan() : Operator("<") {
			priority = 2;
		}
		int operation(variable &a, variable &b) {
			return a.value == b.value ? true : false;
		}
	};

	class greaterThan : public Operator {
	public:
		greaterThan() : Operator(">") {
			priority = 2;
		}
		int operation(variable &a, variable &b) {
			return a.value == b.value ? true : false;
		}
	};


	class lessEqualThan : public Operator {
	public:
		lessEqualThan() : Operator("<=") {
			priority = 2;
		}
		int operation(variable &a, variable &b) {
			return a.value == b.value ? true : false;
		}
	};

	class greaterEqualThan : public Operator {
	public:
		greaterEqualThan() : Operator(">=") {
			priority = 2;
		}
		int operation(variable &a, variable &b) {
			return a.value == b.value ? true : false;
		}
	};
};