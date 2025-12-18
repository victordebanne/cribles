#include <stdio.h>
#include <stdlib.h>
#include "expression.h"


int string_length(char *string){
    //retourne la longueur d'une chaine terminée par '\0'
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

char *strip(char *string){
    //cette fonction permet de retirer les ' ' d'une chaine
    //la chaine se terminera par '\0'
    int i = 0;
    int j = 0;
    int len = string_length(string);
    char *out = malloc((len + 1)*sizeof(char));
    while(i < len){
        if(string[i] != ' '){
            out[j] = string[i];
            j ++;
            i ++;
        } 
        else{
            i ++;
        }
    }
    out[j] = '\0';

  
    return out;
}

char *extract(char *string){
    //cette fonction permet de retirer la balise et les parenthèses
    //expression d'entrée a(c(1,2),c(3,4))
    //expression de sortie c(1,2),c(3,4)
    int len = string_length(string);
    if(len < 4){
        printf("expression incorrecte : %s", string);
        return NULL;
    }
    char *extr = malloc((len - 2) * sizeof(char)); //len - 3 + 1 
    for(int i = 2; i < len - 1; i++){
        extr[i - 2] = string[i];
    }
    extr[len-3] = '\0';
    return extr;
}

char **extract_coma(char *string){
    //cette fonction sépare une string en deux quand elle est séparée par une virgule
    //elle repère la virgule hors des parenthèses car plusieurs expressions peuvent être
    //imbriquées
    int len = string_length(string);
    char **extracted = malloc(2 * sizeof(char*));
    int p = 0; 
    int i = 0;
    while(string[i] != ',' || p != 0){
        if(i == len){
            if(p != 0){
                printf("erreur de parenthèses : %s", string);
                return NULL;
            }
            else{
                printf("il manque un argument : %s", string);
                return NULL;
            }
        }
        if(string[i] == '('){
            p++;
            i++;
        }
        else if(string[i] == ')'){
            p--;
            i++;
        }
        else{
            i++;
        }
    }

    extracted[0] = malloc((i + 1) * sizeof(char)); //on ajoute 1 pour le '\0'
    for(int j = 0; j < i; j++){
        extracted[0][j] = string[j];
    }
    extracted[0][i] = '\0';
    i++; //incrémentation pour passer la virgule

    extracted[1] = malloc((len - i + 1) * sizeof(char));
    for(int j = 0; j < len - i; j++){
        extracted[1][j] = string[i + j];
    }
    extracted[1][len - i] = '\0'; //correction d'une unité
    

    return extracted;
}

int char_to_int(char *string){
    int len = string_length(string);
    for (int j = 0; j < len; j++){
        if (string[j] < '0' || string[j] > '9'){
            printf("Value error : '%s'\n", string);
            return -1;
        }
    }
    int i = atoi(string);
    return i;
}


/*
int main(){
    char s[] = " c( 13, 0) ";
    char *a = strip(s);     //c(13,0)
    char *b = extract(a);   //13,0
    char **c = extract_coma(b); //13   puis   0


    printf("%s\n", c[0]);
    printf("%s\n", c[1]);

    free(a);
    free(b);
    free(c[0]);
    free(c[1]);
    free(c);
    
    return 0;
}
*/