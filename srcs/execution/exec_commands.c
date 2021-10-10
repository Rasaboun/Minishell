/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 15:43:03 by dkoriaki         ###   ########.fr       */
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
		if (builtin_is_exist(cmd->args[0]) == 1 && redir_ret != 2)
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

	g_minishell.in_pipe = 1;
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

int	exec_with_pipe_2(t_cmd *cmd, t_minishell *minishell)
{
	int		ret;

	g_minishell.in_pipe = 1;
	ret = FAILURE;
	if (pipe(cmd->pipe))
		return (ret);
	cmd->pid = fork();
	signal(SIGINT, stop_bin_process);
	signal(SIGQUIT, quit_bin_process);
	if (cmd->pid < 0)
		return (ret);
	else if (cmd->pid == 0)
		ft_child_pid_exec_pipe(cmd, minishell);
	else
		ft_close_for_exec_with_pipe(cmd);
	return (ret);
}

int	exec_cmds(t_cmd *ccmd, t_minishell *minishell)
{
	int			ret;
	t_cmd		*cmd;
	struct stat	sb;

	ret = -1;
	cmd = ccmd;
	while (cmd)
	{
		g_minishell.in_pipe = 0;
		if (ft_is_double_redir_left(cmd) == SUCCESS)
			ret = fd_exec_is_double_redir(&cmd, minishell);
		else
			ret = fd_exec_is_not_double_redir(&cmd, minishell);
		if (stat("./.heredoc", &sb) == 0)
			unlink("./.heredoc");
	}
	return (ret);
}
