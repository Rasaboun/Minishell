/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:35:20 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/05 18:12:56 by rasaboun         ###   ########.fr       */
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
		ret = exec_builtins(cmd, minishell);
		cmd = cmd->next;
		printf("\n\necho $? = %d\n", ret);
	}
	return (ret);
}
