/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 23:24:08 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/11 23:28:23 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tkt(char **line, t_env *env)
{
	int		i;
	t_redir	*l;
	t_redir	*tmp;

	tmp = NULL;
	l = NULL;
	i = 0;
	while (line[i])
	{
		line[i] = delquotes(line[i], env);
		tmp = ft_redirnew(line[i]);
		ft_rediradd_back(&l, tmp);
		i++;
	}
	lstrto_str(l, line);
}

void	strdl(t_redir **q, char *c)
{
	t_redir	*cq;
	t_redir	*tmp;

	tmp = NULL;
	cq = *q;
	if (cq && cq->str == c)
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
