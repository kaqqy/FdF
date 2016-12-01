/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 23:08:27 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 03:41:48 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x_all(t_env *env, double angle)
{
	int		i;
	int		j;
	t_pt	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
			rotate_x(&env->pts[i][j], &env->center, angle);
	}
	rotate_x(&env->x_axis, &origin, angle);
	rotate_x(&env->y_axis, &origin, angle);
	rotate_x(&env->z_axis, &origin, angle);
}

void	rotate_y_all(t_env *env, double angle)
{
	int		i;
	int		j;
	t_pt	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
			rotate_y(&env->pts[i][j], &env->center, angle);
	}
	rotate_y(&env->x_axis, &origin, angle);
	rotate_y(&env->y_axis, &origin, angle);
	rotate_y(&env->z_axis, &origin, angle);
}

void	rotate_z_all(t_env *env, double angle)
{
	int		i;
	int		j;
	t_pt	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
			rotate_z(&env->pts[i][j], &env->center, angle);
	}
	rotate_z(&env->x_axis, &origin, angle);
	rotate_z(&env->y_axis, &origin, angle);
	rotate_z(&env->z_axis, &origin, angle);
}

void	rotate_axis_all(t_env *env, t_pt *axis, double angle)
{
	int		i;
	int		j;
	t_pt	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
			rotate_axis(&env->pts[i][j], &env->center, axis, angle);
	}
	if (axis != &env->x_axis)
		rotate_axis(&env->x_axis, &origin, axis, angle);
	if (axis != &env->y_axis)
		rotate_axis(&env->y_axis, &origin, axis, angle);
	if (axis != &env->z_axis)
		rotate_axis(&env->z_axis, &origin, axis, angle);
}

void	zoom_all(t_env *env, t_pt *center, double scale)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
			zoom(&env->pts[i][j], center, scale);
	}
	zoom(&env->center, center, scale);
}
