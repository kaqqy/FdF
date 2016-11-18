/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 20:40:11 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 15:33:12 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	a;
	size_t	b;

	if (*little == '\0')
		return ((char*)big);
	a = 0;
	while (big[a])
	{
		b = 0;
		while (little[b] && big[a + b] == little[b])
			b++;
		if (!little[b])
			return ((char*)(big + a));
		a++;
	}
	return (NULL);
}
