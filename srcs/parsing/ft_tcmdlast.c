/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcmdlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:08:23 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/18 17:38:39 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_tcmdlast(t_cmd *lst)
{
	t_cmd	*lst2;

	lst2 = lst;
	if (!lst)
		return ((void *)0);
	while (lst2->next)
		lst2 = lst2->next;
	return (lst2);
}
