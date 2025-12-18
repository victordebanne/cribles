#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    int size;
    int *values;
} list;

list create_list(int size);

void free_list(list *l);

void append(list *l,int d);

void concat(list *a, list *b);

void display_list(list *l);

void sort(list *a);

list list_error();

#endif