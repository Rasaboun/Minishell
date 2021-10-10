/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:35:49 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 11:42:40 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_double_redir_left(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (strcmp(cmd->args[i], "'<<'") == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	find_equal_in_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	space_in_env_name(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = find_equal_in_env(str);
	if (equal != -1)
	{
		while (str[i] && i <= equal)
		{
			if (str[i] == ' ')
				return(SUCCESS);
			i++;
		}
	}
	return (FAILURE);
}
