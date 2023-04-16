#ifndef args_h
#define args_h
#include <string.h>
#include <stdio.h>

struct option {
    const char *flag;
    int has_argument;
    void *fn;
};


void parse_args(int arg_count, char **arg_vec, const struct option *options, int options_length);


#endif
