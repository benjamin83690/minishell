#include "../include/minishell.h"

char *cut_arg(t_parse *parse, char *line, int i)
{
    int start;
    char *cmd;
    cmd = NULL;
    start = i;
    (void)parse;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '|')
        {
            i = i - 1;
            break ;
        }
        else
            i++;
    }
    cmd = ft_substr(line, start, i);
    return (cmd);
}

char *sub_arg(char *line , int i)
{
    char *new_line;

    new_line = NULL;

    while (line[i])
    {
        if (line[i] == '>' || line[i] == '|')
        {
            i = i - 1;
            break ;
        }	
        i++;
    }
    new_line = ft_substr(line, i, ft_strlen(line));
    return (new_line);
}