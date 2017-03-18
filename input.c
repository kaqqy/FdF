/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:59:17 by jshi              #+#    #+#             */
/*   Updated: 2017/02/17 18:43:26 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	exit_ss_arr(char **input, t_env *env, char ***ss, char *msg)
{
	int		i;

	ft_strarrdel(&input);
	if (ss)
	{
		i = -1;
		while (++i < env->wid)
			ft_strarrdel(&ss[i]);
		free(ss);
	}
	exit_prog(env, msg);
}

static char	***strsplit_arr(char **input, t_env *env)
{
	char	***ss;
	int		i;
	int		j;

	i = -1;
	if (!(ss = (char***)malloc(sizeof(*ss) * env->wid)))
		exit_ss_arr(input, env, ss, "Error: Malloc failed for variable ss\n");
	while (++i < env->wid)
		ss[i] = ft_strsplit(input[i], ' ');
	while ((i = -1) && ss[0] && ss[0][env->len])
		env->len++;
	while (++i < env->wid && (j = -1))
	{
		if (!ss[i])
			exit_ss_arr(input, env, ss, "Error: ft_strsplit returned NULL\n");
		while (++j < env->len)
		{
			if (!ss[i][j] || ss[i][env->len])
				exit_ss_arr(input, env, ss, "Error: Lines differ in length\n");
//			if (!ft_is_int(ss[i][j]))
//				exit_ss_arr(input, env, ss, "Error: Input isn't an integer\n");
		}
	}
	ft_strarrdel(&input);
	return (ss);
}

static char	**read_file(t_env *env, int argc, char **argv)
{
	int		fd;
	int		ret;
	char	**input;
	char	*line;

	if (argc < 2)
		exit_prog(env, "Usage: ./fdf sourcefile colors\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		exit_prog(env, "Error: Can't open file\n");
	if (!(input = (char**)ft_ptrarrnew()))
		exit_prog(env, "Error: Malloc failed for variable input\n");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_ptrarradd((void***)&input, ft_strdup(line), &env->wid);
		free(line);
	}
	if (close(fd) == -1)
		exit_prog(env, "Error: Can't close file\n");
	if (!env->wid)
		exit_prog(env, "Error: File is empty\n");
	if (ret < 0)
		exit_prog(env, "Error: Can't read file\n");
	ft_ptrarradd((void***)&input, NULL, &env->wid);
	env->wid--;
	return (input);
}

static void	add_pts(t_env *env, int **nums)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->wid)
		env->pts[i] = (t_pt*)malloc(sizeof(**env->pts) * env->len);
	i = -1;
	while (++i < env->wid)
		if (!env->pts[i])
			exit_prog(env, "Error: Malloc failed for variable env->pts[i]\n");
	i = -1;
	while (++i < env->wid && (j = -1))
	{
		while (++j < env->len)
		{
			env->pts[i][j].x = j;
			env->pts[i][j].y = i;
			env->pts[i][j].z = nums[i][j];
		}
	}
	i = -1;
	while (++i < env->wid)
		free(nums[i]);
	free(nums);
}

void		get_map(t_env *env, int argc, char **argv)
{
	int		**nums;

	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->pts = NULL;
	env->cpts = NULL;
	env->colors = NULL;
	env->len = 0;
	env->wid = 0;
	env->drag = 0;
	env->hidden = 1;
	env->key = -1;
	nums = str_to_int_arr(strsplit_arr(read_file(env, argc, argv), env), env);
	if (!(env->pts = (t_pt**)malloc(sizeof(*env->pts) * env->wid)))
		exit_prog(env, "Error: Malloc failed for variable pts\n");
	add_pts(env, nums);
	get_colors(env, argc, argv);
}
