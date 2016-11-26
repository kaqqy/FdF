/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:29:25 by jshi              #+#    #+#             */
/*   Updated: 2016/11/25 18:07:18 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(*env))))
		exit_prog(env, "Error: Malloc failed for variable env\n");
	get_map(env, argc, argv);
	config_pts(env);
	if (!(env->mlx = mlx_init()))
		exit_prog(env, "Error: mlx_init() returned NULL\n");
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_WID, "FdF")))
		exit_prog(env, "Error: mlx_new_window() returned NULL\n");
	if (!(env->img = mlx_new_image(env->mlx, WIN_LEN, WIN_WID)))
		exit_prog(env, "Error: mlx_new_image() returned NULL\n");
	env->data = mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->endian);
	env->bpp /= 8;
	draw_map(env);
	mlx_key_hook(env->win, &key_release_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
