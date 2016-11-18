/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:32:12 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:30:00 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*uc1;
	unsigned char	*uc2;

	uc1 = (unsigned char*)s1;
	uc2 = (unsigned char*)s2;
	while (n && *uc1 == *uc2)
	{
		uc1++;
		uc2++;
		n--;
	}
	if (!n)
		return (0);
	return (*uc1 - *uc2);
}
