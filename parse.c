#include "myfind.h"

t_args  *parse_args(int argc, char **argv)
{
    t_args  *args;
    int     i;

    if (argc < 2)
    {
        printf("Usage: ./myfind <path> [options]\n");
        return (NULL);
    }

    args = malloc(sizeof(t_args));
    if (!args)
        return (NULL);

    args->path = argv[1];
    args->name = NULL;
    args->type = NULL;
    args->user = NULL;
    args->size = -1;
    args->mtime = -1;

    i = 2;

    while (i < argc)
    {
        if (strcmp(argv[i], "-name") == 0 && i + 1 < argc)
        {
            args->name = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-type") == 0 && i + 1 < argc)
        {
            args->type = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-user") == 0 && i + 1 < argc)
        {
            args->user = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-size") == 0 && i + 1 < argc)
        {
            args->size = atol(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-mtime") == 0 && i + 1 < argc)
        {
            args->mtime = atoi(argv[i + 1]);
            i++;
        }
        else
        {
            printf("Unknown or incomplete option: %s\n", argv[i]);
        }

        i++;
    }

    return (args);
}