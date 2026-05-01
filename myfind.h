#ifndef MYFIND_H
# define MYFIND_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>

typedef struct s_args
{
    char *path;
    char *name;
}   t_args;

// prototypes
t_args  *parse_args(int argc, char **argv);
void    traverse(char *path, t_args *args);
int     filter(char *filename, t_args *args);
void    display(char *path);

#endif