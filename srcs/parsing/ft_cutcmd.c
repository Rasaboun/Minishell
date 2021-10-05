/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:14:09 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 18:14:10 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

char	*ft_cutequotes(char *line)
{
	int n;
	char *l;

	l = NULL;

	n = ft_strlen(line);
	if ((n - 2) > 0)
	{
		l = ft_substr(line, 1, n-1);
		return (l);
	}
	return (NULL);
}


void	ft_cutcmd(t_cmd **cmd, char *line)
{
	int	i;
	char *l;
	int n;
	t_cmd *tmp;
	char **str;
	char **strt;
	t_cm *cutcm;
	t_cm *newcut;
	newcut = NULL;
	cutcm = NULL;
	t_cmd	*cmds;
	int ii;

	ii = 0;
	n = 0;

	i = 0;
	str = ft_strtok(line, "|;");
	ft_delquotes(str);
	while (str[i])
	{
		n = 0;
		while (str[i] && ft_strcmp(str[i], "|") != 0)
		{
			n++;
			i++;
		}
		if (n > 0)
		{
			strt = malloc(sizeof(char*) * n+1);
			strt[n] = NULL;
			n--;
			ii = i-1;
			while (n >= 0)
			{
				strt[n] = str[ii];
				n--;
				ii--;
			}
			newcut = ft_cmnew(strt);
			ft_cmadd_back(&cutcm, newcut);
		}
		if (str[i])
		{
			strt = malloc(sizeof(char*) * 2);
			strt[0] = str[i];
			strt[1] = NULL;
			newcut = ft_cmnew(strt);
			ft_cmadd_back(&cutcm, newcut);
			i++;
		}	
	}

	while (cutcm)
	{
		/*for (int u = 0;cutcm->str[u];u++)
			printf("string = %s\n",cutcm->str[u]);
		printf("PAUSE");*/
		cutcm = cutcm->next;
	}
	exit(0);
	
	while (cutcm)
	{
		if (cutcm->next && ft_strcmp(cutcm->next->str[0], "|") == 0)
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmp->type = PIPED;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next->next;
		}
		else if (cutcm->next && ft_strcmp(cutcm->next->str[0], ";") == 0)
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmp->type = BREAK;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next->next;
		}
		else
		{
			tmp = ft_tcmdnew(cutcm->str);
			tmp->type = END;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next;
		}
		i++;
	}

}