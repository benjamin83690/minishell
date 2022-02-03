#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_parse
{
	char	*cmd;
	char	*arg;
	char	*flag;
	char	*dir;

} t_parse;

typedef struct s_env
{
	char *key;
	char *value;

} t_env;

char	*rl_gets(void);
void	get_path(void);
int		ft_strcmp(const char *s1, const char *s2);
int		len_envp(char **envp);
char	*add_slash(char *path);
char	*clean_str(char *path);
int		is_letter(char c);
void	free_tab(char **tab);
t_list	*insert_env(char **envp, t_list *alst);
void	print_list(t_list **alst);

#endif
