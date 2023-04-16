#include "args.h"

void parse_args(int arg_count, char **arg_vec, const struct option *options, int options_length) {
    for (int i = 0; i < arg_count; i++)
    {
        for (int j = 0; j < options_length; j++){
            if (strcmp(arg_vec[i], options[j].flag) == 0) {
                printf("match with %s\n", options[j].flag);
                if (options[j].has_argument)
                    // cast fn to void(char*) and pass the next argumnent.
                    ((void (*)(char*))options[j].fn)(arg_vec[i+1]);
                else
                    // cast fn to void() and call it.
                    ((void (*)())options[j].fn)();
            }

        }
        
    }
}
