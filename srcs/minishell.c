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

char *PATH = NULL;

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

void	change_dir(char *path, t_list *alst)
{
		char *new_path;
		char *res;
		t_list *new;
		new = alst;
		new_path = ft_substr(path, 3, ft_strlen(path));
		if (!ft_strcmp(new_path, ".."))
		{
				new_path = ft_substr(getcwd(NULL, 0), 0, search_slash(getcwd(NULL, 0)));
				chdir((const char *)new_path);
				update_env(alst, new_path);
		}
		else if (!ft_strcmp(path, "cd") || !ft_strcmp(new_path, "~"))
		{
				while (new)
				{
						if (!ft_strcmp(new->key, "HOME"))
								res = ft_strdup(new->content);
						new = new->next;
				}
				chdir(res);
				update_env(alst, res);
		}
		else
		{
				res = add_slash(getcwd(NULL, 0));
				new_path = ft_strjoin(res, new_path);
				if (chdir((const char *)new_path) == -1)
				{
						printf("cd: %s: No such file or directory\n",
										ft_substr(path, 3, ft_strlen(path)));
				}
				else
						update_env(alst, new_path);
		}

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
				if (alst == NULL)
						*alst = new;
				else
						ft_lstadd_back(alst, new);
				free(tab);
		}
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

int	count_letter(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (i > 0)
		return (i);
	return (0);
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

t_parse	*parser_arg(t_parse *parse, char *line)
{
		int i = 0;
		int start = 0;
		int len = 0;
		char *cmd;
		int nbr_redi = count_redirection(line);
		while (line[i])
		{
			if (line[i] != ' ')
			{
				if (line[i] == '>')
				{
					cmd = get_path_redirection(line, start + 1);
					parse = add_redirection(parse, cmd, nbr_redi);
					line = sub_path_direction(line, start + 1);
					free(cmd);	
					cmd = NULL;
					i = 0;
					start = 0;
					//printf("line =====> [%s]\n", line);
				}
				else if (line[i] == '-')
				{
					len = count_letter(line, start);
					cmd = ft_substr(line, start, len);
					parse = insert_arg(parse, cmd);
				}
				else if (line[i] == '|')
				{
					nbr_redi = count_redirection(line);
					last_elem(parse)->pipe = 1;
				}
				else if (is_alpha(line[i]))
				{
					if (last_elem(parse)->pipe == 1 || last_elem(parse)-> cmd == NULL)
					{
						//printf("line =====> [%s]\n", line);
						len = count_letter(line, start);
						cmd = ft_substr(line, start, len);
						//printf("cmd =====> [%s]\n", cmd);
					}
					else
					{
						cmd = cut_arg(last_elem(parse), line, start);
						line = sub_arg(line, start);
						i = 0;
						start = 0;
					}
					parse = insert_arg(parse, cmd);
				}
				//printf("cmd ====> [%s]\n", cmd);
				while (line[i] && line[i] != ' ')
					i++;
			}
			else
			{
				i++;
				start = i;
			}
		}
		//print_arg(parse);
		return (parse);
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

void	my_exec(t_parse *parse, char **av, char **envp, char *line)
{
		int         pid;
		int status;
  		int           pipe_fd[2];
  		int           pipe_fd1[2];
		t_parse *elem;
		elem = parse;
		
		//while (elem)
		//{
				if (pipe(pipe_fd) == -1)
      				perror("pipe");
  				if ((pid = fork()) == -1)
      				perror("fork");
  				else if (pid == 0)
    			{
					char *this_av;
					this_av = ft_substr(line, 0, search_pipe(line));
					av = select_av(this_av);
      				close(pipe_fd[0]);
      				if (dup2(pipe_fd[1], 1) == -1)
      					perror("dup2");
      				else if (execve(ft_strjoin("/bin/", elem->cmd), av, envp) == -1)
      					perror("execve");
    			}
  				else
    			{
      				char      buffer[1024];
      				int       ret;
					line = ft_substr(line, search_pipe(line) + 1, ft_strlen(line));
					av = select_av(line);
					close(pipe_fd[1]);
					pipe(pipe_fd1);
					pid = fork();

					if (pid == 0)
					{
						elem = elem->next;
						close(pipe_fd1[0]);
						dup2(pipe_fd[0], 0);
						close(pipe_fd[0]);

						dup2(pipe_fd1[1], 1);
						close(pipe_fd1[1]);
						if (execve(ft_strjoin("/usr/bin/", elem->cmd), av, envp) == -1)
							perror("execve:");
					}
					else
					{
						close(pipe_fd1[1]);
      					while ((ret = read(pipe_fd1[0], buffer, 1023)) != 0)
      					{
        					buffer[ret] = 0;
        					printf("buff = %s\n", buffer);
      					}
						
					}
    			}
				close(pipe_fd1[0]);
				wait(&status);

		//}
				

}

int main(int ac, char **av, char **envp)
{
		// checker lordre pour excuter variable
		(void)ac;
		(void)av;
		char *line;
		//int pid = getpid();
		t_list *alst;
		alst = NULL;
		insert_env(envp, &alst);
		t_parse *parse;
		while (1)
		{
				line = rl_gets();
				line = ft_strtrim(line, " ");
				av = ft_split(line, ' ');
				parse = malloc(sizeof(t_parse));
				init_parse(parse);
				parse = parser_arg(parse, line);
				my_exec(parse, av, envp, line);
				print_arg(parse);
				free(parse);
				/*if (execve(ft_strjoin("/bin/", av[0]), av, envp) == -1)
				{
				  perror("ne peux pas executer execve\n");
				}
				if (!ft_strncmp(line, "pwd", 3))
						get_path();
				if (!ft_strncmp(line, "cd", 2))
						change_dir(line, alst);
				if (!ft_strcmp(line, "env"))
						print_list(&alst);
				putenv_in_tab(alst);
				if (!ft_strcmp(line, "exit"))
					kill(pid, SIGINT);*/
		}
}
