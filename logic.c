#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int in_array(list *a, int j){
    for(int i = 0; i < a->size; i++){
        if(a->values[i] == j){
            return 1;
        }
    }
    return 0;
}

list non(list *a, int size){
    list l = create_list(0);
    for(int i = 0; i < size; i++){
        if(!in_array(a, i)){
            append(&l, i);
        }
    }
    return l;
}

list inter(list *a, list *b){
    list l = create_list(0);
    for(int i = 0; i < a->size; i++){
        if(in_array(b, a->values[i])){
            append(&l, a->values[i]);
        }
    }
    return l;
}

list cr(int div, int rest, int size){
    list l = create_list(0);
    for(int i = 0; i < size; i++){
        if(i % div == rest){
            append(&l, i);
        }
    }
    return l;
}

list add(list *a, list *b){
    list l = create_list(0);
    for(int i = 0; i < a->size; i++){
        if(!in_array(&l, a->values[i])){
            append(&l, a->values[i]);
        }
    }
    for(int i = 0; i < b->size; i++){
        if(!in_array(&l, b->values[i])){
            append(&l, b->values[i]);
        }
    }
    return l;
}


/*
int main(){
    int size = 20;
    list a = cr(13, 6, size);
    display_list(&a);
    free_list(&a);
    return 0;
}
*/