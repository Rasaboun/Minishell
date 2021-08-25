/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/25 18:50:13 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmds(t_cmd *ccmd, t_env *envp)
{
	int	ret;

	ret = SUCCESS;
	while(ccmd)
	{
		//if (check_builtins(ccmd->args[0])
		ret = exec_builtins(ccmd, envp);
		ccmd = ccmd->next;
	}

	return (ret);
}