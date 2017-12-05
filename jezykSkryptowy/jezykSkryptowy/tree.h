#include "operatory.h"
#include <cstring>
 
class Tree_node {
public:
        Tree_node *left, *right, *parent, *next;
        Variable *var;
        Tree_node(Variable* var) : left(NULL), right(NULL), var(var)
        { }
};
 
class Tree {
public:
        Tree_node* root;
        queue<Variable*> variableList;
 
        Tree() : root(NULL) {};
        void add(Variable* tmp) {
                if (root != NULL)
                        insert(root, tmp);
                else {
                        root = new Tree_node(tmp);
                        root->parent = NULL;
                }
                variableList.push(tmp);
        }
 
        void insert(Tree_node *node, Variable* newVar) {
 
                if (strcmp(node->var->key, newVar->key) == 0)
                        return; //if names match
 
                int i = 0;
 
                if (strcmp(node->var->key, newVar->key) < 0) {
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
 
        Tree_node* search(Tree_node* node, char* name) {
                if (node == NULL)
                        return NULL;
 
                if (strcmp(node->var->key, name) == 0)
                        return node; //if names match
 
                int i = 0;
 
                if (strcmp(node->var->key, name) < 0)
                        return search(node->right, name);
                else
                        return search(node->left, name);
        }
 
        void wypisz_zmienne() {
                while (!variableList.empty()) {
                        node<Variable*> *n = variableList.pop();
 
                        if (n->data->toDisplay == true) {
                                std::cout << n->data->key << " ";
                                if (n->data->liczba.value == Nul)
                                        std::cout << "Nul";
                                else
                                        std::cout << n->data->liczba.value;
                                std::cout << std::endl;
                        }
                        
                        delete n; 
                }
        }
};
