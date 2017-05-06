#include "operatory.h"


class tree
{
public:
	tree *left, *right, *parent;
	variable var;
	tree(variable var) : left(NULL), right(NULL), var(var)
	{ }
};

void insert(tree *N, variable var) {
	if (N->var.key == var.key)
		return;
	if (N->var.key < var.key) {
		if (N->right)
			insert(N->right, var);
		else {
			N->right = new tree(var);
			N->right->parent = N;
		}
	}
	else {
		if (N->left)
			insert(N->left, var);
		else {
			N->left = new tree(var);
			N->left->parent = N;
		}
	}
}


tree* search(tree* N, char* name)
{
	if (N == NULL)
		return NULL;
	if (*(N->var.key) == *name)
		return N;
	if (*(N->var.key) < *name)
		return search(N->right, name);
	else
		return search(N->left, name);
}

//int wysokosc(tree* N) {
//	if (N == NULL) return -1;
//	int a = wysokosc(N->right);
//	int b = wysokosc(N->left);
//
//	if (a >= b) return wysokosc(N->right) + 1;
//	else return wysokosc(N->left) + 1;
//}
//
void wypisz_inorder(tree *n) {
	if (n == NULL) return;
	wypisz_inorder(n->left);

	std::cout << n->var.key << " => ";
	if (n->var.isNul == true)
		std::cout << "Nul" << std::endl;
	else
		std::cout << n->var.value << std::endl;

	wypisz_inorder(n->right);

}
//
//void wypisz_wierzcholki(tree *n) {
//	while (n != NULL) {
//		printf("%d ", n->var->key);
//		n = n->parent;
//	}
//}
//
//int wypisz_l_wierzch(tree *n) {
//	int i = 0;
//	while (n != NULL) {
//		i++;
//		n = n->parent;
//	}
//	return i;
//}

//char *suma_lisci(tree* n) {
//	if (!n->left && !n->right) return n->var.key;
//	char *a = suma_lisci(n->left);
//	char *b = suma_lisci(n->right);
//
//	return a + b;
//}


//std::ostream& operator<<(std::ostream &os, const tree& a) {
//	if (a.var.value)
//		os << "Nul";
//	else
//		os << var.value;
//
//	return os;
//}