/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 15:14:19 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 16:20:29 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	a;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	a = 0;
	if (!size)
		return (srclen);
	while (dstlen + a < size - 1 && a < srclen)
	{
		dst[dstlen + a] = src[a];
		a++;
	}
	if (dstlen + a < size)
		dst[dstlen + a] = '\0';
	return ((dstlen > size ? size : dstlen) + srclen);
}
