/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:49:42 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 15:28:46 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rl_input_eof(char *args, int fd_out)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (i == 0)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if (ft_strcmp(line, args) == 0)
			{
				free(line);
				return ;
			}
			else
			{
				ft_putstr_eol_fd(line, fd_out);
				free(line);
			}
		}
		else
			i = ft_write_error("minishell: warning: wanted `eof'\n");
	}
}

void	ft_child_pid_exec_pipe(t_cmd *cmd, t_minishell *minishell)
{
	int	redir_ret;
	int	ret;

	ret = FAILURE;
	if (cmd->type == PIPED)
		dup2(cmd->pipe[1], STDOUT_FILENO);
	if (cmd->previous && cmd->previous->type == PIPED)
		dup2(cmd->previous->pipe[0], STDIN_FILENO);
	redir_ret = ft_check_redir(cmd->args, minishell);
	if (redir_ret == SUCCESS)
		cmd->args = delete_redir_in_args(cmd->args);
	if (cmd->args[0])
	{
		if (builtin_is_exist(cmd->args[0]) == 1 && redir_ret != 2)
			ret = exec_builtins(cmd, minishell);
		else if (redir_ret != 2)
			ret = bin_fonction(cmd->args, minishell->env);
	}
	exit(ret);
}
