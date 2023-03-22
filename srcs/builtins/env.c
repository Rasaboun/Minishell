/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:18:08 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/11 10:30:17 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_charchr(env->str, '=') == SUCCESS)
		{	
			ft_putstr(env->str);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
