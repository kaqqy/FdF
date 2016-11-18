/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 22:11:26 by jshi              #+#    #+#             */
/*   Updated: 2016/11/01 14:43:06 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void	ft_wstrsub(char **str, int len)
{
	int		nlen;
	int		wlen;
	char	*dup;

	if (len < 0 || len >= (int)ft_strlen(*str))
		return ;
	nlen = 0;
	while ((*str)[nlen] && nlen <= len)
	{
		wlen = 1;
		if (((unsigned char)(*str)[nlen] & 240) == 240)
			wlen = 4;
		else if (((unsigned char)(*str)[nlen] & 224) == 224)
			wlen = 3;
		else if (((unsigned char)(*str)[nlen] & 192) == 192)
			wlen = 2;
		if (nlen + wlen > len)
			break ;
		nlen += wlen;
	}
	(*str)[nlen] = '\0';
	dup = ft_strdup(*str);
	free(*str);
	*str = dup;
}

static int	apply_flags(char *str, t_flags *f)
{
	int		ret;

	ft_wstrsub(&str, f->prec);
	if (f->minus == 1)
		append_char(&str, ' ', f->minwid);
	else if (f->zero == 1)
		prepend_char(&str, '0', f->minwid);
	else
		prepend_char(&str, ' ', f->minwid);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int			print_string(va_list *args, t_flags *f)
{
	char	*str;
	char	*tmp;
	wchar_t	*wstr;

	if (f->lenmod == 3 || f->conv == 'S')
	{
		if (!(wstr = va_arg(*args, wchar_t*)))
			return (apply_flags(ft_strdup("(null)"), f));
		if (!(str = (char*)malloc(sizeof(*str))))
			return (0);
		str[0] = '\0';
		while (*wstr)
		{
			tmp = wchar_to_str(wstr[0]);
			append_str(&str, tmp);
			free(tmp);
			wstr++;
		}
	}
	else
	{
		str = va_arg(*args, char*);
		return (apply_flags(str ? ft_strdup(str) : ft_strdup("(null)"), f));
	}
	return (apply_flags(str, f));
}

int			print_nonprint(va_list *args, t_flags *f)
{
	char	*str;
	int		i;

	str = va_arg(*args, char*);
	str = str ? ft_strdup(str) : ft_strdup("(null)");
	i = -1;
	while (str[++i])
	{
		if (str[i] < 32 || str[i] > 126)
			str[i] = '.';
	}
	return (apply_flags(str, f));
}
