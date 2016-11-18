/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:11:12 by jshi              #+#    #+#             */
/*   Updated: 2016/09/26 23:47:23 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlink;

	newlink = (t_list*)malloc(sizeof(*newlink));
	if (!newlink)
		return (NULL);
	newlink->next = NULL;
	if (!content)
	{
		newlink->content = NULL;
		newlink->content_size = 0;
		return (newlink);
	}
	newlink->content = ft_memalloc(content_size);
	if (!newlink->content)
	{
		free(newlink);
		return (NULL);
	}
	newlink->content_size = content_size;
	ft_memcpy(newlink->content, content, content_size);
	return (newlink);
}
