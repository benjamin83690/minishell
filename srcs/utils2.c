#include "../include/minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
    unsigned char	*str1;
    unsigned char	*str2;
    int				i;

    str1 = (unsigned char *)s1;
    str2 = (unsigned char *)s2;
    i = -1;
    while (str1[++i] && str2[i])
    {
        if (str1[i] != str2[i])
                break ;
    }
    return (str1[i] - str2[i]);
}

int	len_envp(char **envp)
{
    int i = 0;
    while (envp[i])
            i++;
    return (i);
}

int	count_letter(char *cmd, int i)
{
    while (cmd[i] && cmd[i] != ' ')
        i++;
    if (i > 0)
        return (i);
    return (0);
}

int	check_char(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else if (c == '-')
        return (1);
    else if (c == '|')
        return (1);
    else if (c == '.')
        return (1);
    else
        return (0);
}

char *concat_wspace2(char *s1, char *s2)
{
    char *final;
    int i = -1;
    int j = -1;
    final = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
    while (s1[++i])
        final[i] = s1[i];
    final[i] = ' ';
    while (s2[++j])
        final[++i] = s2[j];
    i++;
    final[i] = '\0';
    return (final);
}