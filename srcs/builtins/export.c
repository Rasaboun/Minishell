/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:38:59 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/09/08 15:40:28 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char *str, char *value, t_env *env)
{
	char	**tab;
	t_env	*cur;
	char	*tmp;
	//If 0 arguments, 
	if(!str && !value)
	{
		tab = ft_list_to_array(env);
		tab = ft_sort_env(tab);
		print_env_array(tab);
		return ;
	}
	//IF str existe deja =
	cur = ft_find_env(str, env);
	if (cur != NULL)
	{
		if (!value)
			return ;
		cur->str = ft_change_env(str, value);
		return ;
	}
	//cas : export -> "str=value" && "str="
	if (value)
	{
		tmp = ft_strjoin_env(str, value);
		env = lst_add_back(env, tmp);
	}
	else // cas : "export str"
		env = lst_add_back(env, str);
}