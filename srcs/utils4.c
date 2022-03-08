#include "../include/minishell.h"

int	is_option(char *cmd)
{
    if (cmd[0] == '-')
        return (1);
    return (0);
}

int is_redir(char *cmd)
{
    if (cmd[0] == '<' || cmd[0] == '>')
        return (1);
    return (0);
}

int	is_pipe(char *cmd)
{
    if (cmd[0] == '|')
        return (1);
    return (0);
}