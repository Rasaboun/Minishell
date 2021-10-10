/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:45:24 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 17:03:50 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is(int c)
{
	if (c != '\'' && c != '\"' && c != ' ')
		return (1);
	return (0);
}

char	*ft_substrs(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char) * (max - min + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (min < max)
	{
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

int	whilequote_count(const char *line, t_count *ct, char c)
{
	if (line[ct->i] == c)
	{
		while (line[ct->i] == c)
		{
			ct->i++;
			while (line[ct->i] && line[ct->i] != c)
				ct->i++;
			if (line[ct->i] && line[ct->i] == c)
				ct->i++;
			else
			{
				write(2, "Not closed quote\n", 17);
				g_minishell.ret = 1;
				return (0);
			}
		}
		ct->num++;
	}
	return (1);
}

int	whilequotealpha(const char *line, t_count *ct, char c)
{
	if (line[ct->i] == c)
	{
		ct->i++;
		while (line[ct->i] && line[ct->i] != c)
			ct->i++;
		if (line[ct->i] && line[ct->i] == c)
		{
			ct->i++;
			while (line[ct->i] && ft_is(line[ct->i]))
				ct->i++;
			ct->num++;
		}
		else
		{
			write(2, "Not closed quote\n", 17);
			g_minishell.ret = 1;
			return (0);
		}
	}
	return (1);
}

int	whilealpha_count(const char *line, char *strset, t_count *ct)
{
	if (line[ct->i] && ft_is(line[ct->i]) && !ft_strchr(strset, line[ct->i]))
	{
		while (line[ct->i] && ft_is(line[ct->i])
			&& !ft_strchr(strset, line[ct->i]))
			ct->i++;
		if (line[ct->i] == '\"')
		{
			if (whilequotealpha(line, ct, '\"') == 0)
				return (0);
		}
		if (line[ct->i] == '\'')
		{
			if (whilequotealpha(line, ct, '\'') == 0)
				return (0);
		}
		else if (ct->min < ct->i)
			ct->num++;
	}
	return (1);
}
