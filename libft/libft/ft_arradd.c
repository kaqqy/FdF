/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 22:41:59 by jshi              #+#    #+#             */
/*   Updated: 2016/11/10 23:03:35 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_arradd(int **arr, int num)
{
	int		*realloc;
	int		size;
	int		limit;
	int		i;

	size = (*arr)[0];
	limit = 1;
	while (size > 1)
	{
		size >>= 1;
		limit <<= 1;
	}
	if ((*arr)[0] == limit && limit > 3)
	{
		if (!(realloc = (int*)malloc(sizeof(*realloc) * (2 * limit + 1))))
			return ;
		i = -1;
		while (++i <= (*arr)[0])
			realloc[i] = (*arr)[i];
		free(*arr);
		*arr = realloc;
	}
	(*arr)[0]++;
	(*arr)[(*arr)[0]] = num;
}
