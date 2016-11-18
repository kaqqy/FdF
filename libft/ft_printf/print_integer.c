/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:06:49 by jshi              #+#    #+#             */
/*   Updated: 2016/10/28 20:24:38 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int			print_decimal(char *str, t_flags *f)
{
	int		ret;

	if (f->num == 0 && f->prec == 0)
		empty_string(&str);
	insert_commas(&str, f->apos);
	prepend_char(&str, '0', f->prec);
	if (f->zero == 1 && f->minus == 0 && f->prec < 0)
	{
		prepend_char(&str, '0', f->minwid - 1);
		if (f->sign == 0 || (f->plus == 0 && f->space == 0 && f->sign == 1))
			prepend_char(&str, '0', f->minwid);
	}
	if (f->sign == -1)
		prepend_str(&str, "-");
	else if (f->plus == 1 && f->sign == 1)
		prepend_str(&str, "+");
	else if (f->space == 1 && f->sign == 1)
		prepend_str(&str, " ");
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	prepend_char(&str, ' ', f->minwid);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int			print_octal(char *str, t_flags *f)
{
	int		ret;

	if (f->num == 0 && f->prec == 0)
		empty_string(&str);
	prepend_char(&str, '0', f->prec);
	if (f->zero == 1 && f->minus == 0 && f->prec < 0)
	{
		if (f->pound == 1 && f->num != 0)
			prepend_char(&str, '0', f->minwid - 1);
		else
			prepend_char(&str, '0', f->minwid);
	}
	if (f->pound == 1 && *str != '0')
		prepend_str(&str, "0");
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	else
		prepend_char(&str, ' ', f->minwid);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int			print_hex(char *str, t_flags *f, int fmt)
{
	int		ret;

	if (f->num == 0 && f->prec == 0)
		empty_string(&str);
	prepend_char(&str, '0', f->prec);
	if (f->zero == 1 && f->minus == 0 && f->prec < 0)
	{
		if ((f->pound == 1 && f->num != 0) || fmt == 1)
			prepend_char(&str, '0', f->minwid - 2);
		else
			prepend_char(&str, '0', f->minwid);
	}
	if ((f->pound == 1 && f->num != 0) || fmt == 1)
		prepend_str(&str, "0x");
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	else
		prepend_char(&str, ' ', f->minwid);
	if (f->conv >= 'A' && f->conv <= 'Z')
		ft_strtoupper(str);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int			print_binary(char *str, t_flags *f)
{
	int		ret;

	if (f->num == 0 && f->prec == 0)
		empty_string(&str);
	prepend_char(&str, '0', f->prec);
	if (f->zero == 1 && f->minus == 0 && f->prec < 0)
	{
		if (f->pound == 1 && f->num != 0)
			prepend_char(&str, '0', f->minwid - 2);
		else
			prepend_char(&str, '0', f->minwid);
	}
	if (f->pound == 1 && f->num != 0)
		prepend_str(&str, "0b");
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	else
		prepend_char(&str, ' ', f->minwid);
	if (f->conv >= 'A' && f->conv <= 'Z')
		ft_strtoupper(str);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int			print_quat(char *str, t_flags *f)
{
	int		ret;

	if (f->num == 0 && f->prec == 0)
		empty_string(&str);
	prepend_char(&str, '0', f->prec);
	if (f->zero == 1 && f->minus == 0 && f->prec < 0)
	{
		if (f->pound == 1 && f->num != 0)
			prepend_char(&str, '0', f->minwid - 2);
		else
			prepend_char(&str, '0', f->minwid);
	}
	if (f->pound == 1 && f->num != 0)
		prepend_str(&str, "0q");
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	else
		prepend_char(&str, ' ', f->minwid);
	if (f->conv >= 'A' && f->conv <= 'Z')
		ft_strtoupper(str);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}
