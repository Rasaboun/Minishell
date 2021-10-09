/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:35:49 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/09 23:07:08 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_is_double_redir_left(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (strcmp(cmd->args[i], "'<<'") == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}