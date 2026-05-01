#include "myfind.h"

int main(int argc, char **argv)
{
    t_args *args;

    if (argc < 2)
    {
        write(2, "Usage: ./myfind <path> [-name pattern]\n", 39);
        return 1;
    }
    args = parse_args(argc, argv);
    if (!args)
        return 1;
    traverse(args->path, args);
    free(args);
    return 0;
}