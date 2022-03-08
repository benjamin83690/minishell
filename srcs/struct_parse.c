#include "../include/minishell.h"

t_parse	*insert_arg(t_parse *parse, char *cmd)
{
    t_parse *new;
	
    if (parse == NULL)
    {
        new = create_new(cmd);
        parse = new;
    }
    else
    {
        new = parse;
        while (new)
        {
            if (last_elem(parse)->pipe == 0)
            {
                new = last_elem(parse);
                new = update_new(new, cmd);
            }
            else
            {
                new = create_new(cmd);
                add_back(&parse, new);
            }
            new = new->next;
        }		
    }
    return (parse);
}

t_parse	*create_new(char *cmd)
{
    t_parse *new;
    
    new = malloc(sizeof(t_parse));
    init_parse(new);
    if (is_option(cmd))
            new->flag = ft_strcpy(cmd, new->cmd);
    else if (is_pipe(cmd))
        new->pipe = 1;
    else
    {
        
        if (new->cmd == NULL)
            new->cmd = ft_strcpy(cmd, new->cmd);
        else
        {
            if (new-> arg == NULL)
                new->arg = ft_strcpy(cmd, new->arg);
        }
    }
    new->nbr_arg++;
    return (new);
}

t_parse *update_new(t_parse *new, char *cmd)
{
    if (is_option(cmd))
            new->flag = ft_strcpy(cmd, new->cmd);
    else if (is_pipe(cmd))
            new->pipe = 1;
    else
    {
        
        if (new->cmd == NULL)
            new->cmd = ft_strcpy(cmd, new->cmd);
        else
        {
            if (new-> arg == NULL)
                new->arg = ft_strcpy(cmd, new->arg);
            else
                new->arg = concat_wspace2(new->arg, cmd);
        }
    }
    new->nbr_arg++;
    return (new);
}

t_parse	*last_elem(t_parse *parse)
{
    t_parse *elem;
    elem = parse;
    while (elem->next)
        elem = elem->next;
    return (elem);
}

void	add_back(t_parse **parse, t_parse *new)
{
    t_parse *tmp;

    if (!*parse)
        *parse = new;
    else
    {
        tmp = last_elem(*parse);
        tmp->next = new;
    }
}