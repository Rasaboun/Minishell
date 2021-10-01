/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:31:46 by rasaboun          #+#    #+#             */
/*   Updated: 2021/09/30 17:19:26 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <stdlib.h>
# include "../Libft/libft.h"

# define PIPED 1
# define BREAK 2
# define END 3

# define SUCCESS 0
# define FAILURE 1

typedef struct	s_env {
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct	s_exp {
	int		len_var;
	int		len_value;
	int		equal;
	char	*var;
	char	*value;
}				t_exp;



typedef struct	s_minishell
{
	t_env	*env;
	int		exit;
	int		ret;
	int		stdout;
	int		stdin;
}				t_minishell;

typedef	struct	s_cmd
{
	char **args;
	int pipe[2];
	int type;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}				t_cmd;

//------- Builtins -------//

int		ft_echo(t_cmd *ccmd);
int		ft_pwd(void);
int		ft_exit(t_cmd *ccmd, t_minishell *minishell);
int		ft_cd(t_cmd *ccmd, t_env *env);
int		ft_env(t_env *env);
int		ft_export(t_cmd *cmd, t_env *env);
int		ft_unset(t_cmd *ccmd, t_env *env);

//---------- Execution ----------//

int		exec_cmds(t_cmd *ccmd, t_minishell *minishell);
int		exec_builtins(t_cmd *ccmd, t_minishell *minishell);

//---------- Utils ----------//

int		ft_strcmp(const char *s1, const char *s2);
void    print_lst(t_env *env);
t_env	*ft_init_env(char **envp);
t_env 	*lst_add_back(t_env *env, char *str);
void	ft_putstr(char *str);
void	ft_write_error(char *str);
int		ft_isnum(char *str);
int		ft_charchr(char *str, char c);

t_env	*ft_find_env(char *str, t_env *env);
char	*ft_change_env(t_env *env, char *str, char *value);
char	*ft_strjoin_env(char *s1, char *s2);
int		ft_save_pwd(t_env *env);
char	*ft_env_value(char *str, t_env *env);
int		ft_array_len(char **array);
int		ft_env_len(t_env *env);

void	ft_tcmdadd_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_tcmdlast(t_cmd *lst);
int		ft_tcmdsize(t_cmd *lst);
t_cmd	*ft_tcmdnew(char **args);
void	ft_cutcmd(t_cmd **cmd, char *line);

//---------- FREE ----------//

void	ft_free_array(char **array);

#endif
