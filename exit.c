/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 20:22:09 by jshi              #+#    #+#             */
/*   Updated: 2016/11/24 21:36:30 by jshi             ###   ########.fr       */
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
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	free(env->mlx);
	get_next_line(0, NULL);
	ft_putstr_fd(msg, 2);
	exit(1);
}
