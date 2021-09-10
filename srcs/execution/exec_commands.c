/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/09/10 17:16:08 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmds(t_cmd *ccmd, t_minishell *minishell)
{
	int	ret;
	t_cmd *cmd;

	ret = SUCCESS;
	cmd = ccmd;
	while(cmd)
	{
		ret = exec_builtins(cmd, minishell);
		cmd = cmd->next;
	}
	return (ret);
}