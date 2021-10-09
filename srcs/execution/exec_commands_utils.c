/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:07:52 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/10 01:11:42 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_exec_is_double_redir(t_cmd **cmd, t_minishell *minishell)
{
	int	ret;
	struct stat	sb;

	if ((*cmd)->type == PIPED || ((*cmd)->previous
			&& (*cmd)->previous->type == PIPED))
	{
		if (g_minishell.ret != 130 && g_minishell.ret != 131)
			ret = exec_with_pipe((*cmd), minishell);
	}
	else
		ret = exec_without_pipe((*cmd), minishell);
	(*cmd) = (*cmd)->next;
	if (stat("./.heredoc", &sb) == 0)
		unlink("./.heredoc");
	return (ret);
}