/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 21:03:08 by jshi              #+#    #+#             */
/*   Updated: 2016/09/23 01:38:26 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while (s1[a] && s1[a] == s2[a] && a < n)
		a++;
	if (a == n)
		return (0);
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
