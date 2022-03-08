#include "../include/minishell.h"

void print_list(t_list **alst)
{
    t_list *new;
    new = *alst;
    while (new)
    {
        printf("%s = %s \n", new->key, new->content);
        new = new->next;
    }
}

void	print_arg(t_parse *parse)
{
    t_parse *elem;
    elem = parse;
    int i = 0;
    int j = -1;

    while (elem)
    {
        printf("cmd%d ===>%s\n", i, elem->cmd);
        if (elem->flag != NULL)
            printf("option%d ===>%s\n", i, elem->flag);
        if (elem->arg != NULL)
            printf("arg%d ===>[%s]\n", i, elem->arg);
        if (elem->dir != NULL)
        {
            while (elem->dir[++j])
                printf("command%d-> redirection:[%d] ===>%s\n", i, j, elem->dir[j]);
            j = -1;
        }
        printf("nbr_arg = %d\n", elem->nbr_arg);
        if (elem->pipe)
            printf("pipe[%d] existant = [%d]\n",i, elem->pipe );
        i++;
        elem = elem->next;
    }
}

void init_parse(t_parse *parse)
{
    parse->cmd = NULL;
    parse->arg = NULL;
    parse->dir = NULL;
    parse->flag = NULL;
    parse->pipe = 0;
    parse->next = NULL;
    parse->nbr_arg = 0;
}