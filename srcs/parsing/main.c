/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/07 19:36:31 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void sig_handler(int signum)
{
  printf("\n");
  rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char			*cmd;
	t_minishell		minishell;
	t_cmd *ccmd;
	ccmd = NULL;
	cmd = NULL;
	ft_init_minishell(&minishell, envp);
	while(minishell.exit == 0)
	{
		
		//signal(SIGQUIT,sig_handler);
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		fprintf(stderr, "Line : %s\n",cmd);
		signal(SIGINT,sig_handler);
		if (cmd != NULL)
		{
			if (cmd && cmd[0] != '\0')
				add_history(cmd);
			ft_cutcmd(&ccmd,cmd,minishell.env);
			minishell.ret = exec_cmds(ccmd, &minishell);
			free(cmd);
			ft_freecmd(ccmd);
			ccmd = NULL;
		}
<<<<<<< HEAD
		else
			exit(0);
=======
>>>>>>> master
	}
	ft_clean_all(&minishell);
	//Faut tout free
	return (minishell.ret);
}