/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:05:07 by jshi              #+#    #+#             */
/*   Updated: 2016/11/25 19:10:36 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_release_hook(int k, t_env *env)
{
	int		i;
	int		j;

	ft_printf("%d\n", k);
	if (k == 53)
		exit_prog(env, "");
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			if (k == 13)
				rotate_x(&env->pts[i][j], &env->center, M_PI / 12);
			else if (k == 7)
				rotate_x(&env->pts[i][j], &env->center, -M_PI / 12);
			else if (k == 2)
				rotate_y(&env->pts[i][j], &env->center, M_PI / 12);
			else if (k == 0)
				rotate_y(&env->pts[i][j], &env->center, -M_PI / 12);
			else if (k == 14)
				rotate_z(&env->pts[i][j], &env->center, M_PI / 12);
			else if (k == 6)
				rotate_z(&env->pts[i][j], &env->center, -M_PI / 12);
			else if (k == 123)
				env->pts[i][j].x -= 5;
			else if (k == 124)
				env->pts[i][j].x += 5;
			else if (k == 125)
				env->pts[i][j].y += 5;
			else if (k == 126)
				env->pts[i][j].y -= 5;
			else if (k == 24)
				zoom(&env->pts[i][j], &env->center, 1.1);
			else if (k == 27)
				zoom(&env->pts[i][j], &env->center, 1.0 / 1.1);
		}
	}
	draw_map(env);
	return (0);
}
