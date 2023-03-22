/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:04:15 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 19:07:31 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redirlast(t_redir *lst)
{
	t_redir	*lst2;

	lst2 = lst;
	if (!lst)
		return (NULL);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}

void	ft_rediradd_back(t_redir **alst, t_redir *rnew)
{
	t_redir	*lst2;

	if (*alst == NULL)
		*alst = rnew;
	else
	{
		lst2 = ft_redirlast(*alst);
		lst2->next = rnew;
		rnew->next = NULL;
		rnew->previous = lst2;
	}
}

t_redir	*ft_redirnew(char *st)
{
	t_redir	*s;

	s = (t_redir *)malloc(sizeof(t_redir));
	if (!s)
		return (NULL);
	s->str = st;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}

t_lchar	*lcharaddutil(t_lchar *alst, t_lchar *rnew)
{
	t_lchar	*tmp;

	if (!rnew)
	{
		tmp = alst;
		if (!alst->previous)
		{
			alst = alst->next;
			if (alst)
				alst->previous = NULL;
		}
		else
		{
			if (alst->c != '\"')
				alst = alst->next;
			if (alst)
			{
				alst->previous = tmp->previous;
				tmp->next = alst;
			}
		}
		return (alst);
	}
	return (alst);
}

t_lchar	*ft_lcharadd(t_lchar *alst, t_lchar *rnew)
{
	t_lchar	*tmp;
	t_lchar	*lst;

	lst = alst;
	if (!rnew)
		return (lcharaddutil(alst, rnew));
	if (lst->previous == NULL)
	{
		tmp = ft_lcharlast(rnew);
		lst->previous = tmp;
		tmp->next = lst;
	}
	else
	{
		rnew->previous = lst->previous;
		lst->previous->next = rnew;
		tmp = ft_lcharlast(rnew);
		lst->previous = tmp;
		tmp->next = lst;
	}
	return (lst);
}
