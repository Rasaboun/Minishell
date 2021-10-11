/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:19:07 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/11 12:40:22 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_is_n(char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		if (str[0] != '-')
			return (FAILURE);
		if (str[0] == '-')
		{
			i = 1;
			while (str[i])
			{
				if (str[i] != 'n')
					return (FAILURE);
				i++;
			}
		}
	}
	return (SUCCESS);
}

int	ft_check_option_n(char **str, int i)
{
	int	ret;

	i = 0;
	ret = SUCCESS;
	while (str[i] && ret == SUCCESS)
	{
		i++;
		ret = ft_check_is_n(str[i]);
	}
	return (i);
}

void	ft_print_echo(char **str, int new_line, int multiple_n, int i)
{
	while (str[i])
	{
		if (((i > 1 && new_line == 0) || (i > 2 && new_line == 1))
			&& multiple_n != i && multiple_n != 1)
			write(STDOUT_FILENO, " ", 1);
		ft_putstr(str[i]);
		i++;
	}
}

int	ft_check_args1_echo(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (FAILURE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_echo(t_cmd *ccmd)
{
	int		new_line;
	int		i;
	int		multiple_n;

	new_line = 0;
	i = 1;
	multiple_n = 0;
	if (ccmd->args[1] && ft_check_args1_echo(ccmd->args[1]) == SUCCESS)
	{
		new_line = 1;
		i++;
		i = ft_check_option_n(ccmd->args, i);
		multiple_n = i;
	}
	ft_print_echo(ccmd->args, new_line, multiple_n, i);
	if (new_line == 1)
		return (0);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
