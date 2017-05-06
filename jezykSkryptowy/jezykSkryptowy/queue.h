#pragma once

#include "Node.h"

template <class T>
class queue {
public:
	node<T> *head;
	node<T> *last;

	queue() {
		head = NULL;
		last = NULL;
	}

	bool empty() {
		if (head == NULL) return 1;
		else return 0;
	}

	node<T> *add_new(T data) {
		node<T> *tmp = new node<T>;
		tmp->data = data;
		tmp->next = NULL;

		return tmp;
	}

	//push function
	void add(T data) {
		if (empty()) {
			node<T> *tmp = add_new(data);
			head = tmp;
			last = tmp;
		}
		else {
			node<T> *tmp = add_new(data);
			last->next = tmp;
			last = tmp;
		}
	}

	//pop function
	void del() {
		if (empty()) return;
		else if (head == last) {
			//cout << head->data;
			delete head;
			head = NULL;
			last = NULL;
		}
		else {
			node<T> *tmp = head;
			//cout << head->data;
			head = head->next;
			delete tmp;
		}
	}

	T current() {
		if (!empty())
			return head->data;
		else return NULL;
	}

	//returns size of elements
	int rozmiar() {
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
