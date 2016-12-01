/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 21:49:50 by jshi              #+#    #+#             */
/*   Updated: 2016/11/30 20:30:02 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_points(t_env *env, double x, double y1, double y2)
{
	y1 = floor(y1);
	y2 = floor(y2);
	while (y1 <= y2)
	{
		draw_point(env, x, y1, 0);
		y1 += 1.0;
	}
}

static void	fill_triangle(t_env *env, t_pt *p1, t_pt *p2, t_pt *p)
{
	double	x;
	double	s1;
	double	s2;
	double	lower;
	double	upper;

	x = p->x;
	s1 = (p1->y - p->y) / (p1->x - p->x) * SIGN(p1->x - p->x);
	s2 = (p2->y - p->y) / (p2->x - p->x) * SIGN(p1->x - p->x);
	lower = p->y;
	upper = p->y;
	while (x != p1->x)
	{
		fill_points(env, x, lower, upper);
		x += SIGN(p1->x - p->x);
		lower += s1;
		upper += s2;
	}
	fill_points(env, x, lower, upper);
}

static void	split_triangle(t_env *env, t_pt *p, t_pt *p1, t_pt *p2)
{
	t_pt	p3;

	p3.x = p->x;
	p3.y = (p2->y - p1->y) / (p2->x - p1->x) * (p3.x - p1->x) + p1->y;
	if (p3.y > p->y)
	{
		fill_triangle(env, p, &p3, p1);
		fill_triangle(env, p, &p3, p2);
	}
	else
	{
		fill_triangle(env, &p3, p, p1);
		fill_triangle(env, &p3, p, p2);
	}
}

void		draw_triangle(t_env *env, t_pt *p1, t_pt *p2, t_pt *p3)
{
	t_pt	p4;
	t_pt	p5;
	t_pt	p6;

	p4.x = floor(p1->x);
	p4.y = floor(p1->y);
	p5.x = floor(p2->x);
	p5.y = floor(p2->y);
	p6.x = floor(p3->x);
	p6.y = floor(p3->y);
	if ((p4.x == p5.x && p4.x == p6.x) || (p4.y == p5.y && p4.y == p6.y) ||
			(p4.x < 0 && p5.x < 0 && p6.x < 0) ||
			(p4.y < 0 && p5.y < 0 && p6.y < 0) ||
			(p4.x > WIN_LEN && p5.x > WIN_LEN && p6.x > WIN_LEN) ||
			(p4.y > WIN_WID && p5.y > WIN_WID && p6.y > WIN_WID))
		return ;
	if ((p4.x - p5.x) * (p4.x - p6.x) <= 0.0)
		split_triangle(env, &p4, &p5, &p6);
	else if ((p5.x - p4.x) * (p5.x - p6.x) <= 0.0)
		split_triangle(env, &p5, &p4, &p6);
	else
		split_triangle(env, &p6, &p4, &p5);
}
