/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:14:09 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 22:56:58 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addarg(char **str, t_cm **cutcm)
{
	t_addargs	a;

	a.ii = 0;
	a.n = 0;
	a.newcut = NULL;
	a.i = 0;
	while (str[a.i])
	{
		a.n = 0;
		while (str[a.i] && ft_strcmp(str[a.i], "{'|'}") \
			!= 0 && ft_strcmp(str[a.i], "{';'}") != 0)
		{
			a.n++;
			a.i++;
		}
		if (a.n > 0)
		{
			addarg_utils(str, cutcm, &a);
		}	
	}
	free(str);
	str = NULL;
}

void	ft_freedarg(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

t_cm	*addcmd_utils(t_cm *cutcm, t_cmd **cmd, int type)
{
	t_cmd	*tmp;
	t_cm	*tmmp;

	tmmp = NULL;
	tmp = NULL;
	tmp = ft_tcmdnew(cutcm->str);
	tmmp = cutcm;
	tmp->type = type;
	ft_tcmdadd_back(cmd, tmp);
	cutcm = cutcm->next->next;
	ft_freedarg(tmmp->next->str);
	free(tmmp->next);
	free(tmmp);
	return (cutcm);
}

void	ft_addcmd(t_cm *cutcm, t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cm	*tmmp;

	tmmp = NULL;
	tmp = NULL;
	while (cutcm)
	{
		if (cutcm->next && ft_strcmp(cutcm->next->str[0], "{'|'}") == 0)
			cutcm = addcmd_utils(cutcm, cmd, PIPED);
		else if (cutcm->next && ft_strcmp(cutcm->next->str[0], "{';'}") == 0)
			cutcm = addcmd_utils(cutcm, cmd, BREAK);
		else
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmmp = cutcm;
			tmp->type = END;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next;
			free(tmmp);
		}
	}
}

void	ft_cutcmd(t_cmd **cmd, char *line, t_env *env)
{
	char	**str;
	t_cm	*cutcm;

	cutcm = NULL;
	str = ft_strtok(line, "|;><");
	if (!ft_delquotes(str, env))
	{
		if (str)
			ft_freedarg(str);
		free(line);
		*cmd = NULL;
		return ;
	}
	if (!str || str[0] == NULL)
	{	
		if (str)
			ft_freedarg(str);
		free(line);
		*cmd = NULL;
		return ;
	}
	ft_addarg(str, &cutcm);
	ft_addcmd(cutcm, cmd);
}
