/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:09:00 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 03:37:49 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_pt *p1, t_pt *p2, double angle)
{
	t_pt	p3;
	t_pt	p4;

	p3.y = p1->y - p2->y;
	p3.z = p1->z - p2->z;
	p4.y = p3.y * cos(angle) - p3.z * sin(angle);
	p4.z = p3.y * sin(angle) + p3.z * cos(angle);
	p1->y = p2->y + p4.y;
	p1->z = p2->z + p4.z;
}

void	rotate_y(t_pt *p1, t_pt *p2, double angle)
{
	t_pt	p3;
	t_pt	p4;

	p3.z = p1->z - p2->z;
	p3.x = p1->x - p2->x;
	p4.z = p3.z * cos(angle) - p3.x * sin(angle);
	p4.x = p3.z * sin(angle) + p3.x * cos(angle);
	p1->z = p2->z + p4.z;
	p1->x = p2->x + p4.x;
}

void	rotate_z(t_pt *p1, t_pt *p2, double angle)
{
	t_pt	p3;
	t_pt	p4;

	p3.x = p1->x - p2->x;
	p3.y = p1->y - p2->y;
	p4.x = p3.x * cos(angle) - p3.y * sin(angle);
	p4.y = p3.x * sin(angle) + p3.y * cos(angle);
	p1->x = p2->x + p4.x;
	p1->y = p2->y + p4.y;
}

void	rotate_axis(t_pt *p1, t_pt *p2, t_pt *axis, double angle)
{
	t_pt	p3;
	t_pt	origin;
	double	angle_z;
	double	angle_y;

	p3.x = p1->x - p2->x;
	p3.y = p1->y - p2->y;
	p3.z = p1->z - p2->z;
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	angle_z = (axis->y == 0.0 && axis->x == 0.0) ? 0 : atan(-axis->y / axis->x);
	angle_y = atan(-axis->z / sqrt(axis->x * axis->x + axis->y * axis->y));
	rotate_z(&p3, &origin, angle_z);
	rotate_y(&p3, &origin, angle_y);
	rotate_x(&p3, &origin, angle);
	rotate_y(&p3, &origin, -angle_y);
	rotate_z(&p3, &origin, -angle_z);
	p1->x = p3.x + p2->x;
	p1->y = p3.y + p2->y;
	p1->z = p3.z + p2->z;
}

void	zoom(t_pt *p1, t_pt *p2, double scale)
{
	p1->x = (p1->x - p2->x) * scale + p2->x;
	p1->y = (p1->y - p2->y) * scale + p2->y;
	p1->z = (p1->z - p2->z) * scale + p2->z;
}
