/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 11:55:38 by jshi              #+#    #+#             */
/*   Updated: 2016/11/14 21:08:23 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void		free_all_bufs(t_bufs *files)
{
	t_bufs	*tmp;

	while (files)
	{
		tmp = files->next;
		free(files->str);
		free(files);
		files = tmp;
	}
}

static t_bufs	*create_buf(t_bufs **files, const int fd)
{
	t_bufs	*buf;

	buf = (t_bufs*)malloc(sizeof(*buf));
	if (!buf)
		return (NULL);
	buf->str = ft_strnew(BUFF_SIZE);
	if (!(buf->str))
	{
		free(buf);
		return (NULL);
	}
	buf->fd = fd;
	buf->i = 0;
	buf->next = *files;
	*files = buf;
	return (buf);
}

static int		create_line(const int fd, char **line, t_bufs *buf)
{
	char	*search;
	char	*join;
	int		size;

	while (!(search = ft_strchr((const char*)(buf->str + buf->i), 10)))
	{
		join = ft_strjoin(*line, buf->str + buf->i);
		free(*line);
		*line = join;
		size = read(fd, buf->str, BUFF_SIZE);
		if (size < 0)
			return (-1);
		(buf->str)[size] = '\0';
		buf->i = 0;
		if (!size)
			return (ft_strlen(*line) > 0 ? 1 : 0);
	}
	*search = '\0';
	join = ft_strjoin(*line, buf->str + buf->i);
	free(*line);
	*line = join;
	buf->i = (int)(search - buf->str + 1);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_bufs	*files = NULL;
	t_bufs			*buf;

	if (!line)
	{
		free_all_bufs(files);
		files = NULL;
		return (-1);
	}
	*line = ft_strnew(0);
	buf = files;
	while (buf)
	{
		if (buf->fd == fd)
			break ;
		buf = buf->next;
	}
	if (!buf)
		buf = create_buf(&files, fd);
	if (!buf)
		return (-1);
	return (create_line(fd, line, buf));
}
