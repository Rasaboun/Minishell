/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtok_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:51:05 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 17:02:26 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whilecount(const char *line, char *strset, t_count *ct)
{
	if (whilequote_count(line, ct, '\'') == 0)
		return (0);
	if (whilequote_count(line, ct, '\"') == 0)
		return (0);
	if (whilealpha_count(line, strset, ct) == 0)
		return (0);
	return (1);
}

int	ft_countt(const char *line, char *strset)
{
	t_count	ct;

	ct.m = 0;
	ct.n = 0;
	ct.min = 0;
	ct.num = 0;
	ct.i = 0;
	while (line[ct.i] != '\0')
	{
		while (line[ct.i] && line[ct.i] == ' ')
			ct.i++;
		if (whilecount(line, strset, &ct) == 0)
			return (0);
		if (ft_strchr(strset, line[ct.i]))
		{
			while (line[ct.i] && ft_strchr(strset, line[ct.i]))
				ct.i++;
			ct.num++;
		}
	}
	return (ct.num);
}

void	ft_freee(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

int	init_strok(const char *line, char *strset, t_tok *t)
{
	t->num = ft_countt(line, strset);
	if (t->num < 1)
		return (1);
	t->str = malloc(sizeof(char *) * (t->num + 1));
	if (t->str == NULL)
	{
		ft_write_error("Error");
		g_minishell.ret = 1;
		return (1);
	}
	t->str[t->num] = NULL;
	t->i = 0;
	t->min = 0;
	t->num = 0;
	return (0);
}

void	while_quotes(const char *line, t_tok *t, char c, int w)
{
	if (line[t->i] == c)
	{
		if (w == 0)
			t->min = t->i;
		while (line[t->i] == c)
		{
			t->i++;
			while (line[t->i] && line[t->i] != c)
				t->i++;
			if (line[t->i] && line[t->i] == c)
			{
				t->i++;
				if (line[t->i] != c && line[t->i] != ' ')
					while (line[t->i] && line[t->i] != c)
						t->i++;
			}
		}
		t->str[t->num] = ft_substrs(line, t->min, t->i);
		if (!t->str[t->num])
			ft_freee(t->num, t->str);
		t->num++;
	}
}
