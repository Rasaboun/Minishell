/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:33:38 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/06 23:28:25 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int				i;
	unsigned char	*str;
	unsigned char	*str2;

	i = 0;
	str = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	while ((size_t)i < n)
	{
		str[i] = str2[i];
		if (str[i] == (unsigned char)c)
			return ((void *)&dst[i + 1]);
		i++;
	}
	return (NULL);
}
