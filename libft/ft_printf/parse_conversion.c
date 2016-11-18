/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 21:44:08 by jshi              #+#    #+#             */
/*   Updated: 2016/10/28 20:44:32 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_arg(char **pos, va_list *args, t_flags *f)
{
	int		i;
	int		argnum;

	i = 0;
	argnum = 0;
	while ((*pos)[i] >= '0' && (*pos)[i] <= '9')
	{
		argnum = argnum * 10 + (*pos)[i] - '0';
		i++;
	}
	if ((*pos)[i] != '$')
		return ;
	va_copy(*args, f->arg_start);
	while (--argnum)
		va_arg(*args, int);
	(*pos) += i + 1;
}

void	set_flags(char **pos, t_flags *f)
{
	f->pound = 0;
	f->zero = 0;
	f->minus = 0;
	f->plus = 0;
	f->space = 0;
	f->apos = 0;
	while (**pos == '#' || **pos == '0' || **pos == '-' || **pos == '+' ||
			**pos == ' ' || **pos == '\'')
	{
		if (**pos == '#')
			f->pound = 1;
		else if (**pos == '0')
			f->zero = 1;
		else if (**pos == '-')
			f->minus = 1;
		else if (**pos == '+')
			f->plus = 1;
		else if (**pos == ' ')
			f->space = 1;
		else if (**pos == '\'')
			f->apos = 1;
		(*pos)++;
	}
}

void	set_minwid(char **pos, va_list *args, t_flags *f)
{
	f->minwid = 0;
	while ((**pos >= '0' && **pos <= '9') || **pos == '*')
	{
		if (**pos == '*')
		{
			f->minwid = va_arg(*args, int);
			if (f->minwid < 0)
			{
				f->minwid *= -1;
				f->minus = 1;
			}
		}
		else if ((*pos)[-1] >= '0' && (*pos)[-1] <= '9')
			f->minwid = f->minwid * 10 + **pos - '0';
		else
			f->minwid = **pos - '0';
		(*pos)++;
	}
}

void	set_prec(char **pos, va_list *args, t_flags *f)
{
	f->prec = -6;
	if (**pos != '.')
		return ;
	f->prec = 0;
	(*pos)++;
	if (**pos == '*')
		f->prec = va_arg(*args, int);
	else
	{
		while (**pos >= '0' && **pos <= '9')
		{
			f->prec = f->prec * 10 + **pos - '0';
			(*pos)++;
		}
	}
	while ((**pos >= '0' && **pos <= '9') || **pos == '*')
		(*pos)++;
}

void	set_lenmod(char **pos, t_flags *f)
{
	f->lenmod = 0;
	if ((*pos)[0] == 'h' && (*pos)[1] == 'h')
		f->lenmod = 1;
	else if ((*pos)[0] == 'h')
		f->lenmod = 2;
	else if ((*pos)[0] == 'l' && (*pos)[1] != 'l')
		f->lenmod = 3;
	else if ((*pos)[0] == 'l')
		f->lenmod = 4;
	else if ((*pos)[0] == 'j')
		f->lenmod = 5;
	else if ((*pos)[0] == 'z')
		f->lenmod = 6;
	else if ((*pos)[0] == 'L')
		f->lenmod = 7;
	else if ((*pos)[0] == 't')
		f->lenmod = 8;
	if (f->lenmod == 1 || f->lenmod == 4)
		(*pos) += 2;
	else if (f->lenmod > 0)
		(*pos)++;
}
