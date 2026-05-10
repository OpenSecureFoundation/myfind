#include <stdio.h>
#include <time.h>

typedef struct s_file
{
    char *name;
    long size;
    time_t mod_time;
} t_file;

void sort_by_name(t_file files[], int count);
void sort_by_size(t_file files[], int count);
void sort_by_date(t_file files[], int count);

void display_files(t_file files[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        printf(
            "%s | size: %ld | date: %ld\n",
            files[i].name,
            files[i].size,
            files[i].mod_time
        );
    }

    printf("\n");
}

int main()
{
    t_file files[] = {
        {"zebra.txt", 500, 1700000000},
        {"apple.txt", 100, 1500000000},
        {"main.c", 300, 1600000000}
    };

    int count = 3;

    printf("=== TRI ALPHABETIQUE ===\n");
    sort_by_name(files, count);
    display_files(files, count);

    printf("=== TRI PAR TAILLE ===\n");
    sort_by_size(files, count);
    display_files(files, count);

    printf("=== TRI PAR DATE ===\n");
    sort_by_date(files, count);
    display_files(files, count);

    return 0;
}