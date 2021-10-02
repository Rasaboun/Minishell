/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:19:07 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/02 16:05:15 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *ccmd)
{
	int		new_line;
	int		i;

	new_line = 0;
	i = 1;
	if (ccmd->args[1] && ft_strcmp(ccmd->args[1], "-n") == 0)
	{
		new_line = 1;
		i++;
	}
	while (ccmd->args[i])
	{
		if ((i > 1 && new_line == 0) || (i > 2 && new_line == 1))
			write(STDOUT_FILENO, " ", 1);
		ft_putstr(ccmd->args[i]);
		i++;
	}
	if (new_line == 1)
		return (0);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}