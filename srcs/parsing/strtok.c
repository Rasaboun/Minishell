/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:01:08 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 17:01:46 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
