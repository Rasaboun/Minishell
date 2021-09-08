/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:56:24 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/09/01 11:33:40 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_error(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
}