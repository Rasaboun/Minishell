/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcmdadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:07:23 by rasaboun          #+#    #+#             */
/*   Updated: 2021/08/18 17:45:35 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tcmdadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*lst2;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst2 = ft_tcmdlast(*alst);
		lst2->next = new;
		new->next = NULL;
		new->previous = lst2;
	}
}
