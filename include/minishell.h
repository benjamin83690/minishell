#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <signal.h>

typedef struct s_parse
{
	char	*cmd;
	char	*arg;
	char	*flag;
	char	**dir;
	int	pipe;
	int	nbr_arg;
	struct s_parse	*next;

} t_parse;

typedef struct s_env
{
	char *key;
	char *value;

} t_env;

int	is_alpha(char c);
int	ft_strcmp(const char *s1, const char *s2);
int	len_envp(char **envp);
int	is_letter(char c);
int	len_list(t_list *alst);
int	is_redir(char *cmd);
int	is_pipe(char *cmd);
int	is_option(char *cmd);
int	count_letter(char *cmd, int i);
int	check_char(char c);
int	count_redirection(char *line);
char	*concat_wspace2(char *s1, char *s2);
char	**putenv_in_tab(t_list *alst);
char	*add_slash(char *path);
char	*rl_gets(void);
char	*clean_str(char *path);
char	*get_path_redirection(char *cmd, int i);
char	*cut_arg(t_parse *parse, char *line, int i);
void	free_tab(char **tab);
void	insert_env(char **envp, t_list **alst);
void	print_list(t_list **alst);
void	int_parse(t_parse *parse);
void	add_back(t_parse **parse, t_parse *new);
void	get_path(void);
void	print_arg(t_parse *parse);
void	update_env(t_list *alst, char *path);
t_parse	*parser_arg(t_parse *parse, char *line);
t_parse	*insert_arg(t_parse *parse, char *cmd);
t_parse *last_elem(t_parse *parse);
t_parse	*create_new(char *cmd);
t_parse *update_new(t_parse *new, char *cmd);
t_parse	*add_redirection(t_parse *parse, char *cmdi, int nbr_redi);

#endif
