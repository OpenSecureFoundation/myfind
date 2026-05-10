#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

typedef struct s_file
{
    char *name;
    long size;
    time_t mod_time;
} t_file;

void swap_files(t_file *a, t_file *b)
{
    t_file temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/*
** TRI ALPHABÉTIQUE
*/
void sort_by_name(t_file files[], int count)
{
    int i;
    int j;

    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(files[i].name, files[j].name) > 0)
            {
                swap_files(&files[i], &files[j]);
            }
        }
    }
}

/*
** TRI PAR TAILLE
*/
void sort_by_size(t_file files[], int count)
{
    int i;
    int j;

    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (files[i].size > files[j].size)
            {
                swap_files(&files[i], &files[j]);
            }
        }
    }
}

/*
** TRI PAR DATE
*/
void sort_by_date(t_file files[], int count)
{
    int i;
    int j;

    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (files[i].mod_time > files[j].mod_time)
            {
                swap_files(&files[i], &files[j]);
            }
        }
    }
}