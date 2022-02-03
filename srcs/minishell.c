/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:09:38 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/31 16:57:12 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rl_gets(void)
{
	static char *line_read;
  if (line_read)
  {
      free (line_read);
      line_read = (char *)NULL;
  }
  line_read = readline ("minishell>> ");
  if (line_read && *line_read)
    add_history (line_read);
  return (line_read);
}

void	get_path(void)
{
	if (getcwd(NULL, 0) == NULL)
      perror("getcwd() error");
    else
      printf("%s\n", getcwd(NULL, 0));
}

int	is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') ||(c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
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

void	change_dir(char *path)
{
	char *new_path;
	char *res;
	new_path = ft_substr(path, 3, ft_strlen(path));
	if (!ft_strcmp(new_path, ".."))
	{
		new_path = ft_substr(getcwd(NULL, 0), 0, search_slash(getcwd(NULL, 0)));
		chdir((const char *)new_path);
	}
	else if (!ft_strcmp(path, "cd") || !ft_strcmp(new_path, "~"))
		chdir("/Users/bfichot");
	else
	{
		res = add_slash(getcwd(NULL, 0));
		new_path = ft_strjoin(res, new_path);
		if (chdir((const char *)new_path) == -1)
		{
			printf("cd: %s: No such file or directory\n",
				ft_substr(path, 3, ft_strlen(path)));
		}
	}

}

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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
	}
	//free(tab);
}

t_list	*insert_env(char **envp, t_list *alst)
{
	t_list	*new;
	char	**tab;
	int		i;
	
	i = -1;
	while (envp[++i])
	{
		tab = ft_split(envp[i], '=');
		new = ft_lstnew(tab[1], tab[0]);
		if (alst == NULL)
			alst = new;
		else
			ft_lstadd_back(&alst, new);
		free(tab);
	}
	return (alst);
}

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

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *line;
	t_list *alst;
	alst = NULL;
	while (1)
	{
		alst = insert_env(envp, alst);
		line = rl_gets();
		line = ft_strtrim(line, " ");
		if (!ft_strncmp(line, "pwd", 3))
			get_path();
		if (!ft_strncmp(line, "cd", 2))
			change_dir(line);
		if (!ft_strcmp(line, "env"))
			print_list(&alst);
	}
}
