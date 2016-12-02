/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 02:08:29 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 19:54:49 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_image(t_env *env)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < WIN_WID)
	{
		j = -1;
		while (++j < WIN_LEN)
		{
			k = -1;
			while (++k < env->bpp)
				env->data[env->sl * i + env->bpp * j + k] = 0;
		}
	}
}

static void	draw_lines(t_env *env, int ow, int ol, int i)
{
	int		j;

	i = (1 - ow) * (env->wid - 2);
	while (i != ow * (env->wid - 2) + 2 * ow - 1)
	{
		j = (1 - ol) * (env->len - 2);
		while (j != ol * (env->len - 2) + 2 * ol - 1)
		{
			if (env->hidden)
			{
				draw_triangle(env, &env->pts[i + 1 - ow][j + 1 - ol],
						&env->pts[i + 1 - ow][j + ol],
						&env->pts[i + ow][j + 1 - ol]);
				draw_triangle(env, &env->pts[i + ow][j + ol],
						&env->pts[i + 1 - ow][j + ol],
						&env->pts[i + ow][j + 1 - ol]);
			}
			draw_line(env, &env->pts[i + 1 - ow][j + 1 - ol],
					&env->pts[i + 1 - ow][j + ol]);
			draw_line(env, &env->pts[i + 1 - ow][j + 1 - ol],
					&env->pts[i + ow][j + 1 - ol]);
			j += 2 * ol - 1;
		}
		i += 2 * ow - 1;
	}
}

static void	draw_lines2(t_env *env, int offset_w, int offset_l)
{
	int		i;

	i = 0;
	while (++i < env->wid)
		draw_line(env, &env->pts[i][offset_l * (env->len - 1)],
				&env->pts[i - 1][offset_l * (env->len - 1)]);
	i = 0;
	while (++i < env->len)
		draw_line(env, &env->pts[offset_w * (env->wid - 1)][i],
				&env->pts[offset_w * (env->wid - 1)][i - 1]);
}

void		draw_map(t_env *env)
{
	int		offset_w;
	int		offset_l;

	mlx_clear_window(env->mlx, env->win);
	clear_image(env);
	offset_w = 1;
	offset_l = 1;
	if (env->x_axis.z < 0.0 && env->y_axis.z >= 0.0)
	{
		offset_w = 1;
		offset_l = 0;
	}
	else if (env->x_axis.z < 0.0 && env->y_axis.z < 0.0)
	{
		offset_w = 0;
		offset_l = 0;
	}
	else if (env->x_axis.z >= 0.0 && env->y_axis.z < 0.0)
	{
		offset_w = 0;
		offset_l = 1;
	}
	draw_lines(env, offset_w, offset_l, 0);
	draw_lines2(env, offset_w, offset_l);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
