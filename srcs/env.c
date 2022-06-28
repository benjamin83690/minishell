#include "../include/minishell.h"

void update_env(t_list *alst, char *path)
{
    t_list *list;
    list = alst;
    char *content;
    char *new_content;

    while (list)
    {
        if (!ft_strcmp(list->key, "PWD"))
        {
            content = ft_strcpy(list->content, content);
            new_content = path;
            free(list->content);
            list->content = new_content;
        }
        if (!ft_strcmp(list->key, "OLDPWD"))
        {
            list->content = content;
        }
        list = list->next;
    }
    print_list(&alst);

}

char **putenv_in_tab(t_list *alst)
{
    t_list *list;
    char **tab;
    int i = 0;

    list = alst;
    tab = malloc(sizeof(char *) * len_list(alst) + 1);
    while (list)
    {
        tab[i] = ft_strjoin(list->key, "=");
        tab[i] = ft_strjoin(tab[i], list->content);
        i++;
        list = list->next;
    }
    tab[i] = NULL;
    return (tab);
}

void	insert_env(char **envp, t_list **alst)
{
    t_list	*new;
    char	**tab;
    int		i;

    i = -1;
    while (envp[++i])
    {
        tab = ft_split(envp[i], '=');
        new = ft_lstnew(tab[1], tab[0]);
       /* if (*alst == NULL)
                *alst = new;
        else*/
                ft_lstadd_back(alst, new);
        free(tab);
    }
}
