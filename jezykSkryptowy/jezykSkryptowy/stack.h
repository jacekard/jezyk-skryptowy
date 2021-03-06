#pragma once
 
#include "Node.h"
 
template <class T>
class stack {
public:
        node<T> *stackPtr;
 
        stack() : stackPtr(NULL) {}
 
        bool empty(node<T> *p) {
                return !p;
        }
 
        void push(T data) {
                node<T> *nowy = new node<T>;
                nowy->data = data;
                nowy->next = stackPtr;
                stackPtr = nowy;
        }
        void pop() {
                if (!empty(stackPtr)) {
                        node<T> *temp = new node<T>;
                        temp = stackPtr;
                        stackPtr = stackPtr->next;
                        delete temp;
                }
        }
        void wypisz() {
                node<T> *tmp = stackPtr;
                while (!empty(tmp)) {
                        printf("%d ", tmp->data);
                        tmp = tmp->next;
                }
        }
        T current() {
                if (!empty(stackPtr))
                        return stackPtr->data;
                else return NULL;
        }
        T previous() {
                if (stackPtr->next != NULL)
                        return stackPtr->next->data;
                else return NULL;
        }
 
        T prevprevious() {
                if (stackPtr->next->next != NULL)
                        return stackPtr->next->next->data;
                else return NULL;
        }
 
        int rozmiar() {
                node<T> *tmp = stackPtr;
                int a = 0;
                while (!empty(tmp)) {
                        a++;
                        tmp = tmp->next;
                }
                return a;
        }
 
};
