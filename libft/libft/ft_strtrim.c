/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 00:08:05 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 23:42:59 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	a;
	size_t	b;
	char	*str;

	if (!s)
		return (NULL);
	a = 0;
	while (s[a] == ' ' || s[a] == '\n' || s[a] == '\t')
		a++;
	b = ft_strlen(s);
	while (b && (s[b - 1] == ' ' || s[b - 1] == '\n' || s[b - 1] == '\t'))
		b--;
	if (a > b)
		a = b;
	str = ft_strnew(sizeof(*str) * (b - a));
	if (!str)
		return (NULL);
	while (b - a)
	{
		b--;
		str[b - a] = s[b];
	}
	return (str);
}
