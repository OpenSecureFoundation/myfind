#include "myfind.h"

static void traverse_dir(char *path, t_args *args, int depth, dev_t root_dev)
{
    DIR             *dir;
    struct dirent   *entry;
    struct stat     st;
    char            fullpath[PATH_MAX];

    dir = opendir(path);
    if (!dir)
    {
        perror(path);
        return ;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue ;
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (lstat(fullpath, &st) < 0)
        {
            perror(fullpath);
            continue ;
        }

        /* -xdev : ne pas traverser d'autres systèmes de fichiers */
        if (args->do_xdev && st.st_dev != root_dev)
            continue ;

        /* -maxdepth : ne pas descendre plus loin */
        if (args->maxdepth != -1 && depth > args->maxdepth)
            continue ;

        /* -depth : traiter le contenu avant le dossier lui-même */
        if (args->do_depth && S_ISDIR(st.st_mode))
        {
            if (args->do_prune == 0)
                traverse_dir(fullpath, args, depth + 1, root_dev);
            if (args->mindepth == -1 || depth >= args->mindepth)
                if (filter(entry->d_name, fullpath, &st, args))
                {
                    display(fullpath, &st, args);
                    if (args->do_quit)
                    {
                        closedir(dir);
                        exit(args->exit_code != -1 ? args->exit_code : 0);
                    }
                }
        }
        else
        {
            if (args->mindepth == -1 || depth >= args->mindepth)
                if (filter(entry->d_name, fullpath, &st, args))
                {
                    display(fullpath, &st, args);
                    if (args->do_quit)
                    {
                        closedir(dir);
                        exit(args->exit_code != -1 ? args->exit_code : 0);
                    }
                }
            if (S_ISDIR(st.st_mode) && args->do_prune == 0)
                traverse_dir(fullpath, args, depth + 1, root_dev);
        }
    }
    closedir(dir);
}

void    traverse(char *path, t_args *args, int depth)
{
    struct stat st;
    dev_t       root_dev;

    if (lstat(path, &st) < 0)
    {
        perror(path);
        return ;
    }
    root_dev = st.st_dev;
    if (args->mindepth == -1 || depth >= args->mindepth)
        if (filter(path, path, &st, args))
            display(path, &st, args);
    if (S_ISDIR(st.st_mode))
        traverse_dir(path, args, depth + 1, root_dev);
}