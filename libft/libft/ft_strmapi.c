/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 21:47:41 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 23:42:21 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	a;

	if (!s || !f)
		return (NULL);
	str = ft_strnew(sizeof(*str) * ft_strlen(s));
	if (!str)
		return (NULL);
	a = 0;
	while (s[a])
	{
		str[a] = f(a, s[a]);
		a++;
	}
	return (str);
}
