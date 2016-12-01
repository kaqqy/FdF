/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:29:25 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 03:50:57 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	display_controls(void)
{
	ft_printf("%vDrag to rotate/translate map%y\n", 0x00ffff);
	ft_printf("%vScroll up/down to zoom in/out%y\n", 0x00ff00);
	ft_printf("%vKeys: %y\n", 0xffff00);
	ft_printf("%vControl - Toggle dragging mode\n", 0xff00ff);
	ft_printf("Option - Toggle hidden surfaces%y\n");
	ft_printf("%vw/x - Rotate around x-axis\n", 0xff0000);
	ft_printf("a/d - Rotate around y-axis\n");
	ft_printf("e/z - Rotate around z-axis%y\n");
	ft_printf("%vt/b - Rotate around the map's x-axis\n", 0x0000ff);
	ft_printf("f/h - Rotate around the map's y-axis\n");
	ft_printf("y/v - Rotate around the map's z-axis%y\n");
	ft_printf("%v+/- - Zoom in/out%y\n", 0xff8080);
	ft_printf("%vArrows - Translate the map%y\n", 0x80ff80);
}

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
	display_controls();
	draw_map(env);
	mlx_key_hook(env->win, &key_release_hook, env);
	mlx_mouse_hook(env->win, &mouse_press_hook, env);
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	mlx_hook(env->win, 2, 0, &key_press_hook, env);
	mlx_hook(env->win, 5, 0, &mouse_release_hook, env);
	mlx_hook(env->win, 6, 0, &motion_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
