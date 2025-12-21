#ifndef LOGIC2_H
#define LOGIC2_H

#include "array.h"

list cr(int a, int b, int size_max);

list non(list *l, int size_max);

list add(list *a, list *b);

list inter(list *a, list *b);

/*
int main(){

    list l = cr(7,0);
    list m = non(&l);
    list n = add(&m, &l);
    display_list(&n);

    return 0;
}
*/

#endif