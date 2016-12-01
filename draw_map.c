/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 02:08:29 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 00:47:03 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_point(t_env *env, int x, int y, int color)
{
	int		ind;

	if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_WID)
		return ;
	ind = env->sl * y + env->bpp * x;
	env->data[ind + (env->endian ? (env->bpp - 1) : 0)] = color % 256;
	env->data[ind + (env->endian ? (env->bpp - 2) : 1)] = (color >> 8) % 256;
	env->data[ind + (env->endian ? (env->bpp - 3) : 2)] = (color >> 16) % 256;
}

static int	get_color(t_env *env, double frac)
{
	double	red;
	double	green;
	double	blue;
	int		i;

	if (env->num_colors == 1)
		return (env->colors[0]);
	frac = frac * (env->num_colors - 1);
	i = floor(frac);
	frac -= i;
	if (i >= env->num_colors - 1)
		return (env->colors[env->num_colors - 1]);
	if (i < 0)
		return (env->colors[0]);
	red = ((env->colors[i + 1] >> 16) % 256) * frac +
		((env->colors[i] >> 16) % 256) * (1 - frac);
	green = ((env->colors[i + 1] >> 8) % 256) * frac +
		((env->colors[i] >> 8) % 256) * (1 - frac);
	blue = (env->colors[i + 1] % 256) * frac +
		(env->colors[i] % 256) * (1 - frac);
	return (((int)red << 16) + ((int)green << 8) + blue);
}

static void	draw_line2(t_env *env, t_pt *p1, t_pt *p2, int swap)
{
	double	delta;
	double	error;
	double	signx;
	double	signy;
	double	count;
	double	total;

	if (swap)
		delta = ABS((p2->y - p1->y) / (p2->x - p1->x));
	else
		delta = ABS((p2->x - p1->x) / (p2->y - p1->y));
	error = 0.0;
	signx = SIGN(p2->x - p1->x);
	signy = SIGN(p2->y - p1->y);
	count = 0.0;
	total = swap ? (ABS(p2->x - p1->x)) : (ABS(p2->y - p1->y));
	while (swap ? (p1->x != p2->x) : (p1->y != p2->y))
	{
		swap ? (p1->x += signx) : (p1->y += signy);
		error += delta;
		count += 1.0;
		if (error >= 1.0)
		{
			error -= 1.0;
			swap ? (p1->y += signy) : (p1->x += signx);
		}
		draw_point(env, p1->x, p1->y, get_color(env, (count / total) * p2->w +
					(1 - (count / total)) * p1->w));
	}
}

void		draw_line(t_env *env, t_pt *pt1, t_pt *pt2)
{
	t_pt	p1;
	t_pt	p2;
	int		swap;

	if ((pt1->x < 0 && pt2->x < 0) || (pt1->x > WIN_LEN && pt2->x > WIN_LEN) ||
		(pt1->y < 0 && pt2->y < 0) || (pt1->y > WIN_WID && pt2->y > WIN_WID))
		return ;
	p1.x = floor(pt1->x);
	p1.y = floor(pt1->y);
	p1.w = pt1->w;
	p2.x = floor(pt2->x);
	p2.y = floor(pt2->y);
	p2.w = pt2->w;
	draw_point(env, p1.x, p1.y, get_color(env, pt1->w));
	if (p1.x == p2.x && p1.y == p2.y)
		return ;
	swap = 0;
	if (ABS(p2.x - p1.x) > ABS(p2.y - p1.y))
		swap = 1;
	draw_line2(env, &p1, &p2, swap);
}

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

void		draw_map(t_env *env)
{
	int		i;
	int		j;
	int		offset_w;
	int		offset_l;


	mlx_clear_window(env->mlx, env->win);
	clear_image(env);
	//find which point is furthest back
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
	i = (1 - offset_w) * (env->wid - 2);
	while (i != offset_w * (env->wid - 2) + 2 * offset_w - 1)
	{
		j = (1 - offset_l) * (env->len - 2);
		while (j != offset_l * (env->len - 2) + 2 * offset_l - 1)
		{
			if (env->hidden)
			{
				draw_triangle(env,
						&env->pts[i + 1 - offset_w][j + 1 - offset_l],
						&env->pts[i + 1 - offset_w][j + offset_l],
						&env->pts[i + offset_w][j + 1 - offset_l]);
				draw_triangle(env, &env->pts[i + offset_w][j + offset_l],
						&env->pts[i + 1 - offset_w][j + offset_l],
						&env->pts[i + offset_w][j + 1 - offset_l]);
			}
			draw_line(env, &env->pts[i + 1 - offset_w][j + 1 - offset_l],
					&env->pts[i + 1 - offset_w][j + offset_l]);
			draw_line(env, &env->pts[i + 1 - offset_w][j + 1 - offset_l],
					&env->pts[i + offset_w][j + 1 - offset_l]);
			j += 2 * offset_l - 1;
		}
		i += 2 * offset_w - 1;
	}
	i = 0;
	while (++i < env->wid)
		draw_line(env, &env->pts[i][offset_l * (env->len - 1)],
				&env->pts[i - 1][offset_l * (env->len - 1)]);
	i = 0;
	while (++i < env->len)
		draw_line(env, &env->pts[offset_w * (env->wid - 1)][i],
				&env->pts[offset_w * (env->wid - 1)][i - 1]);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
