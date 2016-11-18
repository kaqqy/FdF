/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 19:05:40 by jshi              #+#    #+#             */
/*   Updated: 2016/10/31 16:27:47 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "ft_printf.h"

int		store_numchar(va_list *args, t_flags *f)
{
	int		*loc;

	loc = va_arg(*args, int*);
	if (f->lenmod == 1)
		*(signed char*)loc = f->num_char;
	else if (f->lenmod == 2)
		*(short*)loc = f->num_char;
	else if (f->lenmod == 3)
		*(long*)loc = f->num_char;
	else if (f->lenmod == 4)
		*(long long*)loc = f->num_char;
	else if (f->lenmod == 5)
		*(intmax_t*)loc = f->num_char;
	else if (f->lenmod == 6)
		*(ssize_t*)loc = f->num_char;
	else if (f->lenmod == 8)
		*(ptrdiff_t*)loc = f->num_char;
	else
		*loc = f->num_char;
	return (0);
}
