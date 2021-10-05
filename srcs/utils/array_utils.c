/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:56:16 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/05 19:31:37 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_free_array(char **array)
{
	int		i;

	i = 0;
	if (array)
	{	
		while (array[i])
		{
			free (array[i]);
			i++;
		}
		free(array);
	}
}

char	**ft_list_to_array(t_env *env)
{
	int		nb_lines;
	int		i;
	char	**array;

	i = 0;
	nb_lines = ft_env_len(env);
	array = (char **)malloc(sizeof(char *) * (nb_lines + 1));
	if (!array)
		return (NULL);
	while (env && i < nb_lines)
	{
		array[i] = ft_strdup(env->str);
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_list_to_array_args(t_args *args)
{
	int		nb_lines;
	int		i;
	char	**array;

	i = 0;
	nb_lines = ft_list_args_len(args);
	array = (char **)malloc(sizeof(char *) * (nb_lines + 1));
	if (!array)
		return (NULL);
	while (args && i < nb_lines)
	{
		array[i] = ft_strdup(args->str);
		args = args->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	print_env_array(char **array)
{
	int		y;
	int		x;
	int		equal;

	y = 0;
	while (array[y])
	{
		x = 0;
		equal = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (array[y][x])
		{
			write(STDOUT_FILENO, &array[y][x], 1);
			if (array[y][x] == '=')
			{
				write(STDOUT_FILENO, "\"", 1);
				equal = 1;
			}
			x++;
		}
		if (equal == 1)
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		y++;
	}
}
