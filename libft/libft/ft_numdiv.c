/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numdiv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 23:54:31 by jshi              #+#    #+#             */
/*   Updated: 2016/09/27 23:49:03 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_numdiv(int n)
{
	int		numdiv;
	int		count;
	int		divisor;

	if (n <= 0)
		return (0);
	numdiv = 1;
	divisor = 2;
	while (n / divisor >= divisor)
	{
		count = 1;
		while (n % divisor == 0)
		{
			n /= divisor;
			count++;
		}
		numdiv *= count;
		divisor++;
	}
	return (numdiv * (n > 1 ? 2 : 1));
}
