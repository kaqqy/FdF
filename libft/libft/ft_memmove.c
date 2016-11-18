/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:36:57 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:34:05 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	a;

	a = 0;
	if (dst < src)
	{
		while (len--)
		{
			*((char*)dst + a) = *((char*)src + a);
			a++;
		}
	}
	else
	{
		while (len--)
			*((char*)dst + len) = *((char*)src + len);
	}
	return (dst);
}
