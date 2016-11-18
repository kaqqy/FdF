/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:27:27 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 14:30:57 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*next;
	t_list	*tmp;
	t_list	*f_ret;

	if (!lst || !f)
		return (NULL);
	next = ft_lstmap(lst->next, f);
	if (!next && lst->next)
		return (NULL);
	f_ret = f(lst);
	cur = ft_lstnew(f_ret->content, f_ret->content_size);
	if (!cur)
	{
		while (next)
		{
			tmp = next->next;
			free(next->content);
			free(next);
			next = tmp;
		}
		return (NULL);
	}
	cur->next = next;
	return (cur);
}
