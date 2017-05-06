#include <iostream>
using namespace std;

class stos {
public:
	stos *nast;
	int dane;

	stos() {
		dane = NULL;
		nast = NULL;
	};
	
};
bool empty(stos *p) { return !p; }

void push(stos *p, int dane) {
	stos *nowy = new stos;
	nowy->dane = dane;
	nowy->nast = p;
	p = nowy;
}
void pop(stos *&p) {
	if (!empty(p)) {
		stos *temp = new stos;
		temp = p;
		p = p->nast;
		delete temp;
	}
}
void wypisz(stos *p) {
	stos *tmp = p;
	while (!empty(tmp)) {
		printf("%d ", tmp->dane);
		tmp = tmp->nast;
	}
}
int current(stos *p) {
	if (!empty(p))
		return p->dane;
	else return NULL;
}
int rozmiar(stos *p) {
	stos *tmp = p;
	int a = 0;
	while (!empty(tmp)) {
		a++;
		tmp = tmp->nast;
	}
	return a;
}