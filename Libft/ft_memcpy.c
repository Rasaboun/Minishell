/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoriaki <dkoriaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:34:21 by rasaboun          #+#    #+#             */
/*   Updated: 2021/10/06 23:25:08 by dkoriaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*str;
	unsigned char	*str2;

	i = 0;
	str = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (!str && !str2)
		return (NULL);
	while ((size_t)i < n)
	{
		str[i] = str2[i];
		i++;
	}
	return (dst);
}
