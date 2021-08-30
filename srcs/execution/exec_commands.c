/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/31 00:49:15 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmds(t_cmd *ccmd, t_env *envp)
{
	int	ret;

	t_cmd *cmd;

	cmd = ccmd;
	ret = SUCCESS;
	while(cmd)
	{
		//if (check_builtins(ccmd->args[0])
		ret = exec_builtins(cmd, envp);
		cmd = cmd->next;
	}

	return (ret);
}