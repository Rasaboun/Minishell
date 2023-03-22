/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:57:21 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 18:59:49 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (0);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

t_lchar	*ft_lcharlast(t_lchar *lst)
{
	t_lchar	*lst2;

	lst2 = lst;
	if (!lst)
		return (NULL);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

int	ft_lcharlen(t_lchar *lst)
{
	t_lchar	*lst2;
	int		i;

	i = 0;
	lst2 = lst;
	if (!lst)
		return (0);
	while (lst2->next)
	{
		lst2 = lst2->next;
		i++;
	}
	return (i);
}

void	ft_lcharadd_back(t_lchar **alst, t_lchar *rnew)
{
	t_lchar	*lst2;

	if (*alst == NULL)
		*alst = rnew;
	else
	{
		lst2 = ft_lcharlast(*alst);
		lst2->next = rnew;
		rnew->next = NULL;
		rnew->previous = lst2;
	}
}

t_lchar	*ft_lcharnew(char st)
{
	t_lchar	*s;

	s = (t_lchar *)malloc(sizeof(t_lchar));
	if (!s)
		return (NULL);
	s->c = st;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}
