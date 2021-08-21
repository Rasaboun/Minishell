
#include"minishell.h"


void sig_handler(int signum)
{
  exit(0);
}
//
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


int main()
{
	char *cmd;
	t_cmd *ccmd;

	ccmd = NULL;
	cmd = NULL;
	while(1)
	{
		signal(SIGINT,sig_handler);
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		if (cmd != NULL)
		{
			ft_cutcmd(&ccmd,cmd);
			break;
		}
		
	}
	while(ccmd != NULL) // AFFICHE CHAQUE COMMANDE AVEC SON TYPE
	{
		printf("%s",ccmd->args[0]);
		if (ccmd->type == PIPED)
			printf(" TYPE PIPED\n");
		if (ccmd->type == BREAK)
			printf(" TYPE BREAK\n");
		if (ccmd->type == END)
			printf(" TYPE END\n");
		ccmd = ccmd->next;
	}

}