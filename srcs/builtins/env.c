/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:18:08 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/09/10 18:20:54 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_env *env)
{
	while (env)
	{
		if(ft_charchr(env->str, '=') == SUCCESS)
		{	
			//printf("%s\n", env->str);
			ft_putstr(env->str);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
	//write(1, "\n", 1);
}