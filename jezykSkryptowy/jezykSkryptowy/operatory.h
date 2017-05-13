#pragma once
#include "zmienne.h"
namespace o {

	class Operator : public MathObject {
	public:
		int priority;
		ARG_TYPE arg_type;
		Operator() {
			math_type = OPERATOR;
		};
		Operator(char* key) : MathObject(key) {
			math_type = OPERATOR;
		};
		virtual Number* operation(Number *a, Number *b) = 0;
		~Operator() {};
	};

	class plus : public Operator {
	public:
		plus() : Operator("+") {
			priority = 5;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value + b->value);
			return wynik;
		}
		~plus() {};
	};

	class minus : public Operator {
	public:
		minus() : Operator("-") {
			priority = 5;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value - b->value);
			return wynik;
		}
	};

	class multiply : public Operator {
	public:
		multiply() : Operator("*") {
			priority = 6;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value * b->value);
			return wynik;
		}
	};

	class divide : public Operator {
	public:
		divide() : Operator("/") {
			priority = 6;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value / b->value);
			return wynik;
		}
	};

	class modulo : public Operator {
	public:
		modulo() : Operator("%") {
			priority = 6;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value % b->value);
			return wynik;
		}
	};

	class assign : public Operator {
	public:
		assign() : Operator("=") {
			priority = 0;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik;
			a->value = b->value;
			return a;
		}
	};

	class OR : public Operator {
	public:
		OR() : Operator("|") {
			priority = 1;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value | b->value);
			return wynik;
		}
	};

	class AND : public Operator {
	public:
		AND() : Operator("&") {
			priority = 2;
			arg_type = TWOARG;
		}
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != Nul && b->value != Nul)
				wynik->setValue(a->value & b->value);
			return wynik;
		}
	};

	class lnawias : public Operator {
	public:
		lnawias() : Operator("(") {
			priority = 0;
			arg_type = NONE;
		}
		Number* operation(Number *a, Number *b) { return NULL; };
	};

	class pnawias : public Operator {
	public:
		pnawias() : Operator(")") {
			priority = 0;
			arg_type = NONE;
		}
		Number* operation(Number *a, Number *b) {};
	};

	class lnawias2 : public Operator {
	public:
		lnawias2() : Operator("{") {
			priority = 0;
			arg_type = NONE;
		}
		Number* operation(Number *a, Number *b) {};
	};

	class pnawias2 : public Operator {
	public:
		pnawias2() : Operator("}") {
			priority = 0;
			arg_type = NONE;
		}
		Number* operation(Number *a, Number *b) {};
	};

	//OPERATORY JEDNOARGUMENTOWE!!
	class NOT : public Operator {
	public:
		NOT() : Operator("!") {
			priority = 7;
			arg_type = ONEARG;
		}
		Number* operation(MathObject *a) {
			Number* n = new Number(dynamic_cast<Number*>(a)->value);
			if (n->value == Nul)
				n->setValue(0);
			else
				n->setValue(Nul);
			return n;
		}
		Number* operation(Number *a, Number *b) { return NULL; };
	};

	//**********//

	class notEqual : public Operator {
	public:
		notEqual() : Operator("!=") {
			priority = 3;
			arg_type = TWOARG;
		}
		void operation(Number *a) {};
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value != b->value)
				wynik->setValue(0);
			return wynik;
		}
	};

	class Equal : public Operator {
	public:
		Equal() : Operator("==") {
			priority = 3;
			arg_type = TWOARG;
		}
		void operation(Number *a) {};
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value == b->value)
				wynik->setValue(0);
			return wynik;
		}
	};

	class lessThan : public Operator {
	public:
		lessThan() : Operator("<") {
			priority = 4;
			arg_type = TWOARG;
		}
		void operation(Number *a) {};
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value < b->value)
				wynik->setValue(0);
			return wynik;
		}
	};

	class greaterThan : public Operator {
	public:
		greaterThan() : Operator(">") {
			priority = 4;
			arg_type = TWOARG;
		}
		void operation(Number *a) {};
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value > b->value)
				wynik->setValue(0);
			return wynik;
		}
	};


	class lessEqualThan : public Operator {
	public:
		lessEqualThan() : Operator("<=") {
			priority = 4;
			arg_type = TWOARG;
		}
		void operation(Number *a) {};
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value <= b->value)
				wynik->setValue(0);
			return wynik;
		}
	};

	class greaterEqualThan : public Operator {
	public:
		greaterEqualThan() : Operator(">=") {
			priority = 4;
			arg_type = TWOARG;
		}
		void operation(Number *a) {};
		Number* operation(Number *a, Number *b) {
			Number* wynik = new Number(Nul);
			if (a->value >= b->value)
				wynik->setValue(0);
			return wynik;
		}
	};
};