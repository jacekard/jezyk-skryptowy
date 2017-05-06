#pragma once

#include "Queue.h"
#include "Stack.h"
#include "Operatory.h"
#include "tree.h"

using namespace op;

#define max 1000

int length(char *s) {
	int licznik = 0;
	while (*(s + licznik) != '\0'){
		licznik++;
	}
	return licznik;
}

int main() {

	int licznikOperacji;
	int zliczajOperacje = 0;

	queue<char*> nazwy;
	int varCount = 0;

	std::cin >> licznikOperacji;

	char character = '0';
	char *line = new char[max];
	tree *root = NULL;

	std::cin.getline(line, max);
	int i = 0;
	while (character != '\n' && character != '\r') {
		std::cin.get(character);
		if (character == ' ' || character == '\n' || character == '\r') {
			*(line + i) = '\0';
			nazwy.add(line);
			line = new char[max];
			i = 0;
		}
		else {
			*(line + i) = character;
			i++;
		}
	}

	varCount = nazwy.rozmiar();

	for (i = 0; i < varCount; i++) {
		variable tmp;
		tmp.key = nazwy.current();
		if (root != NULL)
			insert(root, tmp);
		else {
			root = new tree(tmp);
			root->parent = NULL;
		}
		nazwy.del();
	}

	wypisz_inorder(root);

	tree* szukany = search(root, "abc");

	if (szukany != NULL) {
		std::cout << "Znaleziono: " << szukany->var.key << " => ";
		std::cout << szukany->var << std::endl;
	}


	Operator *Operators[5];
	Operators[0] = new minus();
	Operators[1] = new plus();
	Operators[2] = new multi();
	Operators[3] = new divide();
	Operators[4] = new assign();

	tree* zmienna;
	stack<tree*> vars;
	stack<Operator*> operatory;
	stack<int> liczby;
	while (std::cin >> line) {
		std::cout << line << std::endl;
		for (int i = 0; i < length(line); i++) {
			for (int j = 0; j < 5; j++) {
				if (line + j == Operators[j]->id)
					operatory.push(Operators[j]);
			}
			if (zmienna = search(root, line + i))
				vars.push(zmienna);
			else
				liczby.push((int)line + i);
		}
	}

	int rozmiar1 = vars.rozmiar();
	int rozmiar2 = operatory.rozmiar();
	int rozmiar3 = liczby.rozmiar();

	for (int i = 0; i < rozmiar1; i++) {
		std::cout << vars.current();
		vars.pop();
	}
	std::cout << std::endl;

	for (int i = 0; i < rozmiar2; i++) {
		std::cout << operatory.current();
		operatory.pop();
	}
	std::cout << std::endl;
	for (int i = 0; i < rozmiar3; i++) {
		std::cout << liczby.current();
		liczby.pop();
	}
	std::cout << std::endl;
	return 0;
}



//	if (zliczajOperacje >= licznikOperacji)
//		break;
//	//	if ()
//	cout << name;
//	//if ()
//}