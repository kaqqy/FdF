/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:05:07 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 03:51:25 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press_hook(int k, t_env *env)
{
	if (env->key == -1 && !env->cpts)
		env->key = k;
	return (0);
}

int		key_release_hook(int k, t_env *env)
{
	if (env->key == k)
		env->key = -1;
	if (k == 53)
		exit_prog(env, "");
	if (k == 256 || k == 269)
		env->drag = 1 - env->drag;
	else if (k == 261 || k == 262)
		env->hidden = 1 - env->hidden;
	else
		return (0);
	draw_map(env);
	return (0);
}

int		mouse_press_hook(int b, int x, int y, t_env *env)
{
	int		i;
	int		j;
	t_pt	p;

	if (env->cpts || env->key != -1)
		return (0);
	p.x = x;
	p.y = y;
	p.z = 0;
	if (b == 5)
		zoom_all(env, &p, 1.05);
	if (b == 4)
		zoom_all(env, &p, 1.0 / 1.05);
	if (b == 4 || b == 5)
		draw_map(env);
	if (b != 1)
		return (0);
	if (!(env->cpts = (t_pt**)malloc(sizeof(*env->cpts) * env->wid)))
		exit_prog(env, "Error: Malloc failed for variable cpts\n");
	i = -1;
	while (++i < env->wid)
		env->cpts[i] = (t_pt*)malloc(sizeof(**env->cpts) * env->len);
	i = -1;
	while (++i < env->wid)
		if (!env->cpts[i])
			exit_prog(env, "Error: Malloc failed for variable env->cpts[i]\n");
	i = -1;
	while (++i < env->wid && (j = -1))
		while (++j < env->len)
		{
			env->cpts[i][j].x = env->pts[i][j].x;
			env->cpts[i][j].y = env->pts[i][j].y;
			env->cpts[i][j].z = env->pts[i][j].z;
		}
	env->cx_axis.x = env->x_axis.x;
	env->cx_axis.y = env->x_axis.y;
	env->cx_axis.z = env->x_axis.z;
	env->cy_axis.x = env->y_axis.x;
	env->cy_axis.y = env->y_axis.y;
	env->cy_axis.z = env->y_axis.z;
	env->cz_axis.x = env->z_axis.x;
	env->cz_axis.y = env->z_axis.y;
	env->cz_axis.z = env->z_axis.z;
	env->cx = x;
	env->cy = y;
	return (0);
}

int		mouse_release_hook(int b, int x, int y, t_env *env)
{
	int		i;

	if (b != 1 || !env->cpts || env->key != -1)
		return (0);
	i = -1;
	while (++i < env->wid)
		free(env->cpts[i]);
	free(env->cpts);
	env->cpts = NULL;
	if (env->drag == 1)
	{
		env->center.x += x - env->cx;
		env->center.y += y - env->cy;
	}
	return (0);
}

int		motion_hook(int x, int y, t_env *env)
{
	int		i;
	int		j;
	t_pt	axis;

	if (!env->cpts)
		return (0);
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			env->pts[i][j].x = env->cpts[i][j].x;
			env->pts[i][j].y = env->cpts[i][j].y;
			env->pts[i][j].z = env->cpts[i][j].z;
		}
	}
	env->x_axis.x = env->cx_axis.x;
	env->x_axis.y = env->cx_axis.y;
	env->x_axis.z = env->cx_axis.z;
	env->y_axis.x = env->cy_axis.x;
	env->y_axis.y = env->cy_axis.y;
	env->y_axis.z = env->cy_axis.z;
	env->z_axis.x = env->cz_axis.x;
	env->z_axis.y = env->cz_axis.y;
	env->z_axis.z = env->cz_axis.z;
	if (env->drag == 0)
	{
		if (env->cy != y || env->cx != x)
		{
			axis.x = env->cy - y;
			axis.y = x - env->cx;
			axis.z = 0;
			rotate_axis_all(env, &axis, SIGN(axis.x) *
					sqrt(axis.x * axis.x + axis.y * axis.y) / 200);
		}
	}
	else
	{
		i = -1;
		while (++i < env->wid)
		{
			j = -1;
			while (++j < env->len)
			{
				env->pts[i][j].x += x - env->cx;
				env->pts[i][j].y += y - env->cy;
			}
		}
	}
	draw_map(env);
	return (0);
}

int		expose_hook(t_env *env)
{
	draw_map(env);
	return (0);
}

int		loop_hook(t_env *env)
{
	int		i;
	int		j;

	if (env->cpts || env->key == -1)
		return (0);
	if (env->key == 13)
		rotate_x_all(env, M_PI / 90);
	else if (env->key == 7)
		rotate_x_all(env, -M_PI / 90);
	else if (env->key == 2)
		rotate_y_all(env, M_PI / 90);
	else if (env->key == 0)
		rotate_y_all(env, -M_PI / 90);
	else if (env->key == 14)
		rotate_z_all(env, M_PI / 90);
	else if (env->key == 6)
		rotate_z_all(env, -M_PI / 90);
	else if (env->key == 17)
		rotate_axis_all(env, &env->x_axis, M_PI / 90);
	else if (env->key == 11)
		rotate_axis_all(env, &env->x_axis, -M_PI / 90);
	else if (env->key == 4)
		rotate_axis_all(env, &env->y_axis, M_PI / 90);
	else if (env->key == 3)
		rotate_axis_all(env, &env->y_axis, -M_PI / 90);
	else if (env->key == 16)
		rotate_axis_all(env, &env->z_axis, M_PI / 90);
	else if (env->key == 9)
		rotate_axis_all(env, &env->z_axis, -M_PI / 90);
	else if (env->key == 24)
		zoom_all(env, &env->center, 1.02);
	else if (env->key == 27)
		zoom_all(env, &env->center, 1.0 / 1.02);
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			if (env->key == 123)
				env->pts[i][j].x -= 3;
			else if (env->key == 124)
				env->pts[i][j].x += 3;
			else if (env->key == 125)
				env->pts[i][j].y += 3;
			else if (env->key == 126)
				env->pts[i][j].y -= 3;
		}
	}
	if (env->key == 123)
		env->center.x -= 3;
	else if (env->key == 124)
		env->center.x += 3;
	else if (env->key == 125)
		env->center.y += 3;
	else if (env->key == 126)
		env->center.y -= 3;
	draw_map(env);
	return (0);
}
