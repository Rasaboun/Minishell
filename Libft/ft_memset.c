/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:34:56 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/06 23:23:56 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while ((size_t)i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
