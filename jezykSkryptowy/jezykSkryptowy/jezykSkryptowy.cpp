#pragma once

#include "Queue.h"
#include "Stack.h"
//#include "Operatory.h"
#include "tree.h"
#include "OperatorTable.h"

using namespace std;

#define max 1000

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
	bool czyCyfra;
	if (znak >= '0' && znak <= '9')
		return true;
	else
		return false;
}


//funkcja oblicza wyniki wyrazenia w ONP
int CalculateONP() { return 0; }

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
	char character = '0';
	char *nazwaZmiennej = new char[max];
	Tree *variableTree = new Tree();

	//**
	//formatowanie
	cin.getline(nazwaZmiennej, max);
	//**

	//**
	//*****
	//Funkcja dodaj¹ca zmienne na drzewo binarne 'variableTree'
	int i = 0;
	while (character != '\n' && character != '\r') {
		cin.get(character);
		if (character == ' ' || character == '\n' || character == '\r') {

			*(nazwaZmiennej + i) = '\0';
			//dodawanie obiektu 'tmp' typu variable do 'variableTree'
			variable tmp;
			tmp.toDisplay = true;
			tmp.key = nazwaZmiennej;
			variableTree->add(tmp);
			zliczajZmienne++;

			nazwaZmiennej = new char[max];
			i = 0;
		}
		else {
			*(nazwaZmiennej + i) = character;
			i++;
		}
	}
	//****
	//**


	//kolejka instrukcji, ktore sa kolejkami wyrazen
	queue<queue<char*>*> kolejkaInstrukcji;
	//przechowuje rozdzielone wyrazenia JEDNEJ instrukcji zapisane w kolejnoœci ONP
	queue<char*> *instrukcja;
	//stos operatorow potrzebny do konwersji na ONP
	stack<o::Operator*> stosOperatorow;
	//tablica wszystkich dostepnych operatorow
	OperatorTable OperatorList;

	char *nazwaWyrazenia = new char[max];
	char *line = new char[max];
	char znak = *line;

	i = 0;

	//**
	//****
	//Konwersja z notacji infiksowej do ONP / rozdzielanie wyrazen na instrukcje
	
	instrukcja = new queue<char*>();
	bool nowaInstrukcja = false;
	
	if (1) { 
		cin.getline(line, max);
		
		//warunki rozdzielenia instrukcji w whilu (naprawic)
		while (1) {

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

			//Zmienne
			if (czyLitera(znak)) {
				while (czyLitera(*(line + i + 1))) {
					i++;
					*(nazwaWyrazenia + ++j) = *(line + i);
				}
				//i++;
				*(nazwaWyrazenia + ++j) = '\0';
				
				//
				if (nowaInstrukcja) {
					//Konwersja na ONP
					while (stosOperatorow.current()) {
						instrukcja->push((stosOperatorow.current()->id));
						stosOperatorow.pop();
					}

					kolejkaInstrukcji.push(instrukcja);
					instrukcja = new queue<char*>();
				}
				nowaInstrukcja = true;
				//

				tree_node* zmienna;
				zmienna = variableTree->search(variableTree->root, nazwaWyrazenia);
				if (zmienna) {
					instrukcja->push(zmienna->var.key);
				}
				else {
					variable tmp;
					tmp.key = nazwaWyrazenia;
					variableTree->add(tmp);
					instrukcja->push(tmp.key);
					zliczajZmienne++;
				}
			}
			//Liczby
			else if (czyCyfra(znak)) {
				while (czyCyfra(*(line + i + 1))) {
					*(nazwaWyrazenia + ++j) = *(line + ++i);
				}

				//
				if (nowaInstrukcja) {
					//Konwersja na ONP
					while (stosOperatorow.current()) {
						instrukcja->push((stosOperatorow.current()->id));
						stosOperatorow.pop();
					}

					kolejkaInstrukcji.push(instrukcja);
					instrukcja = new queue<char*>();
				}
				nowaInstrukcja = true;
				//

				*(nazwaWyrazenia + j + 1) = '\0';
				instrukcja->push(nazwaWyrazenia);

			}
			else if (znak == '(') {
				stosOperatorow.push(new o::lnawias());
			}
			else if (znak == ')') {
				while (stosOperatorow.current()->id != "(") {
					instrukcja->push(stosOperatorow.current()->id);
					stosOperatorow.pop();
				}
				stosOperatorow.pop();
			}
			//Operatory
			else {
				if (*(line + i + 1) == '=') {
					*(nazwaWyrazenia + ++j) = *(line + ++i);
					//tutaj bedzie operator liczby ujemnej!

				}

				*(nazwaWyrazenia + ++j) = '\0';
				o::Operator *aktualnyOperator = OperatorList.getOperator(nazwaWyrazenia);

				while (stosOperatorow.current() && aktualnyOperator->priority <= stosOperatorow.current()->priority) {
					instrukcja->push((stosOperatorow.current()->id));
					stosOperatorow.pop();
				}
				stosOperatorow.push(aktualnyOperator);
				nowaInstrukcja = false;

			}
			//resetuj tablice
			nazwaWyrazenia = new char[max];
			i++;
		}
		i = 0;
	}
	//****
	//**


	//dla ostatniej instrukcji
	//Konwersja na ONP
	while (stosOperatorow.current()) {
		instrukcja->push((stosOperatorow.current()->id));
		stosOperatorow.pop();
	}
	kolejkaInstrukcji.push(instrukcja);

	//Wypisywanie rzeczy z kolejkiInstrukcji
	/*while (!kolejkaInstrukcji.empty()) {
		node<queue<char*>*> *node = kolejkaInstrukcji.pop();
		queue<char*> *instrukcja = node->data;
		while (!instrukcja->empty()) {
			cout << (instrukcja->pop()->data) << " ";
		}
		cout << endl;

	}*/

	//pomocniczy stos
	stack<variable> OperatorONP;

	////instrukcja
	//while (!kolejkaInstrukcji.empty()) {
	//	node<queue<char*>*> *node = kolejkaInstrukcji.pop();
	//	queue<char*> *instrukcja = node->data;
	//	while (!instrukcja->empty()) {
	//		char zn = *instrukcja->pop()->data;

	//		if (czyLitera(zn) || czyCyfra(zn)) {
	//			OperatorONP.push(instrukcja->current());
	//			instrukcja->pop();
	//		}
	//		else {

	//			tree* szukany = search(root, onp.current());
	//			char *wynik = new char[max];
	//			onp.pop();

	//			o::Operator *op = getOperator(instrukcja->current());
	//			if (dynamic_cast<o::NOT*>(op)) {
	//				int wynik_int = dynamic_cast<o::NOT*>(op)->operation(szukany->var);


	//				onp.push();
	//				B = onp.current();
	//				onp.pop();
	//			}
	//			else if (dynamic_cast<o::assign*>(op))
	//			else {

	//				onp.push(op->operation();
	//			}
	//			//
	//		}
	//		cout << instrukcja->current() << " ";

	//	}

	//	
		
	//}


	//tree* szukany = search(root, "abc");
	//
	//if (szukany != NULL) {
	//	cout << "Znaleziono: " << szukany->var.key << " => ";
	//	cout << szukany->var << endl;
	//}

	delete line;
	delete nazwaWyrazenia;
	delete nazwaZmiennej;
	std::cout << endl;
	system("pause");
	//return 0;
}


//	if (zliczajOperacje >= licznikOperacji)
//		break;
//	//	if ()
//	cout << name;
//	//if ()
//}