/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:19:07 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/25 18:09:26 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *ccmd)
{
	int		i;
	int		new_line;
	char	str;

	i = 0;
	new_line = 0;
	str = ccmd->args[0];
	if (ccmd->args[2])
	{
		if (ft_strcmp(ccmd->args[1];, "-n") == 0)
			new_line = 1;	
	}
	while (str[i])
	{
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	if (new_line)
		return ;
	write(STDOUT_FILENO, "\n", 1);
}
