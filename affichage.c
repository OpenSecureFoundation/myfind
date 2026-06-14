#include "myfind.h"
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>
#include <libgen.h>  // pour basename()

static void display_ls(char *path, struct stat *st)
{
    char            timebuf[64];
    char            modebuf[11];
    struct passwd   *pw;
    struct group    *gr;

    /* Permissions */
    modebuf[0] = S_ISDIR(st->st_mode)  ? 'd' :
                 S_ISLNK(st->st_mode)  ? 'l' :
                 S_ISBLK(st->st_mode)  ? 'b' :
                 S_ISCHR(st->st_mode)  ? 'c' :
                 S_ISFIFO(st->st_mode) ? 'p' :
                 S_ISSOCK(st->st_mode) ? 's' : '-';
    modebuf[1] = (st->st_mode & S_IRUSR) ? 'r' : '-';
    modebuf[2] = (st->st_mode & S_IWUSR) ? 'w' : '-';
    modebuf[3] = (st->st_mode & S_IXUSR) ? 'x' : '-';
    modebuf[4] = (st->st_mode & S_IRGRP) ? 'r' : '-';
    modebuf[5] = (st->st_mode & S_IWGRP) ? 'w' : '-';
    modebuf[6] = (st->st_mode & S_IXGRP) ? 'x' : '-';
    modebuf[7] = (st->st_mode & S_IROTH) ? 'r' : '-';
    modebuf[8] = (st->st_mode & S_IWOTH) ? 'w' : '-';
    modebuf[9] = (st->st_mode & S_IXOTH) ? 'x' : '-';
    modebuf[10] = '\0';

    /* Propriétaire et groupe */
    pw = getpwuid(st->st_uid);
    gr = getgrgid(st->st_gid);

    /* Date de modification */
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st->st_mtime));

    printf("%s %2lu %-8s %-8s %8ld %s %s\n",
        modebuf,
        (unsigned long)st->st_nlink,
        pw ? pw->pw_name : "unknown",
        gr ? gr->gr_name : "unknown",
        (long)st->st_size,
        timebuf,
        path);
}

static void display_printf(char *path, struct stat *st, char *fmt)
{
    char *p = fmt;

    while (*p)
    {
        if (*p == '%' && *(p + 1))
        {
            p++;
            if (*p == 'p')      printf("%s", path);
            else if (*p == 'f') printf("%s", basename(path));
            else if (*p == 's') printf("%ld", (long)st->st_size);
            else if (*p == 'i') printf("%lu", (unsigned long)st->st_ino);
            else if (*p == 'l') printf("%u", (unsigned)st->st_nlink);
            else if (*p == 'm') printf("%o", (unsigned)(st->st_mode & 0777));
            else if (*p == 'u') {
                struct passwd *pw = getpwuid(st->st_uid);
                printf("%s", pw ? pw->pw_name : "unknown");
            }
            else if (*p == 'g') {
                struct group *gr = getgrgid(st->st_gid);
                printf("%s", gr ? gr->gr_name : "unknown");
            }
            else if (*p == 'T') {
                char timebuf[64];
                strftime(timebuf, sizeof(timebuf), "%b %d %H:%M",
                    localtime(&st->st_mtime));
                printf("%s", timebuf);
            }
            else
                printf("%%%c", *p);
        }
        else if (*p == '\\' && *(p + 1))
        {
            p++;
            if (*p == 'n')      printf("\n");
            else if (*p == 't') printf("\t");
            else if (*p == '\\') printf("\\");
            else                printf("\\%c", *p);
        }
        else
            printf("%c", *p);
        p++;
    }
}

static void display_fprint(char *path, char *file, char delim)
{
    FILE *f = fopen(file, "a");
    if (!f)
    {
        perror(file);
        return ;
    }
    fprintf(f, "%s%c", path, delim);
    fclose(f);
}

void    display(char *path, struct stat *st, t_args *args)
{
    /* -delete */
    if (args->do_delete)
    {
        if (S_ISDIR(st->st_mode))
            rmdir(path);
        else
            unlink(path);
        return ;
    }

    /* -ls */
    if (args->do_ls)
    {
        display_ls(path, st);
        return ;
    }

    /* -printf */
    if (args->printf_fmt)
    {
        display_printf(path, st, args->printf_fmt);
        return ;
    }

    /* -fprint */
    if (args->fprint_file)
        display_fprint(path, args->fprint_file, '\n');

    /* -fprint0 */
    if (args->fprint0_file)
        display_fprint(path, args->fprint0_file, '\0');

    /* -print0 */
    if (args->do_print0)
    {
        printf("%s", path);
        putchar('\0');
        return ;
    }

    /* -print (défaut) */
    if (args->do_print)
        printf("%s\n", path);
}