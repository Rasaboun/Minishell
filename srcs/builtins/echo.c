/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:19:07 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/08/25 22:16:31 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *ccmd)
{
	int		new_line;
	int		i;

	new_line = 0;
	i = 1;
	printf("carrote\n");
	if (ccmd->args[1] && ft_strcmp(ccmd->args[1], "-n") == 0)
		new_line = 1;
	while (ccmd->args[i])	
	{
		if (i > 1)
			write(STDOUT_FILENO, " ", 1);
		ft_putstr(ccmd->args[i]);
		i++;
	}
	if (new_line)
		return (1);
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}
 // Je ne sais pas pq mais quand je fais plsrs fois echo qlq chose, ca affiche
 // ce que j'ai deja écris
 //essaie de faire "echo ca" et a la suite "echo va"
 // t'aura :
 // ca
 // ca           <- lui il est de trop
 // va