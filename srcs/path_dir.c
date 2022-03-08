#include "../include/minishell.h"

void	get_path(void)
{
        if (getcwd(NULL, 0) == NULL)
                perror("getcwd() error");
        else
                printf("%s\n", getcwd(NULL, 0));
}

char *clean_str(char *path)
{
        int		i;
        int		j;
        char	*final;

        i = 0;
        j = 0;
        while (path[i] && !is_letter(path[i]))
                if (path[i] == ' ')
                        i++;
        final = malloc(sizeof(char) * (ft_strlen(path) - i) + 1);
        while (path[i])
        {
                final[j++] = path[i];
                i++;
        }
        final[j] = '\0';
        return (final);
}

int	search_slash(char *path)
{
        int	i;

        i = ft_strlen(path);
        while (path[i] != '/')
                i--;
        return (i);
}

char *add_slash(char *path)
{
        int	i;
        int	j;
        char *new;

        new = malloc(sizeof(char) * ft_strlen(path) + 2);
        i = -1;
        j = 0;
        while (path[++i])
                new[j++] = path[i];
        new[j] = '/';
        j++;
        new[j] = '\0';
        return (new);
}

void	change_dir(char *path, t_list *alst)
{
        char *new_path;
        char *res;
        t_list *new;
        new = alst;
        new_path = ft_substr(path, 3, ft_strlen(path));
        if (!ft_strcmp(new_path, ".."))
        {
                new_path = ft_substr(getcwd(NULL, 0), 0, search_slash(getcwd(NULL, 0)));
                chdir((const char *)new_path);
                update_env(alst, new_path);
        }
        else if (!ft_strcmp(path, "cd") || !ft_strcmp(new_path, "~"))
        {
                while (new)
                {
                        if (!ft_strcmp(new->key, "HOME"))
                                res = ft_strdup(new->content);
                        new = new->next;
                }
                chdir(res);
                update_env(alst, res);
        }
        else
        {
                res = add_slash(getcwd(NULL, 0));
                new_path = ft_strjoin(res, new_path);
                if (chdir((const char *)new_path) == -1)
                {
                        printf("cd: %s: No such file or directory\n",
                        ft_substr(path, 3, ft_strlen(path)));
                }
                else
                        update_env(alst, new_path);
        }
}