#include "myfind.h"

static int  check_name(char *filename, t_args *args)
{
    if (args->name && fnmatch(args->name, filename, 0) != 0)
        return (0);
    if (args->iname && fnmatch(args->iname, filename, FNM_CASEFOLD) != 0)
        return (0);
    return (1);
}

static int  check_path(char *path, t_args *args)
{
    if (args->fpath && fnmatch(args->fpath, path, 0) != 0)
        return (0);
    if (args->ipath && fnmatch(args->ipath, path, FNM_CASEFOLD) != 0)
        return (0);
    if (args->wholename && fnmatch(args->wholename, path, 0) != 0)
        return (0);
    if (args->iwholename && fnmatch(args->iwholename, path, FNM_CASEFOLD) != 0)
        return (0);
    if (args->regex)
    {
        regex_t reg;
        int     ret;

        if (regcomp(&reg, args->regex, REG_EXTENDED) != 0)
            return (0);
        ret = regexec(&reg, path, 0, NULL, 0);
        regfree(&reg);
        if (ret != 0)
            return (0);
    }
    return (1);
}

static int  check_type(char *path, struct stat *st, t_args *args)
{
    if (args->type)
    {
        if (*args->type == 'f' && !S_ISREG(st->st_mode))  return (0);
        if (*args->type == 'd' && !S_ISDIR(st->st_mode))  return (0);
        if (*args->type == 'l' && !S_ISLNK(st->st_mode))  return (0);
        if (*args->type == 'b' && !S_ISBLK(st->st_mode))  return (0);
        if (*args->type == 'c' && !S_ISCHR(st->st_mode))  return (0);
        if (*args->type == 'p' && !S_ISFIFO(st->st_mode)) return (0);
        if (*args->type == 's' && !S_ISSOCK(st->st_mode)) return (0);
    }
    if (args->xtype)
    {
        struct stat lst;
        stat(path, &lst);
        if (*args->xtype == 'f' && !S_ISREG(lst.st_mode))  return (0);
        if (*args->xtype == 'd' && !S_ISDIR(lst.st_mode))   return (0);
        if (*args->xtype == 'l' && !S_ISLNK(lst.st_mode))   return (0);
    }
    return (1);
}

static int  check_user(struct stat *st, t_args *args)
{
    if (args->user)
    {
        struct passwd *pw = getpwnam(args->user);
        if (!pw || st->st_uid != pw->pw_uid)
            return (0);
    }
    if (args->nouser && getpwuid(st->st_uid) != NULL)
        return (0);
    return (1);
}

static int  check_group(struct stat *st, t_args *args)
{
    if (args->group)
    {
        struct group *gr = getgrnam(args->group);
        if (!gr || st->st_gid != gr->gr_gid)
            return (0);
    }
    if (args->nogroup && getgrgid(st->st_gid) != NULL)
        return (0);
    return (1);
}

static int  check_size(struct stat *st, t_args *args)
{
    if (args->size != -1 && st->st_size != args->size)
        return (0);
    return (1);
}

static int  check_perms(char *path, struct stat *st, t_args *args)
{
    if (args->perm != -1 && (st->st_mode & 0777) != (mode_t)args->perm)
        return (0);
    if (args->readable && access(path, R_OK) != 0)
        return (0);
    if (args->writable && access(path, W_OK) != 0)
        return (0);
    if (args->executable && access(path, X_OK) != 0)
        return (0);
    return (1);
}

static int  check_empty(struct stat *st, t_args *args)
{
    if (args->empty)
    {
        if (S_ISREG(st->st_mode) && st->st_size != 0)
            return (0);
        if (S_ISDIR(st->st_mode) && st->st_nlink > 2)
            return (0);
    }
    return (1);
}

static int  check_links(struct stat *st, t_args *args)
{
    if (args->links != -1 && (int)st->st_nlink != args->links)
        return (0);
    if (args->inum != -1 && (long)st->st_ino != args->inum)
        return (0);
    if (args->samefile)
    {
        struct stat ref;
        if (stat(args->samefile, &ref) == 0 && st->st_ino != ref.st_ino)
            return (0);
    }
    return (1);
}

static int  check_lname(char *path, struct stat *st, t_args *args)
{
    char    buf[1024];
    ssize_t len;

    if (!args->lname && !args->ilname)
        return (1);
    if (!S_ISLNK(st->st_mode))
        return (0);
    len = readlink(path, buf, sizeof(buf) - 1);
    if (len < 0)
        return (0);
    buf[len] = '\0';
    if (args->lname && fnmatch(args->lname, buf, 0) != 0)
        return (0);
if (args->ilname && fnmatch(args->ilname, buf, FNM_CASEFOLD) != 0)
        return (0);
    return (1);
}

static int  check_time(struct stat *st, t_args *args)
{
    time_t  now = time(NULL);

    if (args->mtime != -1)
    {
        int days = (int)((now - st->st_mtime) / 86400);
        if (days != args->mtime)
            return (0);
    }
    if (args->atime != -1)
    {
        int days = (int)((now - st->st_atime) / 86400);
        if (days != args->atime)
            return (0);
    }
    if (args->ctime != -1)
    {
        int days = (int)((now - st->st_ctime) / 86400);
        if (days != args->ctime)
            return (0);
    }
    if (args->mmin != -1)
    {
        int mins = (int)((now - st->st_mtime) / 60);
        if (mins != args->mmin)
            return (0);
    }
    if (args->amin != -1)
    {
        int mins = (int)((now - st->st_atime) / 60);
        if (mins != args->amin)
            return (0);
    }
    if (args->cmin != -1)
    {
        int mins = (int)((now - st->st_ctime) / 60);
        if (mins != args->cmin)
            return (0);
    }
    if (args->newer)
    {
        struct stat ref;
        if (stat(args->newer, &ref) == 0 && st->st_mtime <= ref.st_mtime)
            return (0);
    }
    if (args->newerat)
    {
        struct stat ref;
        if (stat(args->newerat, &ref) == 0 && st->st_atime <= ref.st_atime)
            return (0);
    }
    if (args->newermt)
    {
        struct tm   tm = {0};
        strptime(args->newermt, "%Y-%m-%d", &tm);
        time_t ref = mktime(&tm);
        if (st->st_mtime <= ref)
            return (0);
    }
    return (1);
}

int filter(char *filename, char *path, struct stat *st, t_args *args)
{
    if (!check_name(filename, args))     return (0);
    if (!check_path(path, args))         return (0);
    if (!check_type(path, st, args))     return (0);
    if (!check_user(st, args))           return (0);
    if (!check_group(st, args))          return (0);
    if (!check_size(st, args))           return (0);
    if (!check_perms(path, st, args))    return (0);
    if (!check_empty(st, args))          return (0);
    if (!check_links(st, args))          return (0);
    if (!check_lname(path, st, args))    return (0);
    if (!check_time(st, args))           return (0);
    return (1);
}