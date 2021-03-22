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

int		ft_parse_string(char *data, char *start, char *close, char **val)
{
	int ret;

	if ((ret = ft_strstr_index(data, start)) == -1)
		return (1);
	*val = ft_get_string(data, ret, ft_strstr_index(data, close));
	return (0);
}

int		ft_standard2(char *data, t_object *object)
{
	int ret;

	ret = 0;
	ret |= !ft_parse_close(data, "<slice>", "</slice>",
			&(object->slice));
	ret |= !ft_parse_close(data, "<slice_vec>", "</slice_vec>",
			&(object->slice_vec));
	ret |= !ft_parse_close(data, "<rotate>", "</rotate>", &(object->rotate));
	ret |= !ft_parse_close(data, "<scale>", "</scale>", &(object->scale));
	ret |= !ft_color(data, &(object->main_color),
			"<color>", "</color>");
	return (ret);
}

int		ft_standard(char *data, t_object *object)
{
	int		ret;
	int		resolution;

	ret = 0;
	ret |= !ft_parse_value(data, "<specular>",
	"</specular>", &(object->specular));
	ret |= !ft_parse_value(data, "<diffuse>",
	"</diffuse>", &(object->diffuse));
	ret |= !ft_parse_string(data, "<image>",
	"</image>", &(object->image));
	ret |= !ft_parse_value(data, "<reflect>",
	"</reflect>", &(object->reflect));
	ret |= !ft_parse_value(data, "<refract>",
	"</refract>", &(object->refract));
	ret |= !ft_parse_value(data, "<blur>",
	"</blur>", &(object->blur));
	ret |= !ft_parse_close(data, "<position>", "</position>",
			&(object->position));
	ret = ft_standard2(data, object);
	object->normal = (t_vec){0, 1, 0};
	resolution = WIN_WIDTH * WIN_HEIGHT;
	if (object->blur != 0)
		object->pix = (int *)malloc(sizeof(int) * resolution);
	return (!ret);
}

int		ft_parse1(char *data, t_env *env, int parent)
{
	if (parent == LIGHT_T && !ft_light(data, &(env->object_list),
	&(env->o_count)))
		return (0);
	if (parent == PARABOLOID_T && !ft_paraboloid(data, &(env->object_list),
	&(env->o_count)))
		return (0);
	if (parent == ELLIPSOID_T && !ft_ellipsoid(data, &(env->object_list),
	&(env->o_count)))
		return (0);
	if (parent == CUBE_T && !ft_cube(data, &(env->object_list),
	&(env->o_count)))
		return (0);
	if (parent == TRIANGLE_T && !ft_triangle(data, &(env->object_list),
	&(env->o_count)))
		return (0);
	if (parent == DISK_T && !ft_disk(data, &(env->object_list),
	&(env->o_count)))
		return (0);
	return (1);
}

int		ft_parse(char *data, t_env *env, int parent)
{
	if (parent == SCENE_T && !ft_scene(data, env))
		return (0);
	if (parent == CAMERA_T && !ft_camera(data, env))
		return (0);
	if (parent == PLANE_T && !ft_plane(data, &(env->object_list),
				&(env->o_count)))
		return (0);
	if (parent == SPHERE_T && !ft_sphere(data, &(env->object_list),
				&(env->o_count)))
		return (0);
	if (parent == CYLINDER_T && !ft_cylinder(data, &(env->object_list),
				&(env->o_count)))
		return (0);
	if (parent == CONE_T && !ft_cone(data, &(env->object_list),
				&(env->o_count)))
		return (0);
	if (!ft_parse1(data, env, parent))
		return (0);
	return (1);
}
