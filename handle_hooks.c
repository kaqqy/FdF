/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:05:07 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 19:41:25 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	mouse_press_hook2(t_env *env, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->wid && (j = -1))
	{
		while (++j < env->len)
		{
			env->cpts[i][j].x = env->pts[i][j].x;
			env->cpts[i][j].y = env->pts[i][j].y;
			env->cpts[i][j].z = env->pts[i][j].z;
		}
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
}

int			mouse_press_hook(int b, int x, int y, t_env *env)
{
	int		i;
	t_pt	p;

	if (env->cpts || env->key != -1)
		return (0);
	p.x = x;
	p.y = y;
	p.z = 0;
	(b == 5) ? zoom_all(env, &p, 1.05) : 0;
	(b == 4) ? zoom_all(env, &p, 1.0 / 1.05) : 0;
	(b == 4 || b == 5) ? draw_map(env) : 0;
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
	mouse_press_hook2(env, x, y);
	return (0);
}

int			mouse_release_hook(int b, int x, int y, t_env *env)
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

static void	motion_hook2(t_env *env, int x, int y)
{
	int		i;
	int		j;
	t_pt	axis;

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
		while (++i < env->wid && (j = -1))
			while (++j < env->len)
			{
				env->pts[i][j].x += x - env->cx;
				env->pts[i][j].y += y - env->cy;
			}
	}
}

int			motion_hook(int x, int y, t_env *env)
{
	int		i;
	int		j;

	if (!env->cpts)
		return (0);
	i = -1;
	while (++i < env->wid && (j = -1))
		while (++j < env->len)
		{
			env->pts[i][j].x = env->cpts[i][j].x;
			env->pts[i][j].y = env->cpts[i][j].y;
			env->pts[i][j].z = env->cpts[i][j].z;
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
	motion_hook2(env, x, y);
	draw_map(env);
	return (0);
}
