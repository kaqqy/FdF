/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:35:55 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 23:37:49 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		pow_ten;

	len = n < 0 ? 2 : 1;
	pow_ten = 1;
	while ((n / pow_ten >= 10 || n / pow_ten <= -10) && ++len)
		pow_ten *= 10;
	str = ft_strnew(sizeof(*str) * len);
	if (!str)
		return (NULL);
	if (!n)
		str[0] = '0';
	else if (n < 0)
		str[0] = '-';
	while (n)
	{
		str[--len] = (n % 10 < 0 ? -(n % 10) : n % 10) + '0';
		n /= 10;
	}
	return (str);
}
