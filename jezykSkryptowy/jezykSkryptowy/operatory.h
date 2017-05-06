#pragma once
#include "zmienne.h"
namespace op {

	class Operator {
	public:
		char *id;
		Operator(char* id) : id(id) {}
		virtual int operation(variable &a, variable &b) = 0;
	};

	class plus : public Operator {
	public:
		plus() : Operator("+") { }
		int operation(variable &a, variable &b) {
			return a.value + b.value;
		}
	};

	class minus : public Operator {
	public:
		minus() : Operator("-") { }
		int operation(variable &a, variable &b) {
			return a.value - b.value;
		}
	};

	class multi : public Operator {
	public:
		multi() : Operator("*") { }
		int operation(variable &a, variable &b) {
			return a.value * b.value;
		}
	};

	class divide : public Operator {
	public:
		divide() : Operator("/") { }
		int operation(variable &a, variable &b) {
			return a.value / b.value;
		}
	};

	class assign : public Operator {
	public:
		assign() : Operator("=") { }
		int operation(variable &a, variable &b) { return 0; }
		int operation(variable &a, int suma) {
			a.value = suma;
		}
	};
}