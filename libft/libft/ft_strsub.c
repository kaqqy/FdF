/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:24:26 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 23:40:03 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_strnew(sizeof(*sub) * len);
	if (!sub || !s)
		return (NULL);
	while (len--)
		sub[len] = s[start + len];
	return (sub);
}
