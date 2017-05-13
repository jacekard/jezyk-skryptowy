#include "operatory.h"
#include <cstring>

class Tree_node {
public:
	Tree_node *left, *right, *parent;
	Variable *var;
	Tree_node(Variable* var) : left(NULL), right(NULL), var(var)
	{ }
};

class Tree {
public:
	Tree_node* root;
	Tree() : root(NULL) {};
	~Tree() {
		//usuwanie wszystkich elementow drzewa
		deleteAll(root);
	}
	void add(Variable* tmp) {
		if (root != NULL)
			insert(root, tmp);
		else {
			root = new Tree_node(tmp);
			root->parent = NULL;
		}
	}

	void insert(Tree_node *node, Variable* newVar) {
		//if names match
		if (strcmp(node->var->key, newVar->key) == 0)
			return;
		int i = 0;
		while (*(node->var->key + i) != '\0' && *(newVar->key + i) != '\0') {
			if (*(node->var->key + i) == *(newVar->key + i))
				i++;
			else break;
		}
		if (*(node->var->key + i) < *(newVar->key + i)) {
			if (node->right)
				insert(node->right, newVar);
			else {
				node->right = new Tree_node(newVar);
				node->right->parent = node;
			}
		}
		else {
			if (node->left)
				insert(node->left, newVar);
			else {
				node->left = new Tree_node(newVar);
				node->left->parent = node;
			}
		}
	}

	Tree_node* search(Tree_node* node, char* name)
	{
		if (node == NULL)
			return NULL;
		//if names match
		if (strcmp(node->var->key, name) == 0)
			return node;
		int i = 0;
		while (*(node->var->key + i) == *(name + i)) {
				i++;
		}
		if (*(node->var->key + i) < *(name + i))
			return search(node->right, name);
		else
			return search(node->left, name);
	}

	void wypisz_zmienne(Tree_node *n) {
		if (n == NULL) return;

		if (n->var->toDisplay == true) {
			std::cout << n->var->key << " ";
			if (n->var->liczba.value == Nul)
				std::cout << "Nul";
			else
				std::cout << n->var->liczba.value;
			std::cout << std::endl;
		}
		wypisz_zmienne(n->left);
		wypisz_zmienne(n->right);
	}

	void deleteAll(Tree_node *node) {
		if (node == NULL) return;
		deleteAll(node->left);
		deleteAll(node->right);

		delete node;
	}

	//void wypisz_wierzcholki(Tree_node *n) {
	//	while (n != NULL) {
	//		printf("%d ", n->var->key);
	//		n = n->parent;
	//	}
	//}
};



//int wysokosc(Tree_node* N) {
//	if (N == NULL) return -1;
//	int a = wysokosc(N->right);
//	int b = wysokosc(N->left);
//
//	if (a >= b) return wysokosc(N->right) + 1;
//	else return wysokosc(N->left) + 1;
//}
//


//
//int wypisz_l_wierzch(Tree_node *n) {
//	int i = 0;
//	while (n != NULL) {
//		i++;
//		n = n->parent;
//	}
//	return i;
//}

//char *suma_lisci(Tree_node* n) {
//	if (!n->left && !n->right) return n->var.key;
//	char *a = suma_lisci(n->left);
//	char *b = suma_lisci(n->right);
//
//	return a + b;
//}