/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:38:30 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/25 17:51:39 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int		check_builtins(char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int		exec_builtins(t_cmd *ccmd, t_env *env)
{
	int		ret;

	if (strcmp(ccmd->args[0], "echo") == 0)
		return (1);
	/*if (strcmp(ccmd->args[0], "cd") == 0)
		return (1);
	if (strcmp(ccmd->args[0], "pwd") == 0)
		return (1);
	if (strcmp(ccmd->args[0], "export") == 0)
		return (1);
	if (strcmp(ccmd->args[0], "unset") == 0)
		return (1);
	if (strcmp(ccmd->args[0], "env") == 0)
		return (1);
	if (strcmp(ccmd->args[0], "exit") == 0)
		return (1);*/
	return (ret);
}
