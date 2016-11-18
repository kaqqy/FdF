/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 14:05:37 by jshi              #+#    #+#             */
/*   Updated: 2016/10/28 20:46:14 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "ft_printf.h"

char	*ft_itoa_base(uintmax_t n, int base)
{
	int			len;
	uintmax_t	pow;
	char		*str;

	len = 1;
	pow = 1;
	while (n / pow >= (uintmax_t)base)
	{
		pow *= base;
		len++;
	}
	if (!(str = (char*)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	if (!n)
		str[len] = '0';
	while (n)
	{
		if (n % base < 10)
			str[len--] = n % base + '0';
		else
			str[len--] = n % base - 10 + 'a';
		n /= base;
	}
	return (str);
}

char	*get_signed_int(va_list *args, t_flags *f, int base)
{
	intmax_t	a;

	if (f->lenmod == 3 || f->conv == 'D')
		a = va_arg(*args, long);
	else if (f->lenmod == 1)
		a = (char)va_arg(*args, int);
	else if (f->lenmod == 2)
		a = (short)va_arg(*args, int);
	else if (f->lenmod == 4)
		a = va_arg(*args, long long);
	else if (f->lenmod == 5)
		a = va_arg(*args, intmax_t);
	else if (f->lenmod == 6)
		a = va_arg(*args, ssize_t);
	else if (f->lenmod == 8)
		a = va_arg(*args, ptrdiff_t);
	else
		a = va_arg(*args, int);
	f->sign = 1;
	if (a < 0)
		f->sign = -1;
	f->num = (uintmax_t)(f->sign * a);
	return (ft_itoa_base(f->num, base));
}

char	*get_unsigned_int(va_list *args, t_flags *f, int base)
{
	if (f->lenmod == 5 || f->conv == 'p')
		f->num = va_arg(*args, uintmax_t);
	else if (f->lenmod == 3 || f->conv == 'U' || f->conv == 'O')
		f->num = va_arg(*args, unsigned long);
	else if (f->lenmod == 1)
		f->num = (unsigned char)va_arg(*args, unsigned int);
	else if (f->lenmod == 2)
		f->num = (unsigned short)va_arg(*args, unsigned int);
	else if (f->lenmod == 4)
		f->num = va_arg(*args, unsigned long long);
	else if (f->lenmod == 6)
		f->num = va_arg(*args, size_t);
	else
		f->num = va_arg(*args, unsigned int);
	f->sign = 0;
	return (ft_itoa_base(f->num, base));
}
