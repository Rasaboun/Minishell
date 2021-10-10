/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:07:52 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 15:40:26 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_exec_is_double_redir(t_cmd **cmd, t_minishell *minishell)
{
	int			ret;

	if ((*cmd)->type == PIPED || ((*cmd)->previous
			&& (*cmd)->previous->type == PIPED))
	{
		if (g_minishell.ret != 130 && g_minishell.ret != 131)
			ret = exec_with_pipe((*cmd), minishell);
	}
	else
		ret = exec_without_pipe((*cmd), minishell);
	(*cmd) = (*cmd)->next;
	return (ret);
}

int	ft_waitpid_pipe_for_exec(t_cmd *cmd_2)
{
	int	status;
	int	ret;

	while (cmd_2 && (cmd_2->type == PIPED || (cmd_2->previous
				&& cmd_2->previous->type == PIPED)))
	{
		waitpid(cmd_2->pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		cmd_2 = cmd_2->next;
	}
	return (ret);
}

int	fd_exec_is_not_double_redir(t_cmd **cmd, t_minishell *minishell)
{
	int		ret;
	t_cmd	*cmd_2;

	if ((*cmd)->type == PIPED || ((*cmd)->previous
			&& (*cmd)->previous->type == PIPED))
	{
		cmd_2 = (*cmd);
		while ((*cmd) && ((*cmd)->type == PIPED || ((*cmd)->previous
					&& (*cmd)->previous->type == PIPED)))
		{
			if (g_minishell.ret != 130 && g_minishell.ret != 131)
				ret = exec_with_pipe_2((*cmd), minishell);
			(*cmd) = (*cmd)->next;
		}
		ret = ft_waitpid_pipe_for_exec(cmd_2);
	}
	else
	{
		ret = exec_without_pipe((*cmd), minishell);
		(*cmd) = (*cmd)->next;
	}
	return (ret);
}
