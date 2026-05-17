#include "myfind.h"
#include <pwd.h>

int     check_name(char *filename, t_args *args)
{
    if (args->name == NULL)
        return (1);
    if (strcmp(filename, args->name) == 0)
        return (1);
    return (0);
}

int     check_type(char *path, t_args *args)
{
    struct stat info;

    if (args->type == NULL)
        return (1);
    if (lstat(path, &info) != 0)
        return (0);
    if (strcmp(args->type, "f") == 0 && S_ISREG(info.st_mode))
        return (1);
    if (strcmp(args->type, "d") == 0 && S_ISDIR(info.st_mode))
        return (1);
    if (strcmp(args->type, "l") == 0 && S_ISLNK(info.st_mode))
        return (1);
    return (0);
}

int     check_size(char *path, t_args *args)
{
    struct stat info;

    if (args->size == -1)
        return (1);
    if (lstat(path, &info) != 0)
        return (0);
    if (info.st_size == args->size)
        return (1);
    return (0);
}

int     check_mtime(char *path, t_args *args)
{
    struct stat info;
    time_t      now;
    int         days;

    if (args->mtime == -1)
        return (1);
    if (lstat(path, &info) != 0)
        return (0);
    now = time(NULL);
    days = (now - info.st_mtime) / 86400;
    if (days == args->mtime)
        return (1);
    return (0);
}

int     check_user(char *path, t_args *args)
{
    struct stat     info;
    struct passwd   *pw;

    if (args->user == NULL)
        return (1);
    if (lstat(path, &info) != 0)
        return (0);
    pw = getpwuid(info.st_uid);
    if (pw == NULL)
        return (0);
    if (strcmp(pw->pw_name, args->user) == 0)
        return (1);
    return (0);
}

int     filter(char *filename, char *path, t_args *args)
{
    if (!check_name(filename, args))
        return (0);
    if (!check_type(path, args))
        return (0);
    if (!check_size(path, args))
        return (0);
    if (!check_mtime(path, args))
        return (0);
    if (!check_user(path, args))
        return (0);
    return (1);
}