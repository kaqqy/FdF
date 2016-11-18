/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarradd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:20:59 by jshi              #+#    #+#             */
/*   Updated: 2016/11/17 20:53:11 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_ptrarradd(void ***arr, void *addr, int *size)
{
	void	**realloc;
	int		cpy;
	int		limit;
	int		i;

	cpy = *size;
	limit = 1;
	while (cpy > 1)
	{
		cpy >>= 1;
		limit <<= 1;
	}
	if (*size == limit && limit > 3)
	{
		if (!(realloc = (void**)malloc(sizeof(*realloc) * 2 * limit)))
			return ;
		i = -1;
		while (++i < *size)
			realloc[i] = (*arr)[i];
		free(*arr);
		*arr = realloc;
	}
	(*arr)[*size] = addr;
	(*size)++;
}
