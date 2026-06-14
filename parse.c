#include "myfind.h"

static void init_args(t_args *args, char *path)
{
    args->path         = path;

    /* Déjà présentes */
    args->name         = NULL;
    args->type         = NULL;
    args->user         = NULL;
    args->size         = -1;
    args->mtime        = -1;

    /* Temps */
    args->atime        = -1;
    args->ctime        = -1;
    args->newer        = NULL;
    args->newermt      = NULL;
    args->amin         = -1;
    args->mmin         = -1;
    args->cmin         = -1;
    args->newerat      = NULL;

    /* Filtres fichiers */
    args->perm         = -1;
    args->empty        = 0;
    args->readable     = 0;
    args->writable     = 0;
    args->executable   = 0;
    args->iname        = NULL;
    args->fpath        = NULL;
    args->ipath        = NULL;
    args->regex        = NULL;
    args->group        = NULL;
    args->nogroup      = 0;
    args->nouser       = 0;
    args->inum         = -1;
    args->links        = -1;
    args->maxdepth     = -1;
    args->mindepth     = -1;
    args->samefile     = NULL;
    args->xtype        = NULL;
    args->lname        = NULL;
    args->ilname       = NULL;
    args->wholename    = NULL;
    args->iwholename   = NULL;

    /* Actions */
    args->do_print     = 1;
    args->do_print0    = 0;
    args->do_ls        = 0;
    args->do_delete    = 0;
    args->exec_cmd     = NULL;
    args->execdir_cmd  = NULL;
    args->do_ok        = 0;
    args->printf_fmt   = NULL;
    args->fprint_file  = NULL;
    args->do_quit      = 0;
    args->fprint0_file = NULL;
    args->fprintfmt_file = NULL;
    args->exit_code    = -1;

    /* Logique */
    args->do_and       = 0;
    args->do_or        = 0;
    args->do_not       = 0;
    args->do_prune     = 0;

    /* Global */
    args->do_depth     = 0;
    args->do_xdev      = 0;
}

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
    init_args(args, argv[1]);

    i = 2;
    while (i < argc)
    {
        /* ══ Déjà présentes ══ */
        if (strcmp(argv[i], "-name") == 0 && i + 1 < argc)
            { args->name = argv[++i]; }
        else if (strcmp(argv[i], "-type") == 0 && i + 1 < argc)
            { args->type = argv[++i]; }
        else if (strcmp(argv[i], "-user") == 0 && i + 1 < argc)
            { args->user = argv[++i]; }
        else if (strcmp(argv[i], "-size") == 0 && i + 1 < argc)
            { args->size = atol(argv[++i]); }
        else if (strcmp(argv[i], "-mtime") == 0 && i + 1 < argc)
            { args->mtime = atoi(argv[++i]); }

        /* ══ Temps ══ */
        else if (strcmp(argv[i], "-atime") == 0 && i + 1 < argc)
            { args->atime = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-ctime") == 0 && i + 1 < argc)
            { args->ctime = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-newer") == 0 && i + 1 < argc)
            { args->newer = argv[++i]; }
        else if (strcmp(argv[i], "-newermt") == 0 && i + 1 < argc)
            { args->newermt = argv[++i]; }
        else if (strcmp(argv[i], "-amin") == 0 && i + 1 < argc)
            { args->amin = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-mmin") == 0 && i + 1 < argc)
            { args->mmin = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-cmin") == 0 && i + 1 < argc)
            { args->cmin = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-newerat") == 0 && i + 1 < argc)
            { args->newerat = argv[++i]; }

        /* ══ Filtres fichiers ══ */
        else if (strcmp(argv[i], "-perm") == 0 && i + 1 < argc)
            { args->perm = (int)strtol(argv[++i], NULL, 8); }
        else if (strcmp(argv[i], "-empty") == 0)
            { args->empty = 1; }
        else if (strcmp(argv[i], "-readable") == 0)
            { args->readable = 1; }
        else if (strcmp(argv[i], "-writable") == 0)
            { args->writable = 1; }
        else if (strcmp(argv[i], "-executable") == 0)
            { args->executable = 1; }
        else if (strcmp(argv[i], "-iname") == 0 && i + 1 < argc)
            { args->iname = argv[++i]; }
        else if (strcmp(argv[i], "-path") == 0 && i + 1 < argc)
            { args->fpath = argv[++i]; }
        else if (strcmp(argv[i], "-ipath") == 0 && i + 1 < argc)
            { args->ipath = argv[++i]; }
        else if (strcmp(argv[i], "-regex") == 0 && i + 1 < argc)
            { args->regex = argv[++i]; }
        else if (strcmp(argv[i], "-group") == 0 && i + 1 < argc)
            { args->group = argv[++i]; }
        else if (strcmp(argv[i], "-nogroup") == 0)
            { args->nogroup = 1; }
        else if (strcmp(argv[i], "-nouser") == 0)
            { args->nouser = 1; }
        else if (strcmp(argv[i], "-inum") == 0 && i + 1 < argc)
            { args->inum = atol(argv[++i]); }
        else if (strcmp(argv[i], "-links") == 0 && i + 1 < argc)
            { args->links = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-maxdepth") == 0 && i + 1 < argc)
            { args->maxdepth = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-mindepth") == 0 && i + 1 < argc)
            { args->mindepth = atoi(argv[++i]); }
        else if (strcmp(argv[i], "-samefile") == 0 && i + 1 < argc)
            { args->samefile = argv[++i]; }
        else if (strcmp(argv[i], "-xtype") == 0 && i + 1 < argc)
            { args->xtype = argv[++i]; }
        else if (strcmp(argv[i], "-lname") == 0 && i + 1 < argc)
            { args->lname = argv[++i]; }
        else if (strcmp(argv[i], "-ilname") == 0 && i + 1 < argc)
            { args->ilname = argv[++i]; }
        else if (strcmp(argv[i], "-wholename") == 0 && i + 1 < argc)
            { args->wholename = argv[++i]; }
        else if (strcmp(argv[i], "-iwholename") == 0 && i + 1 < argc)
            { args->iwholename = argv[++i]; }

        /* ══ Actions ══ */
        else if (strcmp(argv[i], "-print") == 0)
            { args->do_print = 1; }
        else if (strcmp(argv[i], "-print0") == 0)
            { args->do_print0 = 1; args->do_print = 0; }
        else if (strcmp(argv[i], "-ls") == 0)
            { args->do_ls = 1; }
        else if (strcmp(argv[i], "-delete") == 0)
            { args->do_delete = 1; }
        else if (strcmp(argv[i], "-exec") == 0 && i + 1 < argc)
            { args->exec_cmd = argv[++i]; }
        else if (strcmp(argv[i], "-execdir") == 0 && i + 1 < argc)
            { args->execdir_cmd = argv[++i]; }
        else if (strcmp(argv[i], "-ok") == 0 && i + 1 < argc)
            { args->exec_cmd = argv[++i]; args->do_ok = 1; }
        else if (strcmp(argv[i], "-printf") == 0 && i + 1 < argc)
            { args->printf_fmt = argv[++i]; args->do_print = 0; }
        else if (strcmp(argv[i], "-fprint") == 0 && i + 1 < argc)
            { args->fprint_file = argv[++i]; }
        else if (strcmp(argv[i], "-quit") == 0)
            { args->do_quit = 1; }
        else if (strcmp(argv[i], "-fprint0") == 0 && i + 1 < argc)
            { args->fprint0_file = argv[++i]; }
        else if (strcmp(argv[i], "-fprintfmt") == 0 && i + 1 < argc)
            { args->fprintfmt_file = argv[++i]; }
        else if (strcmp(argv[i], "-exit") == 0 && i + 1 < argc)
            { args->exit_code = atoi(argv[++i]); }

        /* ══ Logique ══ */
        else if (strcmp(argv[i], "-and") == 0 || strcmp(argv[i], "-a") == 0)
            { args->do_and = 1; }
        else if (strcmp(argv[i], "-or") == 0 || strcmp(argv[i], "-o") == 0)
            { args->do_or = 1; }
        else if (strcmp(argv[i], "-not") == 0 || strcmp(argv[i], "!") == 0)
            { args->do_not = 1; }
        else if (strcmp(argv[i], "-prune") == 0)
            { args->do_prune = 1; }

        /* ══ Global ══ */
        else if (strcmp(argv[i], "-depth") == 0)
            { args->do_depth = 1; }
        else if (strcmp(argv[i], "-xdev") == 0)
            { args->do_xdev = 1; }

        else
            printf("Unknown or incomplete option: %s\n", argv[i]);

        i++;
    }

    return (args);
}