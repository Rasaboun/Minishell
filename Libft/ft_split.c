/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:51:59 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/07 13:52:33 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substrr(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char *) * (max - min + 1));
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

static int	ft_count(const char *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (s[i] == '\0')
		return (n);
	if (s[0] != c)
		n++;
	while (s[i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	return (n);
}

static void	ft_free(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

char	**while_for_norm(int i, const char *s, char c, char **s2)
{
	int		min;
	int		n;

	n = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		min = i;
		while (s[i] && s[i] != c)
			i++;
		if (n < ft_count(s, c))
		{
			s2[n] = ft_substrr(s, min, i);
			if (!s2[n])
				ft_free(n, s2);
		}
		n++;
	}
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**s2;
	int		n;

	if (!s)
		return (NULL);
	n = 0;
	s2 = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!s2)
		return (0);
	s2[ft_count(s, c)] = 0;
	i = 0;
	s2 = while_for_norm(i, s, c, s2);
	return (s2);
}
