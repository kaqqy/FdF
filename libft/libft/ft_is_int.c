/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 20:33:39 by jshi              #+#    #+#             */
/*   Updated: 2016/11/21 20:36:43 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_int(char *str)
{
	long	num;
	long	sign;
	int		count;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	count = 0;
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
		count++;
	}
	num *= sign;
	if (!*str && count && count < 11 &&
			num >= -2147483648 && num <= 2147483647)
		return (1);
	return (0);
}
