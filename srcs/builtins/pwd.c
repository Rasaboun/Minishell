/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 10:50:24 by dkoriaki          #+#    #+#             */
/*   Updated: 2021/10/04 15:34:20 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
	{
		write(STDOUT_FILENO, &path, ft_strlen(path));
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	return (FAILURE);
}
