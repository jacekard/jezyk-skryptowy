#pragma once

#include "Queue.h"
#include "Stack.h"
#include "tree.h"
#include "OperatorTable.h"

int length(char *s) {
	int licznik = 0;
	while (*(s + licznik) != '\0'){
		licznik++;
	}
	return licznik;
}

bool czyLitera(char znak) {

	if ((znak >= 'A' && znak <= 'Z')
		|| (znak >= 'a' && znak <= 'z'))
		return true;
	else
		return false;
}

bool czyCyfra(char znak) {
	if (znak >= '0' && znak <= '9')
		return true;
	else
		return false;
}

int intLength(int liczba) {
	if (liczba > 0) {
		return 1 + intLength(liczba / 10);
	}
	else {
		return 0;
	}

	int przyklad = 1234;
	przyklad = intLength(przyklad);
	cout << przyklad;
}

void addNewInstruction(stack<Operator*> &stosOperatorow,
	queue<MathObject*> *&instrukcja,
	queue<queue<MathObject*>*> &kolejkaInstrukcji) {

	while (stosOperatorow.current()) {
		instrukcja->push((stosOperatorow.current()));
		stosOperatorow.pop();
	}
	kolejkaInstrukcji.push(instrukcja);
	instrukcja = new queue<MathObject*>();
}

Variable* addNewVariable(char *nazwa, Tree *VariableTree, int isDeclared) {
	Variable *tmp = new Variable(nazwa);
	if (isDeclared)
		tmp->toDisplay = true;
	VariableTree->add(tmp);
	return tmp;
}

int main() {
	/*
	Zapamietanie adresu PIERWSZEGO ELEMENTU w kolejce

	0a. Wczytanie licznikaOperacji (OK)
	0b. Wczytanie zmiennych do drzewa binarnego (OK)
	1. Rozdzielanie wyra¿eñ (OK)
	2a. Zamiana na ONP wpisywanie wyra¿eñ do kolejek wyra¿eñ
	3. Rozdzielenie instrukcji (trzeba rozpoznaæ co to za instrukcja)
	4. wrzucenie instrukcji do kolejki instrukcji
	5. Wykonanie kodu
	6. w momencie rozpoczêcia while'a, zapisujemy tymczasowo adres instrukcji (która jest kolejk¹) na stos<queue*>
	Dok³adnie zwracamy firstElement
	*/



	//**
	//****
	int licznikOperacji;
	int zliczajOperacje = 0;
	cin >> licznikOperacji;
	//****
	//**

	////Przyk³ad dzia³ania kolejki kolejek
	//queue<queue<char*>*> kolejkaInstrukcji;
	//queue<char*> *kolejka = new queue<char*>();
	//kolejkaInstrukcji.push(kolejka);
	//stack<queue<char*>*> stos_instrukcji;
	//stos_instrukcji.push(kolejka);

	//node<queue<char*>*> node = kolejkaInstrukcji.pop();
	//kolejka = node.data;
	//kolejkaInstrukcji.head = &node;
	////

	int zliczajZmienne = 0;
	char *nazwaWyrazenia = new char[max];
	char *line = new char[max];
	char znak = *line;
	Tree *VariableTree = new Tree();

	//**
	//formatowanie
	cin.getline(line, max);
	//**

	//**
	//*****
	//Funkcja dodaj¹ca zmienne na drzewo binarne 'VariableTree'
	int i = 0, j = 0;
	cin.getline(line, max);

	while (1) {
		znak = *(line + i);
		if (znak == '\0') break;
		if (czyLitera(znak)) {
			*(nazwaWyrazenia) = znak;
			while (czyLitera(*(line + i + 1))) {
				*(nazwaWyrazenia + ++j) = *(line + ++i);
			}
			*(nazwaWyrazenia + ++j) = '\0';
			j = 0;
			i++;
			//dodawanie obiektu 'tmp' ARG_TYPEu Variable do 'VariableTree'
			addNewVariable(nazwaWyrazenia, VariableTree, true);
			zliczajZmienne++;
			nazwaWyrazenia = new char[max];
		}
		else {
			i++;
		}
	}
	//****
	//**


	/*
	ODEJMOWANIE PO ZMIENNEJ/LICZBIE, a w przeciwnych wypadkach
	kiedy jest PO OPERATORZE to:
	a. PRZECIWNOŒÆ JAKO OPERACJA JEST TYLKO PRZED ZMIENNA
	b. przed liczba to do liczby
	*/

	//kolejka instrukcji, ktore sa kolejkami wyrazen
	queue<queue<MathObject*>*> kolejkaInstrukcji;
	//przechowuje rozdzielone wyrazenia JEDNEJ instrukcji zapisane w kolejnoœci ONP
	queue<MathObject*> *instrukcja;
	//stos operatorow potrzebny do konwersji na ONP
	stack<Operator*> stosOperatorow;
	//tablica wszystkich dostepnych operatorow
	OperatorTable OperatorList;

	//**
	//****
	//Konwersja z notacji infiksowej do ONP / rozdzielanie wyrazen na instrukcje
	znak = *line;
	i = 0;

	instrukcja = new queue<MathObject*>();
	bool nowaInstrukcja = false;
	bool czyOperand = false;
	bool czyPrzeciwny = false;

	while (cin.getline(line, max)) {
		/*for (int x = 0; x < 3; x++) {
			cin.getline(line, max);
		*/while (1) {

			int j = 0;
			znak = *(line + i);

			if (znak == '\0') {
				break;
			}
			else if (znak == ' ' || znak == '\t') {
				i++;
				continue;
			}

			*(nazwaWyrazenia + j) = znak;

			//ZMIENNE//
			if (czyLitera(znak)) {
				while (czyLitera(*(line + i + 1))) {
					*(nazwaWyrazenia + ++j) = *(line + ++i);
				}
				*(nazwaWyrazenia + ++j) = '\0';

				if (nowaInstrukcja)
					addNewInstruction(stosOperatorow, instrukcja, kolejkaInstrukcji);

				nowaInstrukcja = true;
				czyOperand = true;

				Tree_node* node = VariableTree->search(VariableTree->root, nazwaWyrazenia);
				if (node)
					instrukcja->push(node->var);
				else {
					Variable *newVar = addNewVariable(nazwaWyrazenia, VariableTree, false);
					instrukcja->push(newVar);
				}
			}
			//***
			//LICZBY//
			else if (czyCyfra(znak)) {
				while (czyCyfra(*(line + i + 1))) {
					*(nazwaWyrazenia + ++j) = *(line + ++i);
				}
				*(nazwaWyrazenia + j + 1) = '\0';

				if (nowaInstrukcja) {
					addNewInstruction(stosOperatorow, instrukcja, kolejkaInstrukcji);
				}
				nowaInstrukcja = true;
				czyOperand = true;

				Number *liczba = new Number(nazwaWyrazenia);
				instrukcja->push(liczba);
			}
			//***
			else if (znak == '@') {
				addNewInstruction(stosOperatorow, instrukcja, kolejkaInstrukcji);
				instrukcja->push(new While());
				nowaInstrukcja = false;
				czyOperand = false;
			}
			else if (znak == '?') {
				addNewInstruction(stosOperatorow, instrukcja, kolejkaInstrukcji);
				instrukcja->push(new Conditional());
				czyOperand = false;
				nowaInstrukcja = false;
			}
			else if (znak == '{') {
				instrukcja->push(new BegNawias());
				nowaInstrukcja = true;
				czyOperand = false;
			}
			else if (znak == '}') {
				addNewInstruction(stosOperatorow, instrukcja, kolejkaInstrukcji);
				instrukcja->push(new EndNawias());
				nowaInstrukcja = false;
				czyOperand = false;
			}
			else if (znak == '(') {
				if (czyOperand == true)
					addNewInstruction(stosOperatorow, instrukcja, kolejkaInstrukcji);
				stosOperatorow.push(new LewyNawias());
				czyOperand = false;
				nowaInstrukcja = false;
			}
			else if (znak == ')') {

				while (!dynamic_cast<LewyNawias*>(stosOperatorow.current())) {
					instrukcja->push(stosOperatorow.current());
					stosOperatorow.pop();
				}

				stosOperatorow.pop();
				czyOperand = true;
				//nowaInstrukcja = false;
			}
			//Operatory
			else {
				if (*(line + i + 1) == '=') {
					*(nazwaWyrazenia + ++j) = *(line + ++i);
				}

				//***
				//POPRAWIC TO WYRAZENIE UNARNE!
				//****

				*(nazwaWyrazenia + ++j) = '\0';
				Operator *aktualnyOperator = OperatorList.getOperator(nazwaWyrazenia);

				czyPrzeciwny = false;

				if (*aktualnyOperator->key == '-') {
					if (czyOperand == false) {
						instrukcja->push(OperatorList.tab[15]);
						czyPrzeciwny = true;
					}
					else
						czyPrzeciwny = false;
				}

				czyOperand = false;

				if (czyPrzeciwny == false) {
					int tmp_priority = 0;
					if (dynamic_cast<Assign*>(aktualnyOperator) || dynamic_cast<NOT*>(aktualnyOperator))
						tmp_priority = 1;
					int actualPriority = aktualnyOperator->priority + tmp_priority;
					while (stosOperatorow.current() && actualPriority <= stosOperatorow.current()->priority) {
						instrukcja->push((stosOperatorow.current()));
						stosOperatorow.pop();
					}
					stosOperatorow.push(aktualnyOperator);
				}
				nowaInstrukcja = false;

			}

			nazwaWyrazenia = new char[max];
			i++;
		}
		i = 0;
	}
	//dla ostatniej instrukcji
	while (stosOperatorow.current()) {
		instrukcja->push((stosOperatorow.current()));
		stosOperatorow.pop();
	}
	kolejkaInstrukcji.push(instrukcja);
	//****
	//**

	//pomocniczy stos
	stack<Number*> stosONP;
	bool toBeDeleted = false;
	bool whileLoop = false;
	bool ifConditional = false;
	czyPrzeciwny = false;
	stack<MathObject*> stosWarunkowy;
	//**
	//****
	//WYKONYWANIE KODU
	while (!kolejkaInstrukcji.empty()) {
		node<queue<MathObject*>*> *node = kolejkaInstrukcji.pop();
		queue<MathObject*> *instrukcja = node->data;
		while (!instrukcja->empty()) {
			MathObject* object = instrukcja->pop()->data;

			if (object->math_type == VARIABLE) {
				//Variable *Var = dynamic_cast<Variable*>(object);
				Tree_node *node = VariableTree->search(VariableTree->root, object->key);
				if (czyPrzeciwny) {
					if (node->var->liczba.value != Nul) {
						stosONP.push(dynamic_cast<Unary*>(OperatorList.tab[15])->operation(&node->var->liczba));
						czyPrzeciwny = false;
						zliczajOperacje++;
					}
				}
				else
					stosONP.push(&node->var->liczba);
			}
			else if (object->math_type == NUMBER) {
				if (czyPrzeciwny) {
					dynamic_cast<Number*>(object)->setValue(-dynamic_cast<Number*>(object)->value);
					stosONP.push(dynamic_cast<Number*>(object));
					czyPrzeciwny = false;
				}
				else
					stosONP.push(dynamic_cast<Number*>(object));
			}
			else if (object->math_type == OPERATOR) {
				if (dynamic_cast<Unary*>(object)) {
					czyPrzeciwny = true;
					continue;
				}

				zliczajOperacje++;
				if (zliczajOperacje >= licznikOperacji)  break;


				Operator *aktualnyOperator = dynamic_cast<Operator*>(object);//OperatorList.getOperator(object->key);
				if (aktualnyOperator->arg_type == ONEARG) {
					Number *A = stosONP.current();
					stosONP.pop();
					stosONP.push(dynamic_cast<NOT*>(aktualnyOperator)->operation(A));
				}
				else {
					Number *A = stosONP.current();
					stosONP.pop();
					Number *B = stosONP.current();
					stosONP.pop();
					stosONP.push(aktualnyOperator->operation(B, A));
				}
			}
			else if (object->math_type == WHILE_LOOP) {
				whileLoop = true;
				stosWarunkowy.push(object);
			}
			else if (object->math_type == CONDITIONAL) {
				stosWarunkowy.push(object);
			}
		}
		if (zliczajOperacje >= licznikOperacji)
			break;
		//oproznianie stosu ONP
		while (stosONP.current()) {
			stosONP.pop();
		}
		if (toBeDeleted) delete instrukcja;
	}

	/*
	if(whileLoop == false || ifConditional == false)
	toBeDeleted = true;
	*/

	cout << zliczajOperacje << endl;
	VariableTree->wypisz_zmienne();

	delete VariableTree;
	delete line;

	//std::cout << endl;
	//system("pause");
	return 0;
}