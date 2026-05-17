#include "myfind.h"

void traverse(char *path, t_args *args)
{
    DIR             *dir;
    struct dirent   *entry;
    struct stat     info;
    char            full_path[1024];

    dir = opendir(path);
    if (dir == NULL)
    {
        perror(path);
        return ;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue ;
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (filter(entry->d_name, full_path, args))
            display(full_path);
        if (lstat(full_path, &info) == 0 && S_ISDIR(info.st_mode))
            traverse(full_path, args);
    }
    closedir(dir);
}