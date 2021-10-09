/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/09 14:08:46 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_without_pipe(t_cmd *cmd, t_minishell *minishell)
{
	int		ret;
	int		redir_ret;

	ret = FAILURE;
	redir_ret = ft_check_redir(cmd->args, minishell);
	if (redir_ret == SUCCESS)
		cmd->args = delete_redir_in_args(cmd->args);
	if (cmd->args[0])
	{
		if (builtin_is_exist(cmd->args[0]) == 1)
			ret = exec_builtins(cmd, minishell);
		else if (redir_ret != 2)
			ret = bin_fonction(cmd->args, minishell->env);
	}
	ft_reset_fds(minishell);
	return (ret);
}

void	ft_close_for_exec_with_pipe(t_cmd *cmd)
{
	close(cmd->pipe[1]);
	if (!cmd->next)
		close(cmd->pipe[0]);
	if (cmd->previous && cmd->previous->type == PIPED)
		close(cmd->previous->pipe[0]);
}

int	exec_with_pipe(t_cmd *cmd, t_minishell *minishell)
{
	int		ret;
	pid_t	pid;
	int		status;
	int		redir_ret;

	ret = FAILURE;
	if (pipe(cmd->pipe))
		return (ret);
	pid = fork();
	signal(SIGINT, stop_bin_process);
	signal(SIGQUIT, quit_bin_process);
	if (pid < 0)
		return (ret);
	else if (pid == 0)
		ft_child_pid_exec_pipe(cmd, minishell);
	else
	{
		waitpid(pid, &status, 0);
		ft_close_for_exec_with_pipe(cmd);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

int	exec_cmds(t_cmd *ccmd, t_minishell *minishell)
{
	int			ret;
	t_cmd		*cmd;
	t_cmd		*cmd_copy;
	int			status;
	struct stat	sb;

	ret = -1;
	cmd = ccmd;
	while (cmd)
	{
		if (cmd->type == PIPED || (cmd->previous
				&& cmd->previous->type == PIPED))
		{
			if (g_minishell.ret != 130 && g_minishell.ret != 131)
				ret = exec_with_pipe(cmd, minishell);
		}
		else
			ret = exec_without_pipe(cmd, minishell);
		cmd = cmd->next;
		if (stat("./.heredoc", &sb) == 0)
			unlink("./.heredoc");
	}
	return (ret);
}
