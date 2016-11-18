/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:17:48 by jshi              #+#    #+#             */
/*   Updated: 2016/09/23 22:30:56 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cur;
	t_list	*next;

	if (!alst || !*alst || !del)
		return ;
	cur = *alst;
	next = cur->next;
	while (next)
	{
		del(cur->content, cur->content_size);
		free(cur);
		cur = next;
		next = next->next;
	}
	del(cur->content, cur->content_size);
	free(cur);
	*alst = NULL;
}
