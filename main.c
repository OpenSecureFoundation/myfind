#include "myfind.h"

int main(int argc, char **argv)
{
    t_args      *args;
    struct stat st;
    int         ret;

    if (argc < 2)
    {
        write(2, "Usage: ./myfind <path> [options]\n", 33);
        return (1);
    }
    args = parse_args(argc, argv);
    if (!args)
        return (1);

    /* Vérifie que le point de départ existe avant de lancer le parcours,
     * afin de renvoyer un code de sortie != 0 (comme find) en cas
     * de chemin invalide, tout en laissant traverse() gerer ses
     * propres erreurs internes (sous-dossiers, permissions, etc.). */
    if (lstat(args->path, &st) < 0)
    {
        perror(args->path);
        free(args);
        return (1);
    }

    traverse(args->path, args, 0);

    /* -exit <code> : code de sortie explicite demande par l'utilisateur,
     * meme si -quit n'a pas ete declenche pendant le parcours. */
    ret = (args->exit_code != -1) ? args->exit_code : 0;
    free(args);
    return (ret);
}