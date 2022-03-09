#include "../include/minishell.h"

int	is_letter(char c)
{
        if ((c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z'))
                return (1);
        return (0);
}

int	len_str(char **tab)
{
        int	i;
        int res;

        i = -1;
        res = 0;
        while (tab[++i])
                res += ft_strlen(tab[i]);
        return (res + i - 1);
}

char *concat_wspace(char **tab)
{
        int		i;
        int		j;
        int		k;
        char	*final;
        final = malloc(sizeof(char) * len_str(tab) + 1);
        i = -1;
        j = -1;
        k = 0;
        while (tab[++i])
        {
                while (tab[i][++j])
                {
                        final[k++] = tab[i][j]; 
                }
                final[k] = ' ';
                k++;
                j = -1;
        }
        final[k] = '\0';
        return (final);
}

char *ft_strcpy(char *s, char *str)
{
        int i = 0;

        str = malloc(sizeof(char) * ft_strlen(s) + 1);
        while (s[i])
        {
                str[i] = s[i];
                i++;
        }
        str[i] = '\0';
        return (str);

}

int len_list(t_list *alst)
{
        t_list *lst;
        int i;

        i = 0;
        lst = alst;
        while (lst)
        {
                i++;
                lst = lst->next;
        }
        return (i);
}