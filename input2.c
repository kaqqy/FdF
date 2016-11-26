/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 01:32:33 by jshi              #+#    #+#             */
/*   Updated: 2016/11/23 22:58:27 by jshi             ###   ########.fr       */
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
