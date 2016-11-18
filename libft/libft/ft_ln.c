/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 16:03:25 by jshi              #+#    #+#             */
/*   Updated: 2016/09/27 16:20:11 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_scinot(double *n, int *powten)
{
	while (*n >= 10)
	{
		*n /= 10;
		(*powten)++;
	}
	while (*n < 1)
	{
		*n *= 10;
		(*powten)--;
	}
}

static double	ft_ln_small(double n)
{
	int		a;
	double	pown;
	double	val;

	n = (n - 1) / (n + 1);
	pown = n;
	a = -1;
	val = 0;
	while (++a < 100)
	{
		val += pown / (2 * a + 1);
		pown *= n * n;
	}
	return (2 * val);
}

double			ft_ln(double n)
{
	int		powten;

	powten = 0;
	if (n <= 0)
		return (n);
	ft_scinot(&n, &powten);
	return (ft_ln_small(n) + ft_ln_small(10) * powten);
}
