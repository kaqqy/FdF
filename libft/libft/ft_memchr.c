/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:25:04 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:29:50 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*uc;

	uc = (unsigned char*)s;
	while (n--)
	{
		if (*uc == (unsigned char)c)
			return ((void*)uc);
		uc++;
	}
	return (NULL);
}
