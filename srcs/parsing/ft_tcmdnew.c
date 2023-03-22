/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcmdnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:08:43 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/10 17:04:49 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_tcmdnew(char **args)
{
	t_cmd	*s;

	s = malloc(sizeof(t_cmd));
	if (!s)
		return (NULL);
	s->args = args;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}
