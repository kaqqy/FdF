/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_pts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 23:09:38 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 03:14:44 by jshi             ###   ########.fr       */
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

static void	scale_height(t_env *env)
{
	int		i;
	int		j;
	double	min;
	double	max;

	min = env->pts[0][0].z;
	max = env->pts[0][0].z;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			if (env->pts[i][j].z < min)
				min = env->pts[i][j].z;
			if (env->pts[i][j].z > max)
				max = env->pts[i][j].z;
		}
	}
	if (max - min > 100.0 && (i = -1))
		while (++i < env->wid && (j = -1))
			while (++j < env->len)
				env->pts[i][j].z *= 100.0 / (max - min);
}

static void	set_loc(t_env *env)
{
	int		i;
	int		j;
	double	min;
	double	max;

	min = env->pts[0][0].z;
	max = env->pts[0][0].z;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			if (env->pts[i][j].z < min)
				min = env->pts[i][j].z;
			if (env->pts[i][j].z > max)
				max = env->pts[i][j].z;
		}
	}
	i = -1;
	while (++i < env->wid && (j = -1))
		while (++j < env->len)
			env->pts[i][j].w = (max == min) ? 0.0 :
				(env->pts[i][j].z - min) / (max - min);
}

void		config_pts(t_env *env)
{
	set_center(env);
	transform_map(env);
	scale_height(env);
	set_loc(env);
	env->x_axis.x = 1;
	env->x_axis.y = 0;
	env->x_axis.z = 0;
	env->y_axis.x = 0;
	env->y_axis.y = 1;
	env->y_axis.z = 0;
	env->z_axis.x = 0;
	env->z_axis.y = 0;
	env->z_axis.z = 1;
	rotate_z_all(env, M_PI / 4);
	rotate_x_all(env, atan(sqrt(2)));
}
