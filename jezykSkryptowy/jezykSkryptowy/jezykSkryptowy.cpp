#pragma once
 
#include "Queue.h"
#include "Stack.h"
#include "tree.h"
#include "OperatorTable.h"
#include "Instruction.h"
 
/*
Declaration in "zmienne.h":
#define OPERATOR_COUNT 16
#define Nul -858993460
#define max 1000
int zliczajOperacje = 0;
int licznikOperacji = 0;
*/
 
 
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
        stack<Instruction*> &stosWarunkowy,
        Instruction *&instrukcja,
        queue<Instruction*> &kolejkaInstrukcji,
        bool isLast) {
 
        if (instrukcja->output->empty())
                return;
 
        while (stosOperatorow.current()) {
                instrukcja->output->push((stosOperatorow.current()));
                stosOperatorow.pop();
        }
 
 
        if (stosWarunkowy.current() == NULL)
                kolejkaInstrukcji.push(instrukcja);
        else if (stosWarunkowy.current()->inst_type == WHILE_LOOP)
                dynamic_cast<While*>(stosWarunkowy.current())->kolejkaInstrukcji->push(instrukcja);
        else if (stosWarunkowy.current()->inst_type == CONDITION) {
                dynamic_cast<Condition*>(stosWarunkowy.current())->kolejkaInstrukcji->push(instrukcja);
        }
        if (isLast == false)
                instrukcja = new SingleInstruction();
}
 
Variable* addNewVariable(char *nazwa, Tree *VariableTree, int isDeclared) {
        Variable *tmp = new Variable(nazwa);
        if (isDeclared)
                tmp->toDisplay = true;
        VariableTree->add(tmp);
        return tmp;
}
 
int main() {
 
        //**
        cin >> licznikOperacji;
        //**
 
        int zliczajZmienne = 0;
        char *nazwaWyrazenia = new char[max];
        char *line = new char[max];
        char znak = *line;
        Tree *VariableTree = new Tree();
 
        //**
        cin.getline(line, max);
        //**
 
        //**
        //*****
        //Funkcja dodaj�ca zmienne na drzewo binarne 'VariableTree'
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
        a. PRZECIWNO�� JAKO OPERACJA JEST TYLKO PRZED ZMIENNA
        b. przed liczba to do liczby
        */
 
        //tablica wszystkich dostepnych operatorow
        OperatorTable OperatorList;
        //kolejka instrukcji, ktore sa kolejkami wyrazen
        queue<Instruction*> kolejkaInstrukcji;
        //przechowuje rozdzielone wyrazenia JEDNEJ instrukcji zapisane w kolejno�ci ONP
        Instruction *instrukcja;
        //stos operatorow potrzebny do konwersji na ONP
        stack<Operator*> stosOperatorow;
        stack<Instruction*> stosWarunkowy;
 
        //**
        //****
        //Konwersja z notacji infiksowej do ONP / rozdzielanie wyrazen na instrukcje
        znak = *line;
        i = 0;
 
        instrukcja = new SingleInstruction();
        bool nowaInstrukcja = false;
        bool czyOperand = false;
        bool czyPrzeciwny = false;
 
        while (cin.getline(line, max)) {
                //for (int x = 0; x < 2; x++) {
                //      cin.getline(line, max);
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
 
                        //ZMIENNE//
                        if (czyLitera(znak)) {
                                while (czyLitera(*(line + i + 1))) {
                                        *(nazwaWyrazenia + ++j) = *(line + ++i);
                                }
                                *(nazwaWyrazenia + ++j) = '\0';
 
                                if (nowaInstrukcja) {
                                        addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, false);
                                }
 
                                nowaInstrukcja = true;
                                czyOperand = true;
 
                                Tree_node* node = VariableTree->search(VariableTree->root, nazwaWyrazenia);
                                if (node) {
                                        instrukcja->output->push(node->var);
                                }
                                else {
                                        Variable *newVar = addNewVariable(nazwaWyrazenia, VariableTree, false);
                                        instrukcja->output->push(newVar);
                                }
                        }
                        //***
                        //LICZBY//
                        else if (czyCyfra(znak)) {
                                while (czyCyfra(*(line + i + 1))) {
                                        *(nazwaWyrazenia + ++j) = *(line + ++i);
                                }
                                *(nazwaWyrazenia + j + 1) = '\0';
 
                                if (nowaInstrukcja)
                                        addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, false);
 
                                nowaInstrukcja = true;
                                czyOperand = true;
 
                                Number *liczba = new Number(nazwaWyrazenia);
                                instrukcja->output->push(liczba);
                        }
                        //***
                        else if (znak == '@') {
                                if (!instrukcja->output->empty())
                                        addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, false);
 
                                Instruction *instWarunkowa = new While();
                                stosWarunkowy.push(instWarunkowa);
 
                                nowaInstrukcja = false;
                                czyOperand = false;
                        }
                        else if (znak == '?') {
                                if (!instrukcja->output->empty())
                                        addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, false);
 
                                Instruction *instWarunkowa = new Condition();
                                stosWarunkowy.push(instWarunkowa);
 
                                nowaInstrukcja = false;
                                czyOperand = false;
                        }
                        else if (znak == '{') {
                                /*      instrukcja->output->push(new BegNawias());*/
                                nowaInstrukcja = true;
                                czyOperand = false;
                        }
                        else if (znak == '}') {
                                if (!instrukcja->output->empty())
                                        addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, false);
 
                                if (stosWarunkowy.previous()) {
                                        if (stosWarunkowy.previous()->inst_type == WHILE_LOOP)
                                                dynamic_cast<While*>(stosWarunkowy.previous())->kolejkaInstrukcji->push(stosWarunkowy.current());
                                        if (stosWarunkowy.previous()->inst_type == CONDITION)
                                                dynamic_cast<Condition*>(stosWarunkowy.previous())->kolejkaInstrukcji->push(stosWarunkowy.current());
                                }
                                else
                                        kolejkaInstrukcji.push(stosWarunkowy.current());
 
                                stosWarunkowy.pop();
 
                                nowaInstrukcja = true;
                                czyOperand = false;
                        }
                        else if (znak == '(') {
                                if (czyOperand == true)
                                        addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, false);
 
                                stosOperatorow.push(new LewyNawias());
                                czyOperand = false;
                                nowaInstrukcja = false;
                        }
                        else if (znak == ')') {
 
                                while (!dynamic_cast<LewyNawias*>(stosOperatorow.current())) {
                                        instrukcja->output->push(stosOperatorow.current());
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
 
                                *(nazwaWyrazenia + ++j) = '\0';
                                Operator *aktualnyOperator = OperatorList.getOperator(nazwaWyrazenia);
 
                                czyPrzeciwny = false;
 
                                if (*aktualnyOperator->key == '-') {
                                        if (czyOperand == false) {
                                                instrukcja->output->push(OperatorList.tab[15]);
 
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
                                                instrukcja->output->push((stosOperatorow.current()));
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
        if (!instrukcja->output->empty())
                addNewInstruction(stosOperatorow, stosWarunkowy, instrukcja, kolejkaInstrukcji, true);
 
 
 
        //****
        //**
 
        //**
        //WYKONANIE KODU
        while (!kolejkaInstrukcji.empty()) {
                if (zliczajOperacje >= licznikOperacji)
                        break;
 
                node<Instruction*> *node = kolejkaInstrukcji.pop();
                node->data->SpecialExecute(OperatorList);
                delete node;
        }
        //**
 
        cout << zliczajOperacje << endl;
        VariableTree->wypisz_zmienne();
 
 
        //zwalnianie pamieci:
        for (int i = 0; i < OPERATOR_COUNT; i++) {
                delete OperatorList.tab[i];
        }
        delete OperatorList.tab;
 
        delete instrukcja;
        delete VariableTree;
        delete line;
 
 
        return 0;
}
