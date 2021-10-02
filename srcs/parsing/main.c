/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/02 14:31:07 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ccmd;

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
  ft_freecmd(ccmd);
  exit(0);
}

void	ft_init_minishell(t_minishell *minishell, char **envp)
{
	minishell->env = ft_init_env(envp);
	minishell->exit = 0;
	minishell->ret = 0;
	minishell->stdout = dup(STDOUT_FILENO);
	minishell->stdin = dup(STDIN_FILENO);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char			*cmd;
	//t_env			*env;
	t_minishell		minishell;

	ccmd = NULL;
	cmd = NULL;
	//env = ft_init_env(envp);
	ft_init_minishell(&minishell, envp);

	//
	while(minishell.exit == 0)
	{
		signal(SIGINT,sig_handler);
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		if (cmd != NULL)
		{
			add_history(cmd);
			ft_cutcmd(&ccmd,cmd);
			minishell.ret = exec_cmds(ccmd, &minishell);
			//printcmd();
			free(cmd);
			ft_freecmd(ccmd);
			ccmd = NULL;
			//if (mini->exit == 1)
				//break;
		}
		
	}
	return (minishell.ret);
}