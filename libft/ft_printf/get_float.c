/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 21:36:33 by jshi              #+#    #+#             */
/*   Updated: 2016/10/26 20:07:18 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static char	*get_pow(int base, int exp)
{
	char	*str;
	int		i;
	int		len;
	int		carry;

	if (!(str = (char*)malloc(sizeof(*str) * (exp + 2))))
		return (NULL);
	i = 0;
	str[0] = '1';
	len = 1;
	while (++i < exp + 2)
		str[i] = '0';
	while (exp-- && (carry = 1))
	{
		i = -1;
		while ((carry /= 10) >= 0 && ++i < len)
		{
			carry += (str[i] - '0') * base;
			str[i] = carry % 10 + '0';
		}
		if ((str[len] = carry + '0') != '0')
			len++;
	}
	str[len] = '\0';
	return (str);
}

static void	add_num(char *dst, char *src)
{
	int		carry;
	int		i;

	if (!dst || !src)
		return ;
	carry = 0;
	i = 0;
	while (src[i])
	{
		carry += *dst + src[i] - '0' * 2;
		*dst = carry % 10 + '0';
		carry /= 10;
		dst++;
		i++;
	}
	while (carry)
	{
		carry += *dst - '0';
		*dst = carry % 10 + '0';
		carry /= 10;
		dst++;
	}
	free(src);
}

static void	fill_float_arr(char *str, unsigned long *frac, int exp)
{
	unsigned long	bit;

	bit = 1UL << 63;
	while (bit)
	{
		if (!(*frac & bit))
		{
			exp--;
			bit >>= 1;
			continue ;
		}
		if (exp >= 0)
			add_num(str + 6000, get_pow(2, exp));
		else
			add_num(str + 6000 + exp, get_pow(5, -exp));
		exp--;
		bit >>= 1;
	}
}

char		*get_float(long double a)
{
	unsigned long	*frac;
	int				i;
	int				exp;
	char			*str;

	if (!(str = (char*)malloc(sizeof(*str) * 12001)))
		return (NULL);
	i = -1;
	while (++i < 12000)
		str[i] = '0';
	str[12000] = '\0';
	frac = (unsigned long*)&a;
	exp = (frac[1] & ((1 << 15) - 1)) - (1 << 14) + 1;
	fill_float_arr(str, frac, exp);
	return (str);
}
