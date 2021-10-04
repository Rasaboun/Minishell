/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 15:50:29 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_is_exist(char *str)
{
	int		ret;

	if (ft_strcmp(str, "echo") == 0)
		ret = 1;
	else if (ft_strcmp(str, "cd") == 0)
		ret = 1;
	else if (ft_strcmp(str, "pwd") == 0)
		ret = 1;
	else if (ft_strcmp(str, "export") == 0)
		ret = 1;
	else if (ft_strcmp(str, "unset") == 0)
		ret = 1;
	else if (ft_strcmp(str, "env") == 0)
		ret = 1;
	else if (ft_strcmp(str, "exit") == 0)
		ret = 1;
	else
		ret = 0;
	return (ret);
}

int	exec_cmds(t_cmd *ccmd, t_minishell *minishell)
{
	int		ret;
	t_cmd	*cmd;

	ret = -1;
	cmd = ccmd;
	while (cmd)
	{
		if (builtin_is_exist(cmd->args[0]) == 1)
			ret = exec_builtins(cmd, minishell);
		else
			ret = bin_fonction(cmd->args, minishell->env);
		cmd = cmd->next;
		printf("\n\necho $? = %d\n", ret);
	}
	return (ret);
}
