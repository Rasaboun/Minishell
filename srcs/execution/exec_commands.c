/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/06 15:02:19 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_without_pipe(t_cmd *cmd, t_minishell *minishell)
{
	int		ret;
	int		redir_ret;

	ret = FAILURE;
	redir_ret = ft_check_redir(cmd->args);
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

int	exec_with_pipe(t_cmd *cmd, t_minishell *minishell)
{
	int		ret;

	ret = FAILURE;
	//if (cmd->type == PIPED || (cmd->previous && cmd->previous->type == PIPED))
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
		if (cmd->type == PIPED || (cmd->previous
				&& cmd->previous->type == PIPED))
			ret = exec_with_pipe(cmd, minishell);
		else
			ret = exec_without_pipe(cmd, minishell);
		cmd = cmd->next;
		if (stat("./.heredoc", &sb) == 0)
			unlink("./.heredoc");
		printf("\n\necho $? = %d\n", ret);
	}
	return (ret);
}
