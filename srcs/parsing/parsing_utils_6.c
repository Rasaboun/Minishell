/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:10:41 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/11 22:02:15 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freeq(t_lchar *q)
{
	t_lchar	*tmp;

	tmp = NULL;
	while (q->previous)
		q = q->previous;
	while (q)
	{
		tmp = q;
		q = q->next;
		free(tmp);
	}
}

void	chartolchar(char *line, t_lchar **q)
{
	int		i;
	t_lchar	*tmp;

	i = 0;
	while (line[i])
	{
		tmp = ft_lcharnew(line[i]);
		ft_lcharadd_back(q, tmp);
		i++;
	}
	tmp = ft_lcharnew(line[i]);
	ft_lcharadd_back(q, tmp);
	free(line);
	line = NULL;
}

void	dollar_utils(t_delquo *d, t_env *env)
{
	if (d->q->c == '?')
	{
		quotesdl(&d->q, '?');
		d->str = ft_itoa(g_minishell.ret);
	}
	else
	{
		d->final = get_dollar(&d->q);
		d->str = ft_env_value(d->final, env);
		free(d->final);
		d->final = NULL;
	}
}

int	dollarsget(t_delquo *d, t_env *env)
{
	while (d->q && d->q->c == '$')
	{
		if (d->q->next->c != ' ' && d->q->next->c != \
			'\0' && d->q->next->c != '\"' && (ft_isalnum(d->q->next->c) \
				|| d->q->next->c == '?'))
		{
			quotesdl(&d->q, '$');
			dollar_utils(d, env);
			d->first = ft_tabtolchar(d->str);
			if (d->str)
				free(d->str);
			if (d->first)
				d->q = ft_lcharadd(d->q, d->first);
			else if (!d->q->previous && !d->q->next)
			{
				ft_freeq(d->q);
				return (0);
			}
		}
		if (d->q && d->q->c == '$' && d->q->next && \
			ft_isalnum(d->q->next->c) != 1)
			d->q = d->q->next;
	}
	return (1);
}

void	ft_all_edit(t_lchar **q)
{
	ft_edit(q, '|');
	ft_edit(q, ';');
	ft_edit(q, '>');
	ft_edit(q, '<');
}
