#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "array.h"
#include "logic.h"
#include "tree.h"

#define MAX 1024
/* 
Le but de ce programme est de pouvoir écrire en entrée une suite d'instructions sous la forme de fonctions 

ces fonctions sont au nombre de 3 : 
- cr()
- inter()
- non()

ainsi que l'addition '+' inférant l'union

ces fonctions sont définies dans le module "logic.h" 
et la concaténation '+' ou union fait parti du module "array.h"

l'utilisateur entrera une formule tu type inter(non(cr(a, b) + cr(c, d)), cr(e, f)) 

*/

char *get_input(){
    char expr[MAX];
    fgets(expr, MAX, stdin);
    char *a = strip(expr);

    return a;
}

void compute_input(char *input){
    Node root = create_node(0);
    create_tree(input, &root, 0);
    compute(&root);
    sort(&root.value);
    display_list(&root.value);

 
    free_tree(&root);
    free(input);
}


int main(){
    
    printf("\n====================\nCalculateur de Cribles\n====================\n\n");
    printf("entrer expression : ");
    //char expr[] = "a(i( n(a(  a(a(c(13, 3), c(13,5)) ,c(13,7)), c(13, 9))), c(11,2)),a(i(n(a(c(11, 4), c(11, 8))), c(13, 9)), a(c(13, 0), a(c(13,1), c(13, 6)))))";
    
    char *input = get_input();

    compute_input(input);

    
    printf("\n====================\nfin du programme\n====================\n\n");

    return 0;
}