/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:36:08 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 20:00:38 by jshi             ###   ########.fr       */
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

/*
** double vars[6];
** vars[0] = delta;
** vars[1] = error;
** vars[2] = signx;
** vars[3] = signy;
** vars[4] = count;
** vars[5] = total;
*/

static void	draw_line2(t_env *env, t_pt *p1, t_pt *p2, int swap)
{
	double	vars[6];

	if (swap)
		vars[0] = ABS((p2->y - p1->y) / (p2->x - p1->x));
	else
		vars[0] = ABS((p2->x - p1->x) / (p2->y - p1->y));
	vars[1] = 0.0;
	vars[2] = SIGN(p2->x - p1->x);
	vars[3] = SIGN(p2->y - p1->y);
	vars[4] = 0.0;
	vars[5] = swap ? (ABS(p2->x - p1->x)) : (ABS(p2->y - p1->y));
	while (swap ? (p1->x != p2->x) : (p1->y != p2->y))
	{
		swap ? (p1->x += vars[2]) : (p1->y += vars[3]);
		vars[1] += vars[0];
		vars[4] += 1.0;
		if (vars[1] >= 1.0)
		{
			vars[1] -= 1.0;
			swap ? (p1->y += vars[3]) : (p1->x += vars[2]);
		}
		draw_point(env, p1->x, p1->y, get_color(env, (vars[4] / vars[5]) * p2->w
					+ (1 - (vars[4] / vars[5])) * p1->w));
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
