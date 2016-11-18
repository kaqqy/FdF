/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:29:41 by jshi              #+#    #+#             */
/*   Updated: 2016/09/28 00:00:03 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qsort(int *arr, size_t num)
{
	size_t	a;
	size_t	b;

	if (num <= 1)
		return ;
	a = 0;
	b = 0;
	ft_swap(arr, arr + (((arr[num / 2] + arr[num / 3]) % num) + num) % num);
	while (++a < num)
	{
		if (arr[a] < arr[0])
		{
			b++;
			ft_swap(arr + a, arr + b);
		}
	}
	ft_swap(arr, arr + b);
	ft_qsort(arr, b);
	ft_qsort(arr + b + 1, num - b - 1);
}
