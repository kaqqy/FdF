/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:57:32 by jshi              #+#    #+#             */
/*   Updated: 2016/09/27 23:42:25 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double n)
{
	double	lower;
	double	upper;
	double	mid;

	if (n < 0)
		return (-1);
	lower = 0;
	upper = n < 1 ? 1 : n;
	while (lower != upper)
	{
		mid = (lower + upper) / 2;
		if (mid == lower || mid == upper)
			return (mid);
		if (mid * mid < n)
			lower = mid;
		else
			upper = mid;
	}
	return (mid);
}
