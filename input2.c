/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 01:32:33 by jshi              #+#    #+#             */
/*   Updated: 2016/12/01 00:30:32 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	exit_stia(char ***ss, t_env *env, int **nums, char *msg)
{
	int		i;

	if (ss)
	{
		i = -1;
		while (++i < env->wid)
			ft_strarrdel(&ss[i]);
		free(ss);
	}
	if (nums)
	{
		i = -1;
		while (++i < env->wid)
			free(nums[i]);
		free(nums);
	}
	exit_prog(env, msg);
}

int			**str_to_int_arr(char ***ss, t_env *env)
{
	int		**nums;
	int		i;
	int		j;

	if (!env->len)
		exit_stia(ss, env, NULL, "Error: Lines are empty\n");
	if (!(nums = (int**)malloc(sizeof(*nums) * env->wid)))
		exit_stia(ss, env, nums, "Error: Malloc failed for variable nums\n");
	i = -1;
	while (++i < env->wid)
		nums[i] = (int*)malloc(sizeof(**nums) * env->len);
	i = -1;
	while (++i < env->wid)
		if (!nums[i])
			exit_stia(ss, env, nums,
					"Error: Malloc failed for variable nums[i]\n");
	i = -1;
	while (++i < env->wid && (j = -1))
		while (++j < env->len)
			nums[i][j] = ft_atoi(ss[i][j]);
	i = -1;
	while (++i < env->wid)
		ft_strarrdel(&ss[i]);
	free(ss);
	return (nums);
}

static int	get_color(char *str)
{
	int		len;
	int		i;
	int		color;

	len = ft_strlen(str);
	if (len < 6)
		return (-1);
	i = 0;
	color = 0;
	while (++i <= 6)
	{
		if (str[len - i] >= '0' && str[len - i] <= '9')
			color += (str[len - i] - '0') * (1 << (4 * (i - 1)));
		else if (str[len - i] >= 'a' && str[len - i] <= 'f')
			color += (str[len - i] - 'a' + 10) * (1 << (4 * (i - 1)));
		else if (str[len - i] >= 'A' && str[len - i] <= 'F')
			color += (str[len - i] - 'A' + 10) * (1 << (4 * (i - 1)));
		else
			return (-1);
	}
	return (color);
}

void		get_colors(t_env *env, int argc, char **argv)
{
	int		i;

	env->num_colors = argc - 2;
	if (env->num_colors == 0)
		env->num_colors = 1;
	if (!(env->colors = (int*)malloc(sizeof(*env->colors) * env->num_colors)))
		exit_prog(env, "Error: Malloc failed for variables env->colors\n");
	if (argc == 2)
	{
		env->colors[0] = 0xffffff;
		return ;
	}
	i = 1;
	while (++i < argc)
		if ((env->colors[i - 2] = get_color(argv[i])) == -1)
			exit_prog(env, "Error: Invalid color\n");
}
