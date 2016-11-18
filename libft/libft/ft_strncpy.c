/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:58:54 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:31:04 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	while (len--)
	{
		if (len < srclen)
			dst[len] = src[len];
		else
			dst[len] = '\0';
	}
	return (dst);
}
