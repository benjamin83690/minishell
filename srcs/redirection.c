#include "../include/minishell.h"

char	*get_path_redirection(char *cmd, int i)
{
    char	*path;
    int		start;
	
    while (cmd[i])
    {
        if (cmd[i] == ' ')
            i++;
        else
        {
            start = i;
            break;
        }
    }
    while (cmd[i] && cmd[i] != ' ')
        i++;
    path = ft_substr(cmd, start, i);
    return (path);
}

char *sub_path_direction(char *cmd, int i)
{
    char *path;

    while (cmd[i])
    {
        if (cmd[i] == ' ')
            i++;
        else
            break;
    }
    while (cmd[i] && cmd[i] != ' ')
        i++;
    path = ft_substr(cmd, i, ft_strlen(cmd));
    //printf("path ===> [%s] \n", path);
    return (path);

}

t_parse *add_redirection(t_parse *parse, char *cmd, int nbr_redi)
{
    t_parse *elem;
    int i = -1;
    if (parse == NULL)
    {
        parse = malloc(sizeof(t_parse));
        init_parse(parse);
    }
    elem = last_elem(parse);
    if (elem->dir == NULL)
    {
        elem->dir = malloc(sizeof(char *) * nbr_redi + 1);
        while (++i < nbr_redi)
            elem->dir[i] = NULL;
    }
    i = -1;
    while (++i < nbr_redi)
    {
        if (elem->dir[i] == NULL)
        {
            elem->dir[i] = ft_strcpy(cmd, elem->dir[i]);
            break;
        }
    }
    i++;
    elem->dir[i] = NULL;
    elem->nbr_arg += 2;
    return (parse);
}