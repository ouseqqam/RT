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

int	ft_cube(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*cube;

	cube = ft_new_object();
	cube->type = type_cube;
	cube->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_close(data, "<bound_min>",
	"</bound_min>", &(cube->obj.b_min));
	ret |= !ft_parse_close(data, "<bound_max>",
	"</bound_max>", &(cube->obj.b_max));
	ret |= !ft_standard(data, &(cube->obj));
	if (ret)
	{
		free(cube);
		return (0);
	}
	ft_object_push_back(object_list, cube);
	return (1);
}

int	ft_camera(char *data, t_env *env)
{
	int ret;

	ret = 0;
	ret |= !ft_parse_value(data, "<fov>",
	"</fov>", &(env->cam.fov));
	ret |= !ft_parse_value(data, "<focus_dist>",
	"</focus_dist>", &(env->cam.focus_dist));
	ret |= !ft_parse_value(data, "<aperture>",
	"</aperture>", &(env->cam.aperture));
	ret |= !ft_parse_value(data, "<angle>",
			"</angle>", &(env->cam.angle));
	ret |= !ft_parse_close(data, "<position>",
	"</position>",
			&(env->cam.position));
	ret |= !ft_parse_close(data, "<look_at>",
			"</look_at>", &(env->cam.look_at));
	env->xml_check.y++;
	return (!ret);
}

int	ft_triangle(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*triangle;

	triangle = ft_new_object();
	triangle->type = type_triangle;
	triangle->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_close(data, "<vertex_0>",
	"</vertex_0>", &(triangle->obj.v0));
	ret |= !ft_parse_close(data, "<vertex_1>",
	"</vertex_1>", &(triangle->obj.v1));
	ret |= !ft_parse_close(data, "<vertex_2>",
	"</vertex_2>", &(triangle->obj.v2));
	ret |= !ft_standard(data, &(triangle->obj));
	if (ret)
	{
		free(triangle);
		return (0);
	}
	ft_object_push_back(object_list, triangle);
	return (1);
}

int	ft_disk(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*disk;

	disk = ft_new_object();
	disk->type = type_disk;
	disk->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<radius>", "</radius>",
			&(disk->obj.radius));
	ret |= !ft_standard(data, &(disk->obj));
	if (ret)
	{
		free(disk);
		return (0);
	}
	ft_object_push_back(object_list, disk);
	return (1);
}
