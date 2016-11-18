/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:20:03 by jshi              #+#    #+#             */
/*   Updated: 2016/09/28 15:02:02 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_wc_c(char const *s, char c)
{
	int		a;
	int		wc;

	a = 0;
	wc = 0;
	while (s[a])
	{
		while (s[a] && s[a] != c)
			a++;
		while (s[a] == c)
			a++;
		wc++;
	}
	if (s[0] == c)
		wc--;
	return (wc);
}

static void		ft_freeall(char **strarr, int len)
{
	while (len--)
		free(strarr[len]);
	free(strarr);
}

static int		ft_fillarr(char **strarr, char const *s, char c, int a)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (s[a] && ++i >= 0)
	{
		j = 0;
		while (s[a + j] && s[a + j] != c)
			j++;
		strarr[i] = ft_strnew(sizeof(**strarr) * j);
		if (!strarr[i])
		{
			ft_freeall(strarr, i);
			return (0);
		}
		k = j;
		while (j--)
			strarr[i][j] = s[a + j];
		a += k;
		while (s[a] == c)
			a++;
	}
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**strarr;
	int		numstr;
	int		a;

	if (!s)
		return (NULL);
	numstr = ft_wc_c(s, c);
	strarr = (char**)malloc(sizeof(*strarr) * (numstr + 1));
	if (!strarr)
		return (NULL);
	strarr[numstr] = NULL;
	a = 0;
	while (s[a] == c)
		a++;
	if (ft_fillarr(strarr, s, c, a))
		return (strarr);
	return (NULL);
}
