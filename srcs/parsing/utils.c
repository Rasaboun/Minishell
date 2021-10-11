/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:37:10 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/11 12:33:56 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_quotesutils(t_delquo *dq, char c, t_env *env)
{
	while (dq->q && dq->q->c == c)
	{
		quotesdl(&dq->q, c);
		while (dq->q && dq->q->next && dq->q->c != c && dq->q->c != '\0')
		{
			if (c == '\"')
			{
				if (dollarsget(dq, env) == 0)
					return (0);
			}
			if (dq->q->c != c)
				dq->q = dq->q->next;
		}
		quotesdl(&dq->q, c);
	}
	return (1);
}

void	delquotes_util(t_delquo *dq)
{
	int	i;

	i = 0;
	while (dq->q->previous)
		dq->q = dq->q->previous;
	i = ft_lcharlen(dq->q);
	dq->final = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (dq->q)
	{
		dq->tmp = dq->q;
		dq->final[i] = dq->q->c;
		dq->q = dq->q->next;
		free(dq->tmp);
		dq->tmp = NULL;
		i++;
	}	
}

char	*delquotes(char *line, t_env *env)
{
	t_delquo	dq;

	dq.str = NULL;
	dq.q = NULL;
	dq.tmp = NULL;
	if (!line)
		return (NULL);
	chartolchar(line, &dq.q);
	while (dq.q && dq.q->next)
	{
		while_quotesutils(&dq, '\'', env);
		if (dq.q && dq.q->c == '$')
			if (dollarsget(&dq, env) == 0)
				return (NULL);
		if (while_quotesutils(&dq, '\"', env) == 0)
			return (NULL);
		ft_all_edit(&dq.q);
		if (dq.q && dq.q->next)
			dq.q = dq.q->next;
	}
	if (!dq.q)
		return (NULL);
	delquotes_util(&dq);
	return (dq.final);
}

int	strsetcmp(char **line, int i)
{
	char	*l;

	l = line[i];
	if (!line[i])
		return (0);
	if (ft_strchr(";|><", line[i][0]))
	{
		if (i == 0 && (ft_strcmp(l, "|") == 0 || ft_strcmp(l, ";") == 0))
			return (1);
		if (i > 0 && (line[i][0] == ';' || line[i][0] == '|' \
			|| line[i][0] == '>' || line[i][0] == '<') && \
				ft_strchr(";|><", line[i - 1][0]))
			return (1);
		if (line[i][0] != ';' && !line[i + 1])
			return (1);
		if (ft_strcmp(l, ">") && ft_strcmp(l, "<") && ft_strcmp(l, ";") && \
			ft_strcmp(l, "|") && ft_strcmp(l, "<<") && ft_strcmp(l, ">>"))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_delquotes(char **line, t_env *env)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] && strsetcmp(line, i))
		{
			ft_werror("syntax error near unexpected token `", line[i], "'");
			g_minishell.ret = 2;
			return (0);
		}
		i++;
	}
	i = 0;
	while (line[i])
	{
		line[i] = delquotes(line[i], env);
		i++;
	}
	return (1);
}
