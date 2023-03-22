/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:01:08 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/11 23:36:33 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstrto_str(t_redir *l, char **line)
{	
	int		i;
	t_redir	*tmp;

	tmp = NULL;
	i = 0;
	while (l->next)
	{
		strdl(&l, NULL);
		if (l && l->str != NULL && l->next)
			l = l->next;
	}
	while (l->previous)
		l = l->previous;
	while (l)
	{
		tmp = l;
		line[i] = l->str;
		l = l->next;
		free(tmp);
		i++;
	}
	line[i] = NULL;
}

void	get_dollars_util(t_lchar **lst, t_dollars *d)
{
	if (d->lchar->next && ft_isdigit(d->lchar->c))
	{
		d->i++;
		d->line = (char *)malloc(sizeof(char) * (d->i + 1));
		d->lchar = *lst;
		d->i = 0;
		if (d->lchar->next && ft_isdigit(d->lchar->c))
		{
			d->tmp = d->lchar->next;
			d->line[d->i] = d->lchar->c;
			free(d->lchar);
			d->lchar = d->tmp;
			d->i++;
		}
		d->line[d->i] = '\0';
	}
}

void	alphanum_strtok(t_tok *t, char *line, char *strset)
{
	if (line[t->i] && ft_is(line[t->i]) && !ft_strchr(strset, line[t->i]))
	{
		t->min = t->i;
		while (line[t->i] && ft_is(line[t->i])
			&& !ft_strchr(strset, line[t->i]))
			t->i++;
		if (line[t->i] == '\'')
			while_quotes(line, t, '\'', 1);
		else if (line[t->i] == '\"')
			while_quotes(line, t, '\"', 1);
		else if (t->min < t->i)
		{
			t->str[t->num] = ft_substrs(line, t->min, t->i);
			if (!t->str[t->num])
				ft_freee(t->num, t->str);
			t->num++;
		}
	}
}

void	strset_strtok(t_tok *t, char *line, char *strset)
{
	if (line[t->i] && ft_strchr(strset, line[t->i]))
	{
		t->min = t->i;
		while (line[t->i] && ft_strchr(strset, line[t->i]))
			t->i++;
		t->str[t->num] = ft_substrs(line, t->min, t->i);
		if (!t->str[t->num])
			ft_freee(t->num, t->str);
		t->num++;
	}
}

char	**ft_strtok(char *line, char *strset)
{
	t_tok	t;

	if (!line)
		return (NULL);
	if (init_strok(line, strset, &t) == 1)
		return (NULL);
	while (line[t.i] != '\0')
	{
		while (line[t.i] && line[t.i] == ' ')
			t.i++;
		while_quotes(line, &t, '\'', 0);
		while_quotes(line, &t, '\"', 0);
		alphanum_strtok(&t, line, strset);
		strset_strtok(&t, line, strset);
		if (line[t.i] == ' ')
			t.i++;
	}
	return (t.str);
}
