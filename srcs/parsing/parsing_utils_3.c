/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:00:42 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 19:03:54 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cm	*ft_cmlast(t_cm *lst)
{
	t_cm	*lst2;

	lst2 = lst;
	if (!lst)
		return (NULL);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void	ft_cmadd_back(t_cm **alst, t_cm *rnew)
{
	t_cm	*lst2;

	if (*alst == NULL)
		*alst = rnew;
	else
	{
		lst2 = ft_cmlast(*alst);
		lst2->next = rnew;
		rnew->next = NULL;
		rnew->previous = lst2;
	}
}

t_cm	*ft_cmnew(char **st)
{
	t_cm	*s;

	s = (t_cm *)malloc(sizeof(t_cm));
	if (!s)
		return (NULL);
	s->str = st;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}

int	ft_whil(char *s3, const char *s1, int i)
{
	int	p;
	int	y;

	p = 0;
	y = 0;
	while (p < i)
	{
		s3[p] = s1[y];
		p++;
		y++;
	}
	return (p);
}

char	*ft_strfjoin(char const *s1, char *s2)
{
	int		p;
	char	*s3;
	int		y;
	int		i;

	if (!s2)
		return (NULL);
	if (!s1)
		return (s2);
	y = 0;
	p = 0;
	i = (int)ft_strlen(s1);
	s3 = (char *)malloc(sizeof(char) * (i + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	p = ft_whil(s3, s1, i);
	y = 0;
	while (p <= (int)(i + ft_strlen(s2) - 1))
	{
		s3[p] = s2[y];
		p++;
		y++;
	}
	s3[p] = '\0';
	return (s3);
}
