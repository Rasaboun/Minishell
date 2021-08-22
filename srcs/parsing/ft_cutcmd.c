#include "minishell.h"

void	ft_cutcmd(t_cmd **cmd, char *line)
{
	int	i;
	char *l;
	int n;
	t_cmd *tmp;
	char **split;

	split = NULL;
	n = 0;
	l = NULL;
	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '|' || line[i] == ';')
		{
			if (line[i+1] == '|' || line[i+1] == ';')
			{
				write(2,"Error argument",15);
				//free
				exit(0);
			}
			l = ft_substr(line,n,i-n);
			split = ft_split(l,' ');
			free(l);
			tmp = ft_tcmdnew(split);
			if (line[i] == '|')
				tmp->type = PIPED;
			if (line[i] == ';')
				tmp->type = BREAK;
			ft_tcmdadd_back(cmd,tmp);
			i++;
			n = i;
		}
		else
			i++;
	}
		l = ft_substr(line,n,i-n);
		split = ft_split(l,' ');
		free(l);
		tmp = ft_tcmdnew(split);
		tmp->type = END;
		ft_tcmdadd_back(cmd,tmp);
}