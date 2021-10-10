/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:31:46 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/10 14:58:45 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
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

# define CANNOT_EXECUTE 126
# define UNKNOWN_COMMAND 127

typedef struct s_env {
	char			*str;
	int				new;
	struct s_env	*next;
}				t_env;

typedef struct s_exp {
	int		len_var;
	int		len_value;
	int		equal;
	char	*var;
	char	*value;
}				t_exp;

typedef struct s_minishell
{
	t_env	*env;
	int		exit;
	int		ret;
	int		in_pipe;
	int		stdout;
	int		stdin;
}				t_minishell;

typedef struct s_count
{
	int		i;
	int		num;
	int		min;
	int		n;
	char	m;
	char	mm;
}				t_count;

typedef struct s_cmd
{
	char			**args;
	int				pipe[2];
	int				type;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}				t_cmd;

typedef struct s_tok{
	int		i;
	int		min;
	char	**str;
	int		num;
}				t_tok;

typedef struct s_cm
{
	char		**str;
	struct s_cm	*next;
	struct s_cm	*previous;
}				t_cm;

typedef struct s_lchar
{
	char			c;
	struct s_lchar	*next;
	struct s_lchar	*previous;
}				t_lchar;

typedef struct s_redir
{
	char			*str;
	struct s_redir	*next;
	struct s_redir	*previous;
}				t_redir;

typedef struct s_args
{
	char			*str;
	struct s_args	*next;
	struct s_args	*previous;
}				t_args;

t_minishell		g_minishell;

//------- binary functions -------//

int		bin_fonction(char **argv, t_env *env);
int		bin_is_exist(char *path, char **cmd, char **env_cpy);
int		exec_bin(char *path, char **cmd, char **env_cpy);
int		ft_check_bin_error(char *path);
void	ft_write_error_bin(int ret);

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
void	print_lst(t_env *env);
t_env	*ft_init_env(char **envp);
t_env	*lst_add_back(t_env *env, char *str, int new);
void	ft_putstr(char *str);

int		ft_istrchr(const char *s, int c);
int		ft_delquotes(char **line, t_env *env);
t_redir	*ft_redirlast(t_redir *lst);
void	ft_rediradd_back(t_redir **alst, t_redir *rnew);
t_redir	*ft_redirnew(char *st);
char	**rediredit(char **tabs);
char	**ft_strtok(char *line, char	*strset);
int		ft_write_error(char *str);
int		ft_isnum(char *str);
int		ft_charchr(char *str, char c);

char	**split_path(t_env *env);
char	**ft_list_to_array(t_env *env);
void	print_env_array(char **array);
void	stop_bin_process(int signum);
void	quit_bin_process(int signum);

t_exp	ft_export_split(char *str);
void	ft_set_variable_and_value(char *str, t_exp *exp);
void	ft_len_variable_and_value(char *str, t_exp *exp);
int		parse_export(char *str);
void	ft_rl_input_eof(char *args, int fd_out);
void	ft_child_pid_exec_pipe(t_cmd *cmd, t_minishell *minishell);
int		ft_ret_fork_status(int status);
int		fd_exec_is_double_redir(t_cmd **cmd, t_minishell *minishell);
int		fd_exec_is_not_double_redir(t_cmd **cmd, t_minishell *minishell);
int		exec_with_pipe_2(t_cmd *cmd, t_minishell *minishell);
int		exec_with_pipe(t_cmd *cmd, t_minishell *minishell);
void	ft_close_for_exec_with_pipe(t_cmd *cmd);
int		exec_without_pipe(t_cmd *cmd, t_minishell *minishell);
void	set_signals(void);

void	ft_werror(char *s1, char *s2, char *s3);
int		builtin_is_exist(char *str);
int		ft_check_redir(char **args, t_minishell *minishell);
void	ft_close(int fd);
void	ft_reset_fds(t_minishell *minishell);
char	**delete_redir_in_args(char **args);
int		ft_list_args_len(t_args *args);
char	**ft_list_to_array_args(t_args *args);
void	ft_free_cell_args_next(t_args *cur);
t_args	*ft_delete_cell_args(t_args *args);
void	ft_delete_cell_args_next(t_args *args, t_args *cur, t_args *prev);
t_args	*ft_init_args(char **args);
int		ft_is_redir(char *str);
void	prompt_signal(int signal);
int		ft_is_double_redir_left(t_cmd *cmd);
int		space_in_env_name(char *str);

void	ft_init_minishell(t_minishell *minishell, char **envp);
int		is_empty_list(t_env *env);
t_env	*ft_find_env(char *str, t_env *env);
char	*ft_change_env(t_env *env, char *str, char *value);
char	*ft_strjoin_env(char *s1, char *s2);
int		ft_save_pwd(t_env *env);
char	*ft_env_value(char *str, t_env *env);
int		ft_array_len(char **array);
int		ft_env_len(t_env *env);
char	**ft_list_to_array(t_env *env);
char	**ft_sort_env(char **envp);
void	print_env_array(char **array);
void	free_env_cell(t_env *env, int how);

int		ft_is(int c);
char	*ft_substrs(const char *s, int min, int max);
t_cm	*ft_cmlast(t_cm *lst);
void	ft_cmadd_back(t_cm **alst, t_cm *rnew);
t_cm	*ft_cmnew(char **st);
void	ft_tcmdadd_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_tcmdlast(t_cmd *lst);
int		ft_tcmdsize(t_cmd *lst);
t_cmd	*ft_tcmdnew(char **args);
void	ft_cutcmd(t_cmd **cmd, char *line, t_env *env);

//---------- FREE ----------//

void	ft_free_array(char **array);
void	ft_clean_all(t_minishell *minishell);
void	ft_freecmd(t_cmd *cmd);

#endif
