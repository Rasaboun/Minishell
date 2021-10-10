/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:18:37 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 14:59:43 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *cmd;
	t_cmd *ccmd;

	ccmd = NULL;
	cmd = NULL;
	ft_init_minishell(&g_minishell, envp);
	while (g_minishell.exit == 0)
	{
		set_signals();
		cmd = readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m ");
		if (cmd != NULL)
		{
			if (cmd && cmd[0] != '\0')
				add_history(cmd);
			ft_cutcmd(&ccmd, cmd, g_minishell.env);
			if (ccmd)
			{
				g_minishell.ret = exec_cmds(ccmd, &g_minishell);
				free(cmd);
				ft_freecmd(ccmd);
				ccmd = NULL;
			}
		}
		else
			ft_exit(ccmd, &g_minishell);
	}
	ft_clean_all(&g_minishell);
	return (g_minishell.ret);
}