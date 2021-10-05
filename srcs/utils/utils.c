/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:56:24 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/05 19:29:42 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_write_error(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
	return (FAILURE);
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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	ft_reset_fds(t_minishell *minishell)
{
	if (minishell->stdout != STDOUT_FILENO)
		dup2(minishell->stdout, STDOUT_FILENO);
	if (minishell->stdin != STDIN_FILENO)
		dup2(minishell->stdin, STDIN_FILENO);
}
