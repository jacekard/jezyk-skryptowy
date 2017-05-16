#pragma once

#include "Node.h"

template <class T>
class queue {
	node < T > *backup;
public:
	node<T> *head;
	node<T> *last;
	node<T> *first;

	queue() : head(NULL), last(NULL) {}

	~queue() {
		//while (!empty()) {
		//	deleteElement();
		//}
	}
	void remember(){
		backup = first;
	}
	void recall(){
		first = backup;
		head = backup;
	}
	bool empty() {
		if (head == NULL) return 1;
		else return 0;
	}

	node<T> *addNewElement(T data) {
		node<T> *tmp = new node<T>;
		tmp->data = data;
		tmp->next = NULL;
		return tmp;
	}

	void push(T data) {
		if (!empty()) {
			node<T> *tmp = addNewElement(data);
			last->next = tmp;
			last = tmp;
		}
		else {
			node<T> *tmp = addNewElement(data);
			head = tmp;
			last = tmp;
			first = tmp;
		}
	}

	node<T>* pop() {
		if (!empty()) {
			node<T> *tmp = head;
			head = head->next;
			return tmp;
		}
		else return NULL;
	}

	node<T>* currentElement() {
		if (!empty())
			return head;
		else return NULL;
	}

	node<T>* firstElement() {
		if (!empty())
			return first;
		else return NULL;
	}

	int sizeOfQueue() {
		node<T> *tmp = head;
		int a = 0;
		if (head == NULL) return 0;
		else if (head == last) return 1;

		while (tmp != NULL) {
			a++;
			tmp = tmp->next;
		}

		return a;
	}

	void deleteElement() {
		if (empty()) return;
		else if (head == last) {
			delete head;
			head = NULL;
			last = NULL;
		}
		else {
			node<T> *tmp = head;
			head = head->next;
			delete tmp;
		}
	}


};


//void showAll(queue_node *head, queue_node *last) {
//	int i = 0; // counting size of given queue_node
//	while (!empty(head)) {
//		if (head == last)
//			cout << head->data << endl;
//		else
//			cout << head->data << "->";
//		head = head->next;
//		i++;
//	}
//}
