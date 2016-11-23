/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:29:25 by jshi              #+#    #+#             */
/*   Updated: 2016/11/23 03:28:23 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_env	*env;
	int		i;
	int		j;

	if (!(env = (t_env*)malloc(sizeof(*env))))
		exit_prog(env, "Error: Malloc failed for variable env\n");
	get_map(env, argc, argv);
	i = -1;
	while (++i < env->wid)
	{
		j = -1;
		while (++j < env->len)
		{
			ft_printf("%d %d %d\n", env->pts[i][j].x, env->pts[i][j].y,
					env->pts[i][j].z);
		}
		ft_printf("\n");
	}
	return (0);
}
