/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:44:58 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/01 14:06:30 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_init_env(char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		env = lst_add_back(env, envp[i], 0);
		i++;
	}
	return (env);
}