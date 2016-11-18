/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_primearr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:44:29 by jshi              #+#    #+#             */
/*   Updated: 2016/09/29 10:03:36 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_nextprime(char *soe, int ub, int p)
{
	int		s;

	s = 1;
	while (ub / ++s >= p)
		soe[s * p] = 1;
	s = p + 1;
	while (soe[s])
		s++;
	return (s);
}

int			*ft_primearr(int n)
{
	int		*pa;
	char	*soe;
	int		ub;
	int		a;

	if (n <= 0)
		return (NULL);
	ub = (int)(n * ft_ln(n * ft_ln(n)));
	if (n < 6)
		ub = 2 * n + 1;
	pa = (int*)malloc(sizeof(*pa) * n);
	soe = ft_strnew(ub);
	if (!pa || !soe)
	{
		free(pa);
		free(soe);
		return (NULL);
	}
	a = 0;
	pa[0] = 2;
	while (++a < n)
		pa[a] = ft_nextprime(soe, ub, pa[a - 1]);
	free(soe);
	return (pa);
}
