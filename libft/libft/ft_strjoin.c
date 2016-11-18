/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 23:28:27 by jshi              #+#    #+#             */
/*   Updated: 2016/10/06 00:04:24 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	int		a;
	int		b;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	cat = ft_strnew(sizeof(*cat) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!cat)
		return (NULL);
	a = -1;
	b = -1;
	while (s1[++a])
		cat[a] = s1[a];
	while (s2[++b])
		cat[a + b] = s2[b];
	return (cat);
}
