#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/*
typedef struct {
    int size;
    double *values;
} list;
*/

list create_list(int size){
    list l;
    l.size = size;
    l.values = malloc(size*sizeof(int));
    return l;
}

void free_list(list *l){
    free(l->values);
}

void append(list *l, int d){
    l->values = realloc(l->values, (l->size + 1) * sizeof(int));
    l->values[l->size] = d;
    l->size += 1;
}

void concat(list *a, list *b){
    a->values = realloc(a->values, (a->size + b->size) * sizeof(int));
    for(int i = 0; i < b->size; i++){
        a->values[a->size + i] = b->values[i];
    }
    a->size += b->size;
}

void display_list(list *l){
    printf("[");
    for (int i = 0; i < l->size; i++){
        printf("%d", l->values[i]);
        if(i < l->size - 1){
            printf(", ");
        }
    }
    printf("]\n");
}

void sort(list *a){
    int i = 1;
    while(i < a->size){
        if(a->values[i] < a->values[i-1]){
            int b = a->values[i];
            int c = a->values[i-1];
            a->values[i - 1] = b;
            a->values[i] = c;
            i = 1;
        }
        else{
            i++;
        }
    }
}
