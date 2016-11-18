/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:45:38 by jshi              #+#    #+#             */
/*   Updated: 2016/11/10 22:37:24 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1);
	dup = ft_strnew(sizeof(*dup) * len);
	if (!dup)
		return (dup);
	while (len--)
		dup[len] = s1[len];
	return (dup);
}
