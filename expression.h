#ifndef EXPR_H
#define EXPR_H

#include <stdio.h>
#include <stdlib.h>


int string_length(char *string);

char *strip(char *string);

char *extract(char *string);

char **extract_coma(char *string);

int char_to_int(char *string);



#endif