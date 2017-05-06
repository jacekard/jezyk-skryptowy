#pragma once
#include <iostream>

template <class T>
class node {
public:
	T data;
	node<T> *next;

	node<T>() {
		data = NULL;
		next = NULL;
	}
};