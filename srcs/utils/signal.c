/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:07:57 by dkoriaki          #+#    #+#             */
/*   Updated: 2023/03/22 23:13:43 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_minishell.ret = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	stop_bin_process(int signum)
{
	if (signum == SIGINT)
	{
		g_minishell.ret = 130;
		write(1, "\n", 1);
	}
}

void	quit_bin_process(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_minishell.ret = 131;
	}
}

void	set_signals(void)
{
	signal(SIGINT, prompt_signal);
	signal(SIGQUIT, SIG_IGN);
}
