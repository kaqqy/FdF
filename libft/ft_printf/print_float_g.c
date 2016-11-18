/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_g.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 01:50:49 by jshi              #+#    #+#             */
/*   Updated: 2016/11/01 00:57:13 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	apply_flags(char *inte, t_flags *f)
{
	int		ret;

	if (f->zero == 1 && f->minus == 0)
	{
		if (f->sign == 1 && f->plus == 0 && f->space == 0)
			prepend_char(&inte, '0', f->minwid);
		else
			prepend_char(&inte, '0', f->minwid - 1);
	}
	if (f->sign == -1)
		prepend_str(&inte, "-");
	else if (f->plus == 1)
		prepend_str(&inte, "+");
	else if (f->space == 1)
		prepend_str(&inte, " ");
	if (f->minus == 1)
		append_char(&inte, ' ', f->minwid);
	else
		prepend_char(&inte, ' ', f->minwid);
	ret = ft_strlen(inte);
	ft_putstr(inte);
	free(inte);
	return (ret);
}

static int	apply_flags_e(char *str, int i, int j, t_flags *f)
{
	char	*inte;
	char	*frac;
	char	*exp;

	j = (i - f->prec < j) ? j : i - f->prec + 1;
	str = round_float(str, j);
	inte = ft_strsub(str, i, 1);
	frac = ft_strsub(str, j, i - j);
	ft_strrev(inte);
	ft_strrev(frac);
	if (f->pound == 1 || ft_strlen(frac) > 0)
		append_str(&inte, ".");
	append_str(&inte, frac);
	if (f->pound == 1)
		append_char(&inte, '0', f->prec + 1);
	free(frac);
	(f->conv == 'G') ? append_str(&inte, "E") : append_str(&inte, "e");
	(i >= 6000) ? append_str(&inte, "+") : append_str(&inte, "-");
	exp = ft_itoa_base((i >= 6000) ? (i - 6000) : (6000 - i), 10);
	prepend_char(&exp, '0', 2);
	append_str(&inte, exp);
	free(exp);
	return (apply_flags(inte, f));
}

static int	apply_flags_f(char *str, int i, int j, t_flags *f)
{
	char	*inte;
	char	*frac;

	j = (i - f->prec < j) ? j : i - f->prec + 1;
	str = round_float(str, j);
	while (str[j] == '0' && j < 6000)
		j++;
	inte = ft_strsub(str, 6000, (i - 5999) <= 0 ? 1 : (i - 5999));
	frac = ft_strsub(str, j, 6000 - j);
	ft_strrev(inte);
	ft_strrev(frac);
	insert_commas(&inte, f->apos);
	if (f->pound == 1 || ft_strlen(frac) > 0)
		append_str(&inte, ".");
	append_str(&inte, frac);
	if (f->pound == 1)
		append_char(&inte, '0', f->prec + 1);
	free(frac);
	free(str);
	return (apply_flags(inte, f));
}

int			print_float_g(va_list *args, t_flags *f)
{
	long double	a;
	char		*str;
	int			i;
	int			j;

	if (f->lenmod == 7)
		a = va_arg(*args, long double);
	else
		a = va_arg(*args, double);
	f->sign = a < 0 ? -1 : 1;
	if ((i = handle_nan(a, f, 0)) >= 0)
		return (i);
	f->prec = (f->prec < 0) ? 6 : f->prec + !f->prec;
	str = get_float(a);
	i = 11999;
	while (str[i] == '0' && i >= 0)
		i--;
	i = i == -1 ? 6000 : i;
	j = 0;
	while (str[j] == '0' && j < i)
		j++;
	if (i - 6000 < -4 || i - 6000 >= f->prec)
		return (apply_flags_e(str, i, j, f));
	return (apply_flags_f(str, i, j, f));
}
