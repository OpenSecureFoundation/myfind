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

typedef struct s_args
{
    char    *path;
    char    *name;
    char    *type;
    char    *user;
    long    size;
    int     mtime;
}   t_args;

// prototypes
t_args  *parse_args(int argc, char **argv);
void    traverse(char *path, t_args *args);
int     filter(char *filename, char *path, t_args *args);
void    display(char *path);

#endif