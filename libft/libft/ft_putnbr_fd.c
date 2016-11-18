/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:00:36 by jshi              #+#    #+#             */
/*   Updated: 2016/09/22 16:01:54 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		pos;
	int		digit;

	pos = 1;
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (n / pos >= 10 || n / pos <= -10)
		pos *= 10;
	while (pos)
	{
		digit = (n / pos) % 10;
		digit = digit < 0 ? -digit : digit;
		ft_putchar_fd(digit + '0', fd);
		pos /= 10;
	}
}
