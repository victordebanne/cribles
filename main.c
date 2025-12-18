#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "array.h"
#include "logic.h"
#include "arbre.h"

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

void tutoriel(){
    printf(
        "\n\n\n\n\n\n\n\n========== TUTORIEL ==========\n"
        "XEN\n"
        "Version 1.2\n\n"

        "Ce logiciel en ligne de commande permet de generer des suites\n"
        "a l'aide d'operateurs d'algebre des ensembles inpire par Xenakis\n"

        "Les suites sont definies a l'aide de la fonction :\n"
        "    c(a,b)\n\n"

        "Exemple :\n"
        "    c(3,1) = 1, 4, 7, 10, 13, ...\n\n"

        "--------------------------------\n"
        "SYNTAXE GENERALE\n"
        "--------------------------------\n\n"

        "x union y        -> a(x, y)\n"
        "x intersection y -> i(x, y)\n"
        "non x            -> n(x)\n\n"

        "Exemple :\n"
        "    3(1) + (3(2) inter 3(4))\n"
        "s'ecrit :\n"
        "    a(c(3,1), i(c(3,2), c(3,4)))\n\n"

        "Les espaces sont autorises dans les expressions.\n"
        "Les erreurs de syntaxe sont detectees et n'entrainent\n"
        "pas le crash du programme.\n\n"

        "--------------------------------\n"
        "EXEMPLE AVANCE \n"
        "--------------------------------\n\n"

        "Expression du crible de Nommos Alpha :\n\n"
        "a(i(n(a(a(a(c(13,3),c(13,5)),c(13,7)),c(13,9))),c(11,2)),a(i(n(a(c(11,4),c(11,8))),c(13,9)),a(c(13,0),a(c(13,1),c(13,6)))))\n\n"
       

        "--------------------------------\n"
        "BIBLIOGRAPHIE\n"
        "--------------------------------\n\n"

        "- Theorie des cribles (Iannis Xenakis) :\n"
        "  https://www.iannis-xenakis.org/theorie-des-cribles/\n\n"

        "- Andreatta, Moreno (2005) :\n"
        "  http://recherche.ircam.fr/equipes/repmus/moreno/AndreattaENSTBretagne2005.pdf\n\n"

        "--------------------------------\n"
        "FIN DU TUTORIEL\n"
        "--------------------------------\n"
    );
}


char *get_input(){
    char expr[MAX];
    fgets(expr, MAX, stdin);
    char *a = strip(expr);

    return a;
}

void compute_input(char *input){
    Node root;
    init_node(&root, 0);

    int err = create_tree2(&root, input, 0);
    if(err == 0){
        compute(&root);
        sort(&root.l);
        printf("\n   votre crible : \n   -------------- \n\n");
        display_list(&root.l);
        printf("\n");
    }
    else{
        printf("/!\\ERREUR : \n");
    }

    free_tree(&root);
    free(input);
    printf("programme execute avec succes\n");
}

char *treat_get_input(char *input){
    int len = string_length(input);
    char *a = malloc((len) * sizeof(char));
    for(int i = 0; i < (len - 1); i++){
        a[i] = input[i];
    }
    a[len - 1] = '\0';

 
    return a;
}


int main(){

    printf("\n====================\nCalculateur de Cribles\n====================\n");


    while(1){

    printf("\nentrer une expression, q pour quitter, t pour le tutoriel\n---------------------------------------------------------\nvotre entree  : ");

    //char expr[] = "a(i(n(a(a(a(c(13,3),c(13,5)),c(13,7)),c(13,9))),c(11,2)),a(i(n(a(c(11,4),c(11,8))),c(13,9)),a(c(13,0),a(c(13,1),c(13,6)))))";
    
    char *input = get_input();
    char *a = treat_get_input(input);
    char *b = strip(a);

    free(input);
    free(a);

    if(b[0] == 'q'){
        free(b);
        break;
    }

    if(b[0] == 't'){
        free(b);
        tutoriel();
    }

    else{
        compute_input(b);
    }

}
    
    printf("\n====================\nfin du programme\n====================\n\n");
    

    return 0;
}