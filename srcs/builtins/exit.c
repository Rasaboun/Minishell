/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:42:40 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 15:40:04 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *ccmd, t_minishell *minishell)
{
	int		ret;

	minishell->exit = 1;
	ret = 0;
	ft_write_error("exit\n");
	if (!ccmd->args[1])
		return (ret);
	if (ft_isnum(ccmd->args[1]) == 1 && !ccmd->args[2])
		ret = ft_atoi(ccmd->args[1]);
	else if (ccmd->args[1] && ft_isnum(ccmd->args[1]) == 0)
	{
		ret = 255;
		ft_write_error("minishell: exit: ");
		ft_write_error(ccmd->args[1]);
		ft_write_error(": numeric argument required\n");
	}
	else if (ft_isnum(ccmd->args[1]) == 1 && ccmd->args[2])
	{
		minishell->exit = 0;
		ret = 1;
		ft_write_error("minishell: exit: too many arguments\n");
	}
	return (ret);
}
