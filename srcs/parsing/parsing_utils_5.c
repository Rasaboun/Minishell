/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:08:46 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 19:10:15 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_dollars_utils(t_lchar **lst, t_dollars *d)
{
	while (d->lchar->next && ft_isalnum(d->lchar->c))
	{
		d->i++;
		d->lchar = d->lchar->next;
	}
	d->line = (char *)malloc(sizeof(char) * (d->i + 1));
	d->lchar = *lst;
	d->i = 0;
	while (d->lchar->next && ft_isalnum(d->lchar->c))
	{
		d->tmp = d->lchar->next;
		d->line[d->i] = d->lchar->c;
		free(d->lchar);
		d->lchar = d->tmp;
		d->i++;
	}
	d->line[d->i] = '\0';
}

char	*get_dollar(t_lchar **lst)
{
	t_dollars	d;

	d.line = NULL;
	d.i = 0;
	d.lchar = *lst;
	d.tmp = *lst;
	d.tmptwo = d.tmp->previous;
	get_dollars_utils(lst, &d);
	if (d.i > 0)
	{
		if (!d.tmptwo)
			d.lchar->previous = NULL;
		else
		{
			d.lchar->previous = d.tmptwo;
			d.tmptwo->next = d.lchar;
		}
	}
	*lst = d.lchar;
	return (d.line);
}

t_lchar	*ft_tabtolchar(char *line)
{
	int		i;
	t_lchar	*tmp;
	t_lchar	*c;

	c = NULL;
	tmp = NULL;
	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		tmp = ft_lcharnew(line[i]);
		ft_lcharadd_back(&c, tmp);
		i++;
	}
	return (c);
}

void	quotesdl(t_lchar **q, char c)
{
	t_lchar	*cq;
	t_lchar	*tmp;

	tmp = NULL;
	cq = *q;
	if (cq && cq->c == c)
	{
		if (!cq->previous)
		{
			tmp = cq;
			cq = cq->next;
			free(tmp);
			cq->previous = NULL;
			*q = cq;
		}
		else
		{
			tmp = cq;
			cq = cq->next;
			cq->previous = tmp->previous;
			tmp->previous->next = cq;
			free(tmp);
			*q = cq;
		}
	}
}

void	ft_edit(t_lchar **q, char c)
{
	t_lchar	*tmp;
	t_lchar	*first;
	t_lchar	*qq;

	qq = *q;
	tmp = NULL;
	if (qq && qq->c == c)
	{
		tmp = qq;
		while (qq->c == c)
		{
			qq = qq->next;
		}
		first = ft_tabtolchar("{'");
		tmp = ft_lcharadd(tmp, first);
		first = ft_tabtolchar("'}");
		*q = ft_lcharadd(qq, first);
	}
}
