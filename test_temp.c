#include "myfind.h"

int     filter(char *filename, t_args *args)
{
    if (args->name == NULL)
        return (1);
    if (strcmp(filename, args->name) == 0)
        return (1);
    return (0);
}

void    display(char *path)
{
    printf("%s\n", path);
}