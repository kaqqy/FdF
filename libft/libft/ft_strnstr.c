/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 20:46:50 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:33:20 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	if (*little == '\0')
		return ((char*)big);
	a = 0;
	while (big[a] && a < len)
	{
		b = 0;
		while (a + b < len && little[b] && big[a + b] == little[b])
			b++;
		if (!little[b])
			return ((char*)(big + a));
		a++;
	}
	return (NULL);
}
