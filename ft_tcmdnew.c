/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcmdnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:08:43 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/19 16:03:24 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_tcmdnew(char **args)
{
	t_cmd *s;

	if (!(s = malloc(sizeof(t_cmd))))
		return (NULL);
	s->args = args;
	s->next = NULL;
	s->previous = NULL;
	return (s);
}
