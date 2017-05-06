#include <iostream>
using namespace std;



typedef struct list {
	int data;
	list *next;
};

bool empty(list *head) {
	if (head == NULL) return 1;
	else return 0;
}

list *addNew(list *& head, list *&last, int data) {
	list *tmp = new list;
	tmp->data = data;
	tmp->next = NULL;

	return tmp;
}

//push function
void add(list *& head, list *&last, int data) {
	if (empty(head)) {
		list *tmp = addNew(head, last, data);
		head = tmp;
		last = tmp;
	}
	else {
		list *tmp = addNew(head, last, data);
		last->next = tmp;
		last = tmp;
	}
}

//pop function
void del(list *&head, list *&last) {
	if (empty(head)) return;    // list is empty
	else if (head == last) {
		cout << head->data;
		delete head;
		head == NULL;
		last == NULL;
	}
	else {
		list *tmp = head;
		cout << head->data;
		head = head->next;
		delete tmp;
	}
}

void showAll(list *head, list *last) {
	int i = 0; // counting size of given list
	while (!empty(head)) {
		if (head == last)
			cout << head->data << endl;
		else
			cout << head->data << "->";
		head = head->next;
		i++;
	}
}