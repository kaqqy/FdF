/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_pts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 23:09:38 by jshi              #+#    #+#             */
/*   Updated: 2016/11/24 02:00:45 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_center(t_env *env)
{
	int		i;
	int		j;

	env->center.x = 0;
	env->center.y = 0;
	env->center.z = 0;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			env->center.x += env->pts[i][j].x;
			env->center.y += env->pts[i][j].y;
			env->center.z += env->pts[i][j].z;
		}
	}
	env->center.x /= env->wid * env->len;
	env->center.y /= env->wid * env->len;
	env->center.z /= env->wid * env->len;
}

static void	transform_map(t_env *env)
{
	int		i;
	int		j;
	double	scale;

	scale = MIN((double)WIN_WID / (env->wid - 1),
			(double)WIN_LEN / (env->len - 1)) / 2;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			env->pts[i][j].x = (env->pts[i][j].x - env->center.x) * scale +
				WIN_LEN / 2;
			env->pts[i][j].y = (env->pts[i][j].y - env->center.y) * scale +
				WIN_WID / 2;
			env->pts[i][j].z = (env->pts[i][j].z - env->center.z) * scale;
		}
	}
	env->center.x = WIN_LEN / 2;
	env->center.y = WIN_WID / 2;
	env->center.z = 0;
}

void		config_pts(t_env *env)
{
	set_center(env);
	transform_map(env);
}
