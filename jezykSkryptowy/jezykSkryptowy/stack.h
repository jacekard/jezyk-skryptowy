#pragma once

#include "Node.h"

template <class T>
class stack {
public:
	node<T> *s;

	stack() {
		s = NULL;
	}

	bool empty(node<T> *p) {
		return !p;
	}

	void push(T data) {
		node<T> *nowy = new node<T>;
		nowy->data = data;
		nowy->next = s;
		s = nowy;
	}
	void pop() {
		if (!empty(s)) {
			node<T> *temp = new node<T>;
			temp = s;
			s = s->next;
			delete temp;
		}
	}
	void wypisz() {
		node<T> *tmp = s;
		while (!empty(tmp)) {
			printf("%d ", tmp->data);
			tmp = tmp->next;
		}
	}
	T current() {
		if (!empty(s))
			return s->data;
		else return NULL;
	}
	int rozmiar() {
		node<T> *tmp = s;
		int a = 0;
		while (!empty(tmp)) {
			a++;
			tmp = tmp->next;
		}
		return a;
	}

};
