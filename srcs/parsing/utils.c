/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:37:10 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/10 17:45:24 by rasaboun         ###   ########.fr       */
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

static	int	ft_whil(char *s3, const char *s1, int i)
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

char	*delquotes(char *line, t_env *env)
{
	int		i;
	t_lchar	*q;
	t_lchar	*tmp;
	char	*final;
	t_lchar	*first;
	char	*str;

	str = NULL;
	i = 0;
	q = NULL;
	tmp = NULL;
	if (!line)
		return (NULL);
	while (line[i])
	{
		tmp = ft_lcharnew(line[i]);
		ft_lcharadd_back(&q, tmp);
		i++;
	}
	tmp = ft_lcharnew(line[i]);
	ft_lcharadd_back(&q, tmp);
	i = 0;
	free(line);
	line = NULL;

	while (q && q->next)
	{
		while (q && q->c == '\'')
		{
			if (!q->previous && q->next && q->c == '\'')
			{
				q->next->previous = NULL;
				q = q->next;
			}
			while (q->next && q->c != '\'' && q->c != '\0')
				q = q->next;
			if (q && q->previous && q->c == '\'')
			{
				q->previous->next = q->next;
				q->next->previous = q->previous;
			}
			if (q->c == '\'' && q->next->c == '\0' && !q->previous)
			{
				q->next->previous = NULL;
				q = q->next;
			}
			if (q->next)
				q = q->next;
		}
		while (q && q->c == '$')
		{
			if (q->next->c != ' ' && q->next->c != '\0')
			{
				quotesdl(&q, '$');
				if (q->c == '?' && (q->next->c == ' ' || q->next->c == '\"' || q->next->c == '\0'))
				{
					quotesdl(&q, '?');
					str = ft_itoa(g_minishell.ret);
				}
				else
				{
					final = get_dollar(&q);
					str = ft_env_value(final, env);
					free(final);
					final = NULL;
				}
				first = ft_tabtolchar(str);
				if (str)
				{
					free(str);
					str = NULL;
				}
				if (first)
					q = ft_lcharadd(q, first);
				else if (!q->previous)
				{
					ft_freeq(q);
					return (NULL);
				}
			}
		}
		while (q && q->c == '\"')
		{
			quotesdl(&q, '\"');
			while (q && q->next && q->c != '\"' && q->c != '\0')
			{
				while (q->c == '$')
				{
					if (q->next->c != ' ' && q->next->c != '\"')
					{
						quotesdl(&q, '$');
						if (q->c == '?' && (q->next->c == ' ' || q->next->c == '\"' || q->next->c == '\0'))
						{
							quotesdl(&q, '?');
							str = ft_itoa(g_minishell.ret);
						}
						else
						{
							final = get_dollar(&q);
							str = ft_env_value(final, env);
							free(final);
							final = NULL;
						}
						first = ft_tabtolchar(str);
						if (str)
						{
							free(str);
							str = NULL;
						}
						if (first)
							q = ft_lcharadd(q, first);
						else if (!q->previous)
						{
							ft_freeq(q);
							return (NULL);
						}
					}
				}
				if (q->c != '\"')
					q = q->next;
			}
			quotesdl(&q, '\"');
		}
		ft_edit(&q, '|');
		ft_edit(&q, ';');
		ft_edit(&q, '>');
		ft_edit(&q, '<');
		if (q && q->next)
			q = q->next;
	}
	if (!q)
		return (NULL);

	while (q->previous)
		q = q->previous;

	i = ft_lcharlen(q);
	final = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (q)
	{
		tmp = q;
		final[i] = q->c;
		q = q->next;
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (final);
}

int	strsetcmp(char **line, int i)
{
	char *l;

	l = line[i];
	if (!line[i])
		return (0);
	if (ft_strchr(";|><", line[i][0]))
	{
		if (i == 0 && (ft_strcmp(line[i], "{';'}") || ft_strcmp(line[i], "{'|'}")))
			return (1);
		if (i > 0 && (line[i][0] == ';' || line[i][0] == '|' || line[i][0] == '>' || line[i][0] == '<') && ft_strchr(";|><", line[i - 1][0]))
			return (1);
		if (line[i][0] != ';' && !line[i + 1])
			return (1);
		if (ft_strcmp(l, ">") && ft_strcmp(l, "<") && ft_strcmp(l, ";") &&
			ft_strcmp(l, "|") && ft_strcmp(l, "<<") && ft_strcmp(l, ">>"))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_delquotes(char **line, t_env *env)
{
	int i;

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