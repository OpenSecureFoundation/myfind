#ifndef MYFIND_H
# define MYFIND_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <regex.h>
# include <fnmatch.h>

typedef struct s_args
{
    /* ── Chemin racine ── */
    char    *path;

    /* ── Déjà présentes ── */
    char    *name;
    char    *type;
    char    *user;
    long    size;
    int     mtime;

    /* ── Temps ── */
    int     atime;
    int     ctime;
    char    *newer;
    char    *newermt;
    int     amin;
    int     mmin;
    int     cmin;
    char    *newerat;

    /* ── Filtres fichiers ── */
    int     perm;
    int     empty;
    int     readable;
    int     writable;
    int     executable;
    char    *iname;
    char    *fpath;
    char    *ipath;
    char    *regex;
    char    *group;
    int     nogroup;
    int     nouser;
    long    inum;
    int     links;
    int     maxdepth;
    int     mindepth;
    char    *samefile;
    char    *xtype;
    char    *lname;
    char    *ilname;
    char    *wholename;
    char    *iwholename;

    /* ── Actions ── */
    int     do_print;
    int     do_print0;
    int     do_ls;
    int     do_delete;
    char    *exec_cmd;
    char    *execdir_cmd;
    int     do_ok;
    char    *printf_fmt;
    char    *fprint_file;
    int     do_quit;
    char    *fprint0_file;
    char    *fprintfmt_file;
    int     exit_code;

    /* ── Logique ── */
    int     do_and;
    int     do_or;
    int     do_not;
    int     do_prune;

    /* ── Global ── */
    int     do_depth;
    int     do_xdev;
}   t_args;

/* ── Prototypes ── */
t_args  *parse_args(int argc, char **argv);
void    traverse(char *path, t_args *args, int depth);
int     filter(char *filename, char *path, struct stat *st, t_args *args);
void    display(char *path, struct stat *st, t_args *args);

#endif