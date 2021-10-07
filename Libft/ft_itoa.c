/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:59:36 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/06 23:15:10 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc(int i)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	return (s);
}

static	int	ft_numlen(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static char	*make(int i, unsigned int nb, char *s)
{
	while (nb > 0)
	{
		s[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				i;
	char			*s;

	i = ft_numlen((long)n);
	s = ft_malloc(i);
	if (!s)
		return (0);
	s[i--] = '\0';
	if (n == 0)
	{
		s[0] = '0';
		return (s);
	}
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	nb = (unsigned int)n;
	s = make(i, nb, s);
	return (s);
}
