/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 19:18:29 by jshi              #+#    #+#             */
/*   Updated: 2016/10/31 16:38:03 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void	round_float_hex(char **str, t_flags *f, int *exp, int i)
{
	if ((*str)[f->prec + 1] == '8' && !(*str)[f->prec + 2])
	{
		if (((*str)[f->prec] <= '9' && (*str)[f->prec] % 2 == 1) ||
				((*str)[f->prec] >= 'a' && (*str)[f->prec] % 2 == 0))
			(*str)[f->prec]++;
	}
	else if ((*str)[f->prec + 1] >= '8')
		(*str)[f->prec]++;
	if ((*str)[f->prec] == 10 + '0')
		(*str)[f->prec] = 'a';
	i = f->prec;
	while (i > 0 && (*str)[i] == 'g')
	{
		(*str)[i--] = '0';
		(*str)[i]++;
		if ((*str)[i] == 10 + '0')
			(*str)[i] = 'a';
	}
	if (i == 0 && (*str)[i] == 'g')
	{
		(*str)[i] = '0';
		prepend_str(str, "1");
		(*exp) += 4;
	}
}

static char	*get_float_hex(long double a, t_flags *f, int *exp)
{
	char	*str;
	int		i;

	if (!(str = (char*)malloc(sizeof(*str) * 20)))
		return (NULL);
	i = -1;
	if (a == 0.0)
		str[++i] = '0';
	while (a > 0.0)
	{
		str[++i] = (int)a + '0';
		if (str[i] >= 10 + '0')
			str[i] = str[i] - 10 - '0' + 'a';
		a -= (int)a;
		a *= 16;
	}
	str[++i] = '\0';
	if (f->prec >= 0 && f->prec < i - 1)
		round_float_hex(&str, f, exp, 0);
	return (str);
}

static int	apply_flags(int exp, t_flags *f, char *inte, char *frac)
{
	if (f->pound == 1 || ft_strlen(frac) > 0 || f->prec > 0)
		append_str(&inte, ".");
	append_char(&frac, '0', f->prec);
	append_str(&inte, frac);
	free(frac);
	(exp < 0) ? append_str(&inte, "p-") : append_str(&inte, "p+");
	frac = ft_itoa_base(exp < 0 ? -exp : exp, 10);
	append_str(&inte, frac);
	free(frac);
	if (f->zero == 1 && f->minus == 0)
		prepend_char(&inte, '0', f->minwid - 3);
	if (f->zero && !(f->minus) && f->sign && !(f->plus) && !(f->space))
		prepend_char(&inte, '0', f->minwid - 2);
	prepend_str(&inte, "0x");
	(f->sign == -1) ? prepend_str(&inte, "-") : 0;
	if (f->sign == 1 && (f->plus == 1 || f->space == 1))
		(f->plus == 1) ? prepend_str(&inte, "+") : prepend_str(&inte, " ");
	(f->minus == 1) ? append_char(&inte, ' ', f->minwid) : 0;
	prepend_char(&inte, ' ', f->minwid);
	(f->conv == 'A') ? ft_strtoupper(inte) : 0;
	exp = ft_strlen(inte);
	ft_putstr(inte);
	free(inte);
	return (exp);
}

int			print_float_hex(va_list *args, t_flags *f)
{
	long double	a;
	int			i;
	int			exp;
	long double min;
	char		*str;

	(f->lenmod == 7) ? (a = va_arg(*args, long double)) : 0;
	(f->lenmod != 7) ? (a = va_arg(*args, double)) : 0;
	(f->lenmod == 7) ? (min = 8.0) : 0;
	(f->lenmod != 7) ? (min = 1.0) : 0;
	f->sign = a < 0 ? -1 : 1;
	if ((i = handle_nan(a, f, 0)) >= 0)
		return (i);
	a *= f->sign;
	exp = 0;
	while (a < min && a != 0.0 && --exp < 0)
		a *= 2;
	while (a >= 2 * min && a != 0.0 && ++exp > -100000)
		a /= 2;
	str = get_float_hex(a, f, &exp);
	i = apply_flags(exp, f, ft_strsub(str, 0, 1),
			ft_strsub(str, 1, (f->prec < 0) ? (ft_strlen(str) - 1) : f->prec));
	free(str);
	return (i);
}
