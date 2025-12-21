#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "logic.h"

list cr(int a, int b, int size_max){
    if(a <= b || a < 0 || b < 0 || b > size_max){
        return create_list(0);
    }
    int card = (size_max - b) / a + 1;
    list l = create_list(card);
    for(int i = 0; i < card; i++){
        l.values[i] = b + i * a;
    }
    return l;
}

list non(list *l, int size_max){
    int card = size_max + 1 - l->size;
    list out = create_list(card);

    int i = 0;
    int j = 0;
    int k = 0;
    while(i < card){
        if(k != l->values[j]){
            out.values[i] = k;
            k++;
            i++;
        }
        else{
            k++;
            if(j < l->size - 1){
            j++;
            }
        }
    }
    return out;
}

list add(list *a, list *b){
    //compteur de valeurs uniques
    int card = 0;
    int ita = 0;
    int itb = 0;
    while(ita < a->size && itb < b->size){
        if(a->values[ita] < b->values[itb]){
            ita++;
            card++;
        }
        else if(a->values[ita] > b->values[itb]){
            itb++;
            card++;
        }
        else{
            ita++;
            itb++;
            card++;
        }
    }
    card += b->size - itb + a->size - ita;
    list out = create_list(card);
    //ajouter les valeurs dans la liste
    int i = 0;
    ita = 0;
    itb = 0;
    while(ita < a->size && itb < b->size){
        if(a->values[ita] < b->values[itb]){
            out.values[i] = a->values[ita];
            ita++, i++;
        }
        else if(a->values[ita] > b->values[itb]){
            out.values[i] = b->values[itb];
            itb++, i++;
        }
        else{
            out.values[i] = b->values[itb];
            ita++;
            itb++;
            i++;
        }
    }
    while(ita < a->size){
        out.values[i] = a->values[ita];
        ita++, i++;
    }
    while(itb < b->size){
        out.values[i] = b->values[itb];
        itb++, i++;
    }
    return out;
}

list inter(list *a, list *b){
    int card = 0;
    int ita = 0;
    int itb = 0;
    while(ita < a->size && itb < b->size){
        if(a->values[ita] < b->values[itb]){
            ita++;
        }
        else if(a->values[ita] > b->values[itb]){
            itb++;
        }
        else{
            ita++;
            itb++;
            card++;
        }
    }
    list out = create_list(card);
    int i = 0;
    ita = 0;
    itb = 0;
    while(ita < a->size && itb < b->size){
        if(a->values[ita] < b->values[itb]){
            ita++;
        }
        else if(a->values[ita] > b->values[itb]){
            itb++;
        }
        else{
            out.values[i] = a->values[ita];
            ita++;
            itb++;
            i++;
        }
    }
    return out;
}

/*
int main(){

    list l = cr(7,0);
    list m = non(&l);
    list n = add(&m, &l);
    display_list(&n);

    return 0;
}
*/