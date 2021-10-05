/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/02 14:32:34 by rasaboun         ###   ########.fr       */
=======
/*   Updated: 2021/10/04 17:10:28 by dkoriaki         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ccmd;

void sig_handler(int signum)
{
  ft_freecmd(ccmd);
  exit(0);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char			*cmd;
	t_minishell		minishell;

	ccmd = NULL;
	cmd = NULL;
	ft_init_minishell(&minishell, envp);
	while(minishell.exit == 0)
	{
		signal(SIGINT,sig_handler);
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		if (cmd != NULL)
		{
			add_history(cmd);
			ft_cutcmd(&ccmd,cmd);
			minishell.ret = exec_cmds(ccmd, &minishell);
			free(cmd);
			ft_freecmd(ccmd);
			ccmd = NULL;
		}
	}
	ft_clean_all(&minishell);
	//Faut tout free
	return (minishell.ret);
}