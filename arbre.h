#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"



typedef struct Node{
    list l;
    int role;
    int nb_nodes;
    int is_init;
    struct Node *nodes;
    int computed;
}Node;

list resolve(char *string);

void init_node(Node *n, int role);

int create_tree(Node *n, int size);

int create_tree2(Node *n, char *string, int i);

void free_tree(Node *n);

void compute(Node *n);

/*
int main(){

    Node root;
    init_node(&root, 0);

    char expr[] = "a(i(c(3,1),c(2,1)),c(5,1))";

    int err = create_tree2(&root, expr, 0);
    if(err == 0){
        compute(&root);
        sort(&root.l);
        display_list(&root.l);
    }

    free_tree(&root);
    printf("ok\n");
    return 0;
}
*/

#endif
