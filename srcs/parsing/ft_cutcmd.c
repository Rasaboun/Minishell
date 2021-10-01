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
	t_redir *cutcm;
	t_redir *newcut;
	newcut = NULL;
	cutcm = NULL;
	t_cmd	*cmds;


	i = 0;
	str = ft_strtok(line, "|;");
	ft_delquotes(str);
	while (str[i])
	{
		printf("|%s|\n",str[i]);
		newcut = ft_redirnew(str[i]);
		ft_rediradd_back(&cutcm, newcut);
		i++;
	}
	exit(0);
	while (cutcm)
	{
		if (cutcm->next && ft_strcmp(cutcm->next->str, "|") == 0)
		{
			strt = ft_split(cutcm->str, ' ');
			tmp = ft_tcmdnew(strt);
			tmp->type = PIPED;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next->next;
		}
		else if (cutcm->next && ft_strcmp(cutcm->next->str, ";") == 0)
		{
			strt = ft_split(cutcm->str, ' ');
			tmp = ft_tcmdnew(strt);
			tmp->type = BREAK;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next->next;
		}
		else
		{
			strt = ft_split(cutcm->str, ' ');
			tmp = ft_tcmdnew(strt);
			tmp->type = END;
			ft_tcmdadd_back(cmd, tmp);
			cutcm = cutcm->next;
		}
		i++;
	}

}