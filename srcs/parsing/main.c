/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/01 16:02:24 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"






void	ft_freecmd(t_cmd *cmd)
{
	int i;
	t_cmd *tmp;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		tmp = cmd;
		
		cmd = cmd->next;
		free(tmp);
	}
}



void sig_handler(int signum)
{
  exit(0);
}

void	printcmd()
{
	while(g_ccmd != NULL) // AFFICHE CHAQUE COMMANDE AVEC SON TYPE
	{
		printf("%s",g_ccmd->args[0]);
		if (g_ccmd->type == PIPED)
			printf(" TYPE PIPED\n");
		if (g_ccmd->type == BREAK)
			printf(" TYPE BREAK\n");
		if (g_ccmd->type == END)
			printf(" TYPE END\n");
		g_ccmd = g_ccmd->next;
	}
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *cmd;
	t_env *env;
	t_cmd *tmp;
	g_ccmd = NULL;
	cmd = NULL;
	env = ft_init_env(envp);
	//
	while(1)
	{
		signal(SIGINT,sig_handler);
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		if (cmd != NULL)
		{
			ft_cutcmd(&g_ccmd,cmd);
			/*while (g_ccmd)
			{
				for (int y = 0; g_ccmd->args[y];y++)
					printf("|%s|",g_ccmd->args[y]);
				g_ccmd = g_ccmd->next;
			}*/
			
			exit(0);
			//exec_cmds(ccmd, env);
			//break;
		}
		
	}


}