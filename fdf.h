/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:28:28 by jshi              #+#    #+#             */
/*   Updated: 2016/11/25 18:39:58 by jshi             ###   ########.fr       */
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
	t_pt	center;
	int		len;
	int		wid;
}				t_env;

void			exit_prog(t_env *env, char *msg);
void			get_map(t_env *env, int argc, char **argv);
int				**str_to_int_arr(char ***ss, t_env *env);
void			config_pts(t_env *env);
void			draw_map(t_env *env);
int				key_release_hook(int k, t_env *env);
void			rotate_x(t_pt *p1, t_pt *p2, double angle);
void			rotate_y(t_pt *p1, t_pt *p2, double angle);
void			rotate_z(t_pt *p1, t_pt *p2, double angle);
void			zoom(t_pt *p1, t_pt *p2, double scale);
#endif
