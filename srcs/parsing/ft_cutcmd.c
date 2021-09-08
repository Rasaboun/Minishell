#include "minishell.h"

int	ft_quotes(t_cmd **cmd, char *line, int i)
{
	int n;
	char *l;

	l = NULL;


	n = 0;
	if (line[i] == '"')
	{
		while(line[i] != '"' && line[i] != '\0')
			i++;
		if (line[i] == '\0')
			return (-1);
		else
		{

			return (i);	
		}
			
	}

}


void	ft_cutcmd(t_cmd **cmd, char *line)
{
	int	i;
	char *l;
	int n;
	t_cmd *tmp;
	char **split;
	int q;

	q = 0;
	split = NULL;
	n = 0;
	l = NULL;
	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '\'')// 39 = '
		{
			q++;
			i++;
		while(line[i] != '\'' && line[i] != '\0')
			i++;
		if (line[i] == '\0')
		{
			write(2,"Error argument",15);
			//free
			exit(0);
		}
		}
		if (line[i] == '|' || line[i] == ';')
		{
			q = 0;
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
		i++;
	}
		l = ft_substr(line,n,i-n);
		if (q == 0)
		{
		split = ft_split(l,' ');
		free(l);
		tmp = ft_tcmdnew(split);
		}
		else
		{
			split = ft_split(l,-1);
			free(l);
			tmp = ft_tcmdnew(split);
		}
		tmp->type = END;
		ft_tcmdadd_back(cmd,tmp);
}