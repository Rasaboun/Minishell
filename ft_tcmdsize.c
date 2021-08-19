/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcmdsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:08:54 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/18 17:43:43 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tcmdsize(t_cmd *lst)
{
	t_cmd	*lst2;
	int		i;

	lst2 = lst;
	i = 0;
	while (lst2 != NULL)
	{
		lst2 = lst2->next;
		i++;
	}
	return (i);
}
