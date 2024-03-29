/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutcmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:18:35 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/11 14:42:43 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whilequote(t_delquo *dq, t_env *env)
{
	if (while_quotesutils(dq, '\'', env) == 0)
		return (0);
	if (while_quotesutils(dq, '\"', env) == 0)
		return (0);
	return (1);
}

char	*ft_cutequotes(char *line)
{
	int		n;
	char	*l;

	l = NULL;
	n = ft_strlen(line);
	if ((n - 2) > 0)
	{
		l = ft_substr(line, 1, n - 1);
		return (l);
	}
	return (NULL);
}

void	addarg_utils(char **str, t_cm **cutcm, t_addargs *a)
{
	if (a->n > 0)
	{
		a->strt = malloc(sizeof(char *) * (a->n + 1));
		a->strt[a->n] = NULL;
		a->n--;
		a->ii = a->i - 1;
		while (a->n >= 0)
		{
			a->strt[a->n] = str[a->ii];
			a->n--;
			a->ii--;
		}
		a->newcut = ft_cmnew(a->strt);
		ft_cmadd_back(cutcm, a->newcut);
	}
	if (str[a->i])
	{
		a->strt = malloc(sizeof(char *) * 2);
		a->strt[0] = str[a->i];
		a->strt[1] = NULL;
		a->newcut = ft_cmnew(a->strt);
		ft_cmadd_back(cutcm, a->newcut);
		a->i++;
	}	
}
