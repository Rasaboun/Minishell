
#include "minishell.h"

void sig_handler(int signum)
{
  exit(0);
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