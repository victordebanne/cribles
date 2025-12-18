#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "expression.h"
#include "logic.h"
#include "arbre.h"

#define TREE_ERROR -1
#define VALID_TREE 0
#define SIZE 130

/*
typedef struct Node{
    list l;
    int role;
    int nb_nodes;
    int is_init;
    struct Node *nodes;
    int computed;
}Node;
*/

list resolve(char *string){
    char *extr = extract(string);
    if(extr == NULL){

        return list_error();
    }
    char **res = extract_coma(extr);
    if(res == NULL){
        free(extr);
        return list_error();
    }
    char *a = res[0];
    char *b = res[1];
    int ai = char_to_int(a);
    if(ai == -1){
        free(extr);
        free(res[0]);
        free(res[1]);
        free(res);
        return list_error();
    }
    int bi = char_to_int(b);
    if(bi == -1){
        free(extr);
        free(res[0]);
        free(res[1]);
        free(res);
        return list_error();
    }

    free(extr);
    free(res[0]);
    free(res[1]);
    free(res);

    return cr(ai, bi, SIZE);
}

void init_node(Node *n, int role){
    n->is_init = 1;
    n->role = role;
    n->computed = 0;

    //root
    if(role == 0){
        n->nb_nodes = 1;
        n->nodes = malloc(n->nb_nodes * sizeof(Node));
        n->l.size = 0;
        n->l.values = NULL;
    }

    //feuilles
    if(role == 1){
        n->nb_nodes = 0;
        n->nodes = NULL;
        n->l.size = 0;
        n->l.values = NULL;
    }

    //non
    if(role == 2){
        n->nb_nodes = 1;
        n->nodes = malloc(n->nb_nodes * sizeof(Node));
        n->l.size = 0;
        n->l.values = NULL;
    }

    //inter
    if(role == 3){
        n->nb_nodes = 2;
        n->nodes = malloc(n->nb_nodes * sizeof(Node));
        n->l.size = 0;
        n->l.values = NULL;
    }
    
    //union
    if(role == 4){
        n->nb_nodes = 2;
        n->nodes = malloc(n->nb_nodes * sizeof(Node));
        n->l.size = 0;
        n->l.values = NULL;
    }
        
    //les enfants sont initialisés vides
    for(int i = 0; i < n->nb_nodes; i++){
        n->nodes[i].is_init = 0;
        n->nodes[i].computed = 0;
        n->nodes[i].nodes = NULL;
        n->nodes[i].l.values = NULL;
        n->nodes[i].l.size = 0;
    }
}

int create_tree(Node *n, int size){
    if(size < 1){
        return VALID_TREE;
    }
    for(int i = 0; i < n->nb_nodes; i++){
        Node *new_node = &n->nodes[i];
        init_node(new_node, 1);
        int err = create_tree(new_node, size - 1);
        if(err == TREE_ERROR){
            printf("error");
            return TREE_ERROR;
        }
    }
    return VALID_TREE;
}

int create_tree2(Node *n, char *string, int i){

    if(string[0] == 'c'){
        Node *new_node = &n->nodes[i];
        init_node(new_node, 1);
        new_node->l = resolve(string);
        if(new_node->l.size == -1){
            printf("error\n");
            return TREE_ERROR;
        }
        new_node->computed = 1;
    }
    
    else if(string[0] == 'n'){
        Node *new_node = &n->nodes[i];
        init_node(new_node, 2);
        char *expr = extract(string);
        if(expr == NULL){
            return TREE_ERROR;
        }
        int err = create_tree2(new_node, expr, 0);
        if(err == TREE_ERROR){
            printf("error\n");
            return TREE_ERROR;
        }
    }
    
    else if(string[0] == 'i'){
        Node *new_node = &n->nodes[i];
        init_node(new_node, 3);
        char *expr = extract(string);
        if(expr == NULL){
            printf("error\n");
            return TREE_ERROR;
        }
        char **extra = extract_coma(expr);
        if(extra == NULL){
            free(expr);
            return TREE_ERROR;
        }
        int err1 = create_tree2(new_node, extra[0], 0);
        int err2 = create_tree2(new_node, extra[1], 1);
        if(err1 == TREE_ERROR || err2 == TREE_ERROR){
            printf("error\n");
            return TREE_ERROR;
        }
    }

    else if(string[0] == 'a'){
        Node *new_node = &n->nodes[i];
        init_node(new_node, 4);
        char *expr = extract(string);
        if(expr == NULL){
            printf("error\n");
            return TREE_ERROR;
        }
        char **extra = extract_coma(expr);
        if(extra == NULL){
            free(expr);
            printf("error\n");
            return TREE_ERROR;
        }
        int err1 = create_tree2(new_node, extra[0], 0);
        int err2 = create_tree2(new_node, extra[1], 1);
        if(err1 == TREE_ERROR || err2 == TREE_ERROR){
            printf("error\n");
            return TREE_ERROR;
        }
    }
    else{
        printf("erreur de balisage %s\n", string);
        return TREE_ERROR;
    }

    return VALID_TREE;
}

void free_tree(Node *n){
    for(int i = 0; i < n->nb_nodes; i++){
        if(n->nodes[i].is_init == 1){
            free_tree(&n->nodes[i]);
        } 
    }
    free(n->nodes);
    n->nodes = NULL;
    free(n->l.values);
    n->l.values = NULL;
    n->is_init = 0;
}

void compute(Node *n){
    for(int i = 0; i < n->nb_nodes; i++){
        if(n->nodes[i].computed == 0){
            compute(&n->nodes[i]);
        }
    }
    if(n->role == 2){
        n->l = non(&n->nodes[0].l, SIZE);
        n->computed = 1;
    }

    if(n->role == 3){
        n->l = inter(&n->nodes[0].l, &n->nodes[1].l);
        n->computed = 1;
    }

    if(n->role == 4){
        n->l = add(&n->nodes[0].l, &n->nodes[1].l);
        n->computed = 1;
    }

    if(n->role == 0){
        //deepcopy du noeud supérieur
        n->l.size = n->nodes[0].l.size;
        n->l.values = malloc(n->l.size * sizeof(int));
        for(int j = 0; j < n->l.size; j++){
            n->l.values[j] = n->nodes[0].l.values[j];
        } 
        n->computed = 1;
    }
}

/*
int main(){

    Node root;
    init_node(&root, 0);

    char expr[] = "c(7,0)";

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



