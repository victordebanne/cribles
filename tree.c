#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "logic.h"
#include "expression.h"
#include "tree.h"


#define SIZE 20
#define MAX 1024



Node create_node(int role){
    Node n;
    n.role = role;
    n.state = 0;
    if(role < 3 ){
        n.nb_nodes = 1;
        n.nodes = malloc(1 * sizeof(Node));
    }
    else{
        n.nb_nodes = 2;
        n.nodes = malloc(2 * sizeof(Node));
    }
    return n;
}

void init_node(Node *n, int role){
    n->state = 0;
    n->role = role;
    n->value = create_list(0);

    if(role == 0 || role == 2 ){
        n->nb_nodes = 1;
        n->nodes = malloc(1 * sizeof(Node));
    }
    else if(role == 1){
        n->nb_nodes = 0;
    }
    else{
        n->nb_nodes = 2;
        n->nodes = malloc(2 * sizeof(Node));
    }
}

void free_node(Node *n){
    free_list(&n->value);
    free(n->nodes);
}

list resolve(char *string){
    char *extr = extract(string);
    char **res = extract_coma(extr);
    char *a = res[0];
    char *b = res[1];
    int ai = char_to_int(a);
    int bi = char_to_int(b);

    free(extr);
    free(res[0]);
    free(res[1]);
    free(res);


    return cr(ai, bi, SIZE);
}

void create_tree(char *string, Node *n, int i){

    if(string[0] == 'c'){

        init_node(&n->nodes[i], 1);

        n->nodes[i].value = resolve(string);
        n->nodes[i].state = 1;

    }
    else if(string[0] == 'n'){
        init_node(&n->nodes[i], 2);

        char *extr = extract(string);
        create_tree(extr, &n->nodes[i], 0);

        free(extr);
    }
    else if(string[0] == 'i'){
        init_node(&n->nodes[i], 3);

        char *extr = extract(string);
        char **extra = extract_coma(extr);
        
        create_tree(extra[0], &n->nodes[i], 0);
        create_tree(extra[1], &n->nodes[i], 1);
        free(extr);
        free(extra[0]);
        free(extra[1]);
        free(extra);
    }
    else if(string[0] == 'a'){
        init_node(&n->nodes[i], 4);
        
        char *extr = extract(string);
        char **extra = extract_coma(extr);
        
        create_tree(extra[0], &n->nodes[i], 0);
        create_tree(extra[1], &n->nodes[i], 1);
        free(extr);
        free(extra[0]);
        free(extra[1]);
        free(extra);
        
    }
    else{
        printf("erreur dans le balisage de la formule : \n%c, n'existe pas ou est mal placé.\n", string[0]);
    }
}

void compute(Node *n){
    for(int i = 0; i < n->nb_nodes; i++){
        if(n->nodes[i].state == 0){
            compute(&n->nodes[i]);
        }
    }
    if(n->role == 0){
        int size = n->nodes[0].value.size;
        n->value = create_list(size);
        for(int i = 0; i < size; i++){
            n->value.values[i] = n->nodes[0].value.values[i];
        }
        n->state = 1;
    }
    if(n->role == 2){
        n->value = non(&n->nodes[0].value, SIZE);
        n->state = 1;
    }
    if(n->role == 3){
        n->value = inter(&n->nodes[0].value, &n->nodes[1].value);
        n->state = 1;
    }
    if(n->role == 4){
        n->value = add(&n->nodes[0].value, &n->nodes[1].value);
        n->state = 1;
    }
}

void free_tree(Node *n){
    for(int i = 0; i < n->nb_nodes; i++){
        free_tree(&n->nodes[i]);
    }
    free_list(&n->value);   
    if(n->nb_nodes > 0){
        free(n->nodes);      
    }
    if(n->role == 0){
        printf("succes\n");
    }
}

