#include "../include/minishell.h"

int	count_redirection(char *line)
{
    int i = 0;
    int size = 0;
	
    while (line[i] == ' ' || line[i] == '|')
        i++;
    while (line[i] && line[i] != '|')
    {
        if (line[i] == '>')
            size++;
        i++;
    }
    return (size);
}

int	is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

char **select_av(char *line)
{
    char **new_av;
    new_av = ft_split(line, ' ');
	
    return (new_av);

}

int search_pipe(char *line)
{
    int i = 0;
    int res = 0;

    while (line[i])
    {
        if (line[i] == '|')
            break;
        i++;
    }
    res = i;
    return (res);
}

void	free_tab(char **tab)
{
        int	i;

        i = 0;
        while (tab[i])
        {
                free(tab[i]);
        }
}