/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 02:08:29 by jshi              #+#    #+#             */
/*   Updated: 2016/11/24 21:40:48 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_point(t_env *env, int x, int y, int color)
{
	int		ind;

	if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_WID)
		return ;
	ind = env->sl * y + env->bpp * x;
	env->data[ind + (env->endian ? (env->bpp - 1) : 0)] = color % 256;
	env->data[ind + (env->endian ? (env->bpp - 2) : 1)] = (color >> 8) % 256;
	env->data[ind + (env->endian ? (env->bpp - 3) : 2)] = (color >> 16) % 256;
}

static void	draw_line2(t_env *env, t_pt *p1, t_pt *p2, int swap)
{
	double	delta;
	double	error;
	double	signx;
	double	signy;

	if (swap)
		delta = ABS((p2->y - p1->y) / (p2->x - p1->x));
	else
		delta = ABS((p2->x - p1->x) / (p2->y - p1->y));
	error = 0.0;
	signx = SIGN(p2->x - p1->x);
	signy = SIGN(p2->y - p1->y);
	while (swap ? (p1->x != p2->x) : (p1->y != p2->y))
	{
		swap ? (p1->x += signx) : (p1->y += signy);
		error += delta;
		if (error >= 1.0)
		{
			error -= 1.0;
			swap ? (p1->y += signy) : (p1->x += signx);
		}
		draw_point(env, p1->x, p1->y, 0xffffff);
	}
}

static void	draw_line(t_env *env, t_pt *pt1, t_pt *pt2)
{
	t_pt	p1;
	t_pt	p2;
	int		swap;

	if ((pt1->x < 0 && pt2->x < 0) || (pt1->x > WIN_LEN && pt2->x > WIN_LEN) ||
		(pt1->y < 0 && pt2->y < 0) || (pt1->y > WIN_WID && pt2->y > WIN_WID))
		return ;
	p1.x = floor(pt1->x);
	p1.y = floor(pt1->y);
	p2.x = floor(pt2->x);
	p2.y = floor(pt2->y);
	draw_point(env, p1.x, p1.y, 0xffffff);
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

	mlx_clear_window(env->mlx, env->win);
	clear_image(env);
	i = -1;
	while (++i < env->wid)
	{
		j = 0;
		while (++j < env->len)
			draw_line(env, &env->pts[i][j - 1], &env->pts[i][j]);
	}
	i = 0;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
			draw_line(env, &env->pts[i - 1][j], &env->pts[i][j]);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
