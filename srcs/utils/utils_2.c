/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:55:13 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/09 13:41:22 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_charchr(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	**split_path(t_env *env)
{
	char	**array;
	char	*path;

	path = ft_env_value("PATH", env);
	array = ft_split(path, ':');
	free(path);
	return (array);
}

void	ft_werror(char *s1, char *s2, char *s3)
{
	ft_write_error(s1);
	ft_write_error(s2);
	ft_write_error(s3);
	ft_write_error("\n");
}

int	ft_ret_fork_status(int status)
{
	int	ret;

	ret = FAILURE;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status);
		if (ret != 131 && ret != 130)
			ret += 128;
	}
	return (ret);
}
