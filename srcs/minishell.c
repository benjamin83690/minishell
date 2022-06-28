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
					len = count_letter(line, start);
					cmd = ft_substr(line, start, len);
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
			while (line[i] && line[i] != ' ')
				i++;
		}
		else
		{
			i++;
			start = i;
		}
	}
	return (parse);
}

void	my_exec(t_parse *parse, char **envp, t_list *alst)
{
	int         pid;
	int			status;
	int         pipe_fd[2];
	int         pipe_fd1[2];
	t_parse *elem;
	elem = parse;
	char *argv[] = {check_path_access(alst, parse->cmd), parse->flag ,NULL};

	
	/*
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			perror("dup2");
		//argv = { check_path_access(alst, elem->cmd), parse->flag, NULL };
		else if (execve(check_path_access(alst,parse->cmd), argv, envp) == -1)
			perror("execve");
	}
	else
	{
		char      buffer[1024];
		int       ret;
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
			//argv = {check_path_access(alst, elem->cmd), parse->flag, NULL}; 
			if (execve(check_path_access(alst,parse->cmd), argv, envp) == -1)
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
	 */
	while (parse)
	{
		if (parse->cmd && !parse->pipe)
		{
			if ((pid = fork()) == -1)
				perror("fork");
			else if (pid == 0)
			{
				if (execve(check_path_access(alst,parse->cmd ), argv, envp) == -1)
					perror("execve");
			}
			//else
			//	wait(&status);
		}
		parse = parse->next;
	}
	wait(&status);
}

int back_slash(char *str)
{
	if (str[ft_strlen(str)] == '/')
			return 1;
	return 0;
}

char *check_path_access(t_list *alst, char *cmd)
{
	char **tab_path;
	char *path;

	while (alst != NULL)
	{
		if (!strcmp(alst->key, "PATH"))
		{
			tab_path = ft_split(alst->content, ':');
			break;
		}
		alst = alst->next;
	}
	int i = -1;
	while (tab_path[++i])
	{
		if (!back_slash(tab_path[i]))
		{
			path = ft_strjoin(tab_path[i], "/");
			path = ft_strjoin(path, cmd);
		}
		else
			path = ft_strjoin(tab_path[i], cmd);
		if (!access(path, X_OK | R_OK))
				return (path);
	}
	return (NULL);
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
		my_exec(parse, envp, alst);
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
