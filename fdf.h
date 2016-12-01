/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:28:28 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 03:54:23 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_LEN 960
# define WIN_WID 720

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct	s_pt
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_pt;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		bpp;
	int		sl;
	int		endian;
	t_pt	**pts;
	t_pt	**cpts;
	t_pt	center;
	int		len;
	int		wid;
	int		cx;
	int		cy;
	t_pt	x_axis;
	t_pt	y_axis;
	t_pt	z_axis;
	t_pt	cx_axis;
	t_pt	cy_axis;
	t_pt	cz_axis;
	int		drag;
	int		hidden;
	int		*colors;
	int		num_colors;
	int		key;
}				t_env;

void			exit_prog(t_env *env, char *msg);
void			get_map(t_env *env, int argc, char **argv);
int				**str_to_int_arr(char ***ss, t_env *env);
void			get_colors(t_env *env, int argc, char **argv);
void			config_pts(t_env *env);
void			draw_point(t_env *env, int x, int y, int color);
void			draw_line(t_env *env, t_pt *pt1, t_pt *pt2);
void			draw_map(t_env *env);
void			draw_triangle(t_env *env, t_pt *p1, t_pt *p2, t_pt *p3);
int				key_press_hook(int k, t_env *env);
int				key_release_hook(int k, t_env *env);
int				mouse_press_hook(int b, int x, int y, t_env *env);
int				mouse_release_hook(int b, int x, int y, t_env *env);
int				motion_hook(int x, int y, t_env *env);
int				expose_hook(t_env *env);
int				loop_hook(t_env *env);
void			rotate_x(t_pt *p1, t_pt *p2, double angle);
void			rotate_y(t_pt *p1, t_pt *p2, double angle);
void			rotate_z(t_pt *p1, t_pt *p2, double angle);
void			rotate_axis(t_pt *p1, t_pt *p2, t_pt *axis, double angle);
void			zoom(t_pt *p1, t_pt *p2, double scale);
void			rotate_x_all(t_env *env, double angle);
void			rotate_y_all(t_env *env, double angle);
void			rotate_z_all(t_env *env, double angle);
void			rotate_axis_all(t_env *env, t_pt *axis, double angle);
void			zoom_all(t_env *env, t_pt *center, double scale);
#endif
