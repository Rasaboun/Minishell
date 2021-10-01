/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:31:46 by rasaboun          #+#    #+#             */
/*   Updated: 2021/09/13 02:28:29 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <stdlib.h>

# define PIPED 1
# define BREAK 2
# define END 3

# define SUCCESS 0
# define FAILURE 1

typedef	struct	s_cmd
{
	char **args;
	int pipe[2];
	int type;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}				t_cmd;

typedef	struct	s_redir
{
	char *str;
	struct s_redir	*next;
	struct s_redir	*previous;
}				t_redir;

typedef struct	s_env {
	char			*str;
	struct s_env	*next;
}				t_env;

typedef	struct	s_tok{
	int		i;
	int		min;
	char	**str;
	int		num;
}				t_tok;


//------- Builtins -------//

int		ft_echo(t_cmd *ccmd);

//---------- Execution ----------//

int		exec_cmds(t_cmd *ccmd, t_env *envp);
int		exec_builtins(t_cmd *ccmd, t_env *env);

//---------- Utils ----------//

int		ft_strcmp(const char *s1, const char *s2);
void    print_lst(t_env *env);
void	ft_env(t_env *env);
t_env	*ft_init_env(char **envp);
t_env 	*lst_add_back(t_env *env, char *str);
void	ft_putstr(char *str);


char	**ft_strtok(const char *line, char	*strset);
void	ft_tcmdadd_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_tcmdlast(t_cmd *lst);
int		ft_tcmdsize(t_cmd *lst);
t_cmd	*ft_tcmdnew(char **args);
void	ft_cutcmd(t_cmd **cmd, char *line);


#endif
