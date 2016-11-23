/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 20:22:09 by jshi              #+#    #+#             */
/*   Updated: 2016/11/22 03:41:00 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_prog(t_env *env, char *msg)
{
	int		i;

	if (!env)
		exit(0);
	if (env->pts)
	{
		i = -1;
		while (++i < env->wid)
			free(env->pts[i]);
	}
	free(env->pts);
	free(env->mlx);
	free(env->win);
	get_next_line(0, NULL);
	ft_putstr_fd(msg, 2);
	exit(0);
}
