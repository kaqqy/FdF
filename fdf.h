/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:28:28 by jshi              #+#    #+#             */
/*   Updated: 2016/11/23 01:33:47 by jshi             ###   ########.fr       */
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
	int		x;
	int		y;
	int		z;
}				t_pt;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	t_pt	**pts;
	int		len;
	int		wid;
}				t_env;

void			exit_prog(t_env *env, char *msg);
void			get_map(t_env *env, int argc, char **argv);
int				**str_to_int_arr(char ***ss, t_env *env);
#endif
