/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 21:44:53 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 23:39:52 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	a;

	if (!s || !f)
		return (NULL);
	str = ft_strnew(sizeof(*str) * ft_strlen(s));
	if (!str)
		return (NULL);
	a = 0;
	while (s[a])
	{
		str[a] = f(s[a]);
		a++;
	}
	return (str);
}
