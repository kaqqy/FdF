/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:13:17 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 19:33:09 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_press_hook(int k, t_env *env)
{
	if (env->key == -1 && !env->cpts)
		env->key = k;
	return (0);
}

int			key_release_hook(int k, t_env *env)
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

static void	loop_hook2(t_env *env, int x, int y)
{
	int		i;
	int		j;

	if (env->key == 123)
		x = -3;
	else if (env->key == 124)
		x = 3;
	else if (env->key == 125)
		y = 3;
	else if (env->key == 126)
		y = -3;
	env->center.x += x;
	env->center.y += y;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			env->pts[i][j].x += x;
			env->pts[i][j].y += y;
		}
	}
}

int			loop_hook(t_env *env)
{
	if (env->cpts || env->key == -1)
		return (0);
	(env->key == 13) ? rotate_x_all(env, M_PI / 90) : 0;
	(env->key == 7) ? rotate_x_all(env, -M_PI / 90) : 0;
	(env->key == 2) ? rotate_y_all(env, M_PI / 90) : 0;
	(env->key == 0) ? rotate_y_all(env, -M_PI / 90) : 0;
	(env->key == 14) ? rotate_z_all(env, M_PI / 90) : 0;
	(env->key == 6) ? rotate_z_all(env, -M_PI / 90) : 0;
	(env->key == 17) ? rotate_axis_all(env, &env->x_axis, M_PI / 90) : 0;
	(env->key == 11) ? rotate_axis_all(env, &env->x_axis, -M_PI / 90) : 0;
	(env->key == 4) ? rotate_axis_all(env, &env->y_axis, M_PI / 90) : 0;
	(env->key == 3) ? rotate_axis_all(env, &env->y_axis, -M_PI / 90) : 0;
	(env->key == 16) ? rotate_axis_all(env, &env->z_axis, M_PI / 90) : 0;
	(env->key == 9) ? rotate_axis_all(env, &env->z_axis, -M_PI / 90) : 0;
	(env->key == 24) ? zoom_all(env, &env->center, 1.02) : 0;
	(env->key == 27) ? zoom_all(env, &env->center, 1.0 / 1.02) : 0;
	if (env->key > 122 && env->key < 127)
		loop_hook2(env, 0, 0);
	draw_map(env);
	return (0);
}

int			expose_hook(t_env *env)
{
	draw_map(env);
	return (0);
}
