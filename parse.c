#include "myfind.h"

t_args *parse_args(int argc, char **argv)
{
    t_args *args;
    int i;

    args = malloc(sizeof(t_args));
    if (!args)
        return NULL;
    args->path = argv[1];
    args->name = NULL;
    i = 2;
    while (i < argc)
    {
        if (strcmp(argv[i], "-name") == 0 && i + 1 < argc)
        {
            args->name = argv[i + 1];
            i++;
        }
        i++;
    }
    return args;
}