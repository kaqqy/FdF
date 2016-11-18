/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 22:27:10 by jshi              #+#    #+#             */
/*   Updated: 2016/10/28 17:20:02 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char		*round_float(char *str, int pos)
{
	int		i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (pos < 1 || pos >= 12000)
		return (str);
	if (i == pos - 1 && str[pos - 1] == '5')
	{
		if ((str[pos] - '0') % 2 == 0)
			return (str);
		str[pos]++;
	}
	else if (str[pos - 1] >= '5')
		str[pos]++;
	while (str[pos] == '0' + 10)
	{
		str[pos] = '0';
		pos++;
		str[pos]++;
	}
	return (str);
}

int			handle_nan(long double a, t_flags *f, int ret)
{
	char		*str;

	if (a != a)
		str = ft_strdup("nan");
	else if (a == 1.0 / 0.0 || a == -1.0 / 0.0)
		str = ft_strdup("inf");
	else
		return (-1);
	(f->conv >= 'A' && f->conv <= 'Z') ? ft_strtoupper(str) : 0;
	if (f->sign == -1 && a == a)
		prepend_str(&str, "-");
	else if (f->plus == 1 && a == a)
		prepend_str(&str, "+");
	else if (f->space == 1 && a == a)
		prepend_str(&str, " ");
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	prepend_char(&str, ' ', f->minwid);
	ft_putstr(str);
	ret = ft_strlen(str);
	free(str);
	return (ret);
}

static int	apply_flags(char *inte, char *frac, t_flags *f, int ret)
{
	insert_commas(&inte, f->apos);
	if (f->pound == 1 || ft_strlen(frac) > 0)
		append_str(&inte, ".");
	append_str(&inte, frac);
	free(frac);
	if (f->zero == 1 && f->minus == 0)
	{
		prepend_char(&inte, '0', f->minwid - 1);
		if (f->sign == 1 && f->plus == 0 && f->space == 0)
			prepend_char(&inte, '0', f->minwid);
	}
	if (f->sign == -1)
		prepend_str(&inte, "-");
	else if (f->plus == 1)
		prepend_str(&inte, "+");
	else if (f->space == 1)
		prepend_str(&inte, " ");
	if (f->minus == 1)
		append_char(&inte, ' ', f->minwid);
	prepend_char(&inte, ' ', f->minwid);
	ret = ft_strlen(inte);
	ft_putstr(inte);
	free(inte);
	return (ret);
}

int			print_float(va_list *args, t_flags *f)
{
	long double	a;
	char		*str;
	char		*frac;
	char		*inte;
	int			i;

	if (f->lenmod == 7)
		a = va_arg(*args, long double);
	else
		a = va_arg(*args, double);
	f->sign = a < 0 ? -1 : 1;
	if ((i = handle_nan(a, f, 0)) >= 0)
		return (i);
	if (f->prec < 0)
		f->prec = 6;
	str = round_float(get_float(a), 6000 - f->prec);
	frac = ft_strsub(str, 6000 - f->prec, f->prec);
	ft_strrev(frac);
	i = 11999;
	while (str[i] == '0' && i >= 5999)
		i--;
	inte = ft_strsub(str, 6000, (i - 5999) <= 0 ? 1 : (i - 5999));
	ft_strrev(inte);
	free(str);
	return (apply_flags(inte, frac, f, 0));
}
