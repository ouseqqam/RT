/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:36:31 by achatoua          #+#    #+#             */
/*   Updated: 2021/03/16 16:36:38 by achatoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

int	ft_check_mandatory3(t_env *env, int index,
		int parent, int level)
{
	if (level == 2 && parent == ELLIPSOID_T &&
			!ft_strstr(TAG_ELLIPSOID_L_1""\
			TAG_ELLIPSOID_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == CUBE_T &&
			!ft_strstr(TAG_CUBE_L_1""\
			TAG_CUBE_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == TRIANGLE_T &&
			!ft_strstr(TAG_TRIANGLE_L_1""\
			TAG_TRIANGLE_L_2""TAG_TRIANGLE_L_3, env->tags[level][index]))
		return (0);
	if (level == 3 && parent == COLOR_T &&
			!ft_strstr(TAG_COLOR_L, env->tags[level][index]))
		return (0);
	if (level == 3 && (parent == POSITION_T
		|| parent == SCALE_T || parent == LOOK_AT_T
		|| parent == ROTATE_T || parent == BOUND_MIN_T
		|| parent == BOUND_MAX_T || parent == VERTEX_0_T
		|| parent == VERTEX_1_T || parent == VERTEX_2_T)
			&& !ft_strstr(TAG_VECTOR_L, env->tags[level][index]))
		return (0);
	return (1);
}

int	ft_check_mandatory2(t_env *env, int index,
		int parent, int level)
{
	if (level == 2 && parent == SPHERE_T &&
			!ft_strstr(TAG_SPHERE_L_1""TAG_SPHERE_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == DISK_T &&
			!ft_strstr(TAG_DISK_L_1""TAG_DISK_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == PLANE_T &&
			!ft_strstr(TAG_PLANE_L_1""TAG_PLANE_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == CYLINDER_T &&
			!ft_strstr(TAG_CY_L_1""TAG_CY_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == CONE_T &&
			!ft_strstr(TAG_CONE_L_1""TAG_CONE_L_2, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == LIGHT_T &&
			!ft_strstr(TAG_LIGHT_L, env->tags[level][index]))
		return (0);
	if (level == 2 && parent == PARABOLOID_T &&
			!ft_strstr(TAG_PA_L_1""TAG_PA_L_2, env->tags[level][index]))
		return (0);
	if (ft_check_mandatory3(env, index,
				parent, level) == 0)
		return (0);
	return (1);
}

int	ft_check_mandatory(t_env *env, t_parse *parse)
{
	int i;

	if (!parse->level && !parse->parent)
		return (1);
	if (parse->level == 2 && parse->parent == SCENE_T &&
			!ft_strstr(TAG_SCENE_L, env->tags[parse->level][parse->index]))
		return (0);
	if (parse->level == 2 && parse->parent == CAMERA_T &&
			!ft_strstr(TAG_CAMERA_L, env->tags[parse->level][parse->index]))
		return (0);
	if (ft_check_mandatory2(env, parse->index,
				parse->parent, parse->level) == 0)
		return (0);
	if (parse->level >= 2)
	{
		i = -1;
		while (++i < TAGS_NUM && parse->man[i] != -1)
			if (parse->man[i] == parse->index)
				return (0);
		parse->man[i] = parse->index;
	}
	return (1);
}
