/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 21:03:03 by jshi              #+#    #+#             */
/*   Updated: 2016/10/31 16:32:50 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int		print_color_text(va_list *args)
{
	char	*str;
	char	*num;
	int		ret;
	int		col;

	col = va_arg(*args, int);
	str = ft_strdup("\e[38;2;");
	num = ft_itoa_base((col >> 16) & 255, 10);
	append_str(&str, num);
	free(num);
	append_str(&str, ";");
	num = ft_itoa_base((col >> 8) & 255, 10);
	append_str(&str, num);
	free(num);
	append_str(&str, ";");
	num = ft_itoa_base(col & 255, 10);
	append_str(&str, num);
	free(num);
	append_str(&str, "m");
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int		print_color_bg(va_list *args)
{
	char	*str;
	char	*num;
	int		ret;
	int		col;

	col = va_arg(*args, int);
	str = ft_strdup("\e[48;2;");
	num = ft_itoa_base((col >> 16) & 255, 10);
	append_str(&str, num);
	free(num);
	append_str(&str, ";");
	num = ft_itoa_base((col >> 8) & 255, 10);
	append_str(&str, num);
	free(num);
	append_str(&str, ";");
	num = ft_itoa_base(col & 255, 10);
	append_str(&str, num);
	free(num);
	append_str(&str, "m");
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (ret);
}

int		print_color_reset(void)
{
	ft_putstr("\e[0m");
	return (4);
}
