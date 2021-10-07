/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:30:30 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/06 23:17:56 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*malzero(size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = (void *)malzero(size * count);
	if (!tab)
		return (NULL);
	return (tab);
}
