/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/25 18:49:51 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void sig_handler(int signum)
{
  exit(0);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *cmd;
	t_cmd *ccmd;
	t_env *env;

	ccmd = NULL;
	cmd = NULL;
	env = ft_init_env(envp);
	//
	while(1)
	{
		signal(SIGINT,sig_handler);
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		if (cmd != NULL)
		{
			ft_cutcmd(&ccmd,cmd);
			exec_cmds(ccmd, env);
			//
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