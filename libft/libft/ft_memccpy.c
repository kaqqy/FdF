/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:00:55 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:29:30 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	a;

	a = 0;
	while (a < n)
	{
		*((char*)dst + a) = *((char*)src + a);
		if (*((unsigned char*)src + a) == (unsigned char)c)
			return (dst + a + 1);
		a++;
	}
	return (NULL);
}
