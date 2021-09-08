/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 17:38:30 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/31 00:21:06 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		exec_builtins(t_cmd *ccmd, t_env *env)
{
	int		ret;

	if (ccmd && ccmd->args[0] != NULL && ft_strcmp(ccmd->args[0], "echo") == 0)
	{
		return (ft_echo(ccmd));
	}
		
	/*if (ft_strcmp(ccmd->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(ccmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(ccmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(ccmd->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(ccmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(ccmd->args[0], "exit") == 0)
		return (1);*/
	return (FAILURE);
}