#ifndef TREE_H
#define TREE_H

#include "array.h"

typedef struct Node{
    list value; //contient les valeurs retournées par les fonctions 
    int role; //1 feuilles, 2 non, 3 inter, 4 union, 0 root
    int nb_nodes;
    struct Node *nodes; //contient les enfants
    int state; //les fonctions ont elles été calculées
} Node;

Node create_node(int role);

void init_node(Node *n, int role);

void free_node(Node *n);

list resolve(char *string);

void create_tree(char *string, Node *n, int i);

void compute(Node *n);

void free_tree(Node *n);

#endif