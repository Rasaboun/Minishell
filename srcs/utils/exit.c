/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:08:08 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/11 10:48:21 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_all(t_minishell *minishell)
{
	t_env	*env;
	t_env	*tmp;

	env = minishell->env;
	while (env)
	{
		if (env->new == 1)
			free(env->str);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	ft_freecmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
